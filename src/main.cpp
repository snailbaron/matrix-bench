#include <Windows.h>
#include <tclap/CmdLine.h>
#include <sstream>
#include <iostream>
#include <queue>
#include <functional>
#include "bench.hpp"
#include "errors.hpp"
#include "config.h"
#include "running_median.hpp"

struct Measurement 
{
    double time;
    unsigned long long ticks;

    Measurement(double time, unsigned long long ticks) : time(time), ticks(ticks) {}
};

Measurement measure(LARGE_INTEGER freq, MatrixMult func, float *a, float *b, float *c, size_t n)
{
    unsigned z;
    unsigned long long r1 = __rdtscp(&z);

    LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);
    func(a, b, c, n);
    QueryPerformanceCounter(&end);
    double timeSec = static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart;

    unsigned long long r2 = __rdtscp(&z);

    return Measurement(timeSec, r2 - r1);
}

int main(int argc, char *argv[])
{
    std::string method;
    size_t size;
    size_t iters;

    try {
        TCLAP::CmdLine cmd("Matrix multiplication benchmark", ' ', BENCH_VERSION);

        TCLAP::ValueArg<std::string> methodArg("m", "method", "Calculation method", true, "", "method", cmd);
        TCLAP::ValueArg<size_t> sizeArg("s", "size", "Matrix size", true, 0, "size", cmd);
        TCLAP::ValueArg<size_t> itersArg("i", "iterations", "Number of iterations", true, 0, "number", cmd);

        cmd.parse(argc, argv);

        method = methodArg.getValue();
        size = sizeArg.getValue();
        iters = itersArg.getValue();
    } catch (TCLAP::ArgException &e) {
        std::cerr << "ERROR: " << e.error() << " in command line argument " << e.argId() << std::endl;
        return 1;
    } catch (CommandLineBullshit &bs) {
        std::cout << "You have some bullshit in argument " << bs.Arg() << std::endl;
        return 1;
    }

    if (functions.find(method) == functions.end()) {
        std::cout << "Unknown method: " << method << std::endl;
        return 1;
    }
    MatrixMult func = functions[method];

    std::cout << "Generating matrices" << std::endl;

    float *a = new float[size * size];
    float *b = new float[size * size];
    float *c = new float[size * size];

    for (size_t i = 0; i < size; i++) {
        a[i] = b[i] = 1.0f;
    };

    std::cout << "Compooting" << std::endl;

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    RunningMedian<double> times;
    RunningMedian<unsigned long long> ticks;

    for (size_t i = 2; i < iters; i++) {
        Measurement m = measure(freq, func, a, b, c, size);

        times.Push(m.time);
        ticks.Push(m.ticks);
    }

    std::cout << "TIME  : " << times.Median() << "s" << std::endl;
    std::cout << "TICKS : " << ticks.Median() << std::endl;
    std::cout << "TICKS/TIME : " << ticks.Median() / times.Median() << std::endl;



    delete[] a;
    delete[] b;
    delete[] c;
}
