#include <tclap/CmdLine.h>
#include <sstream>
#include <iostream>
#include "bench.hpp"
#include "config.h"

int main(int argc, char *argv[])
{
    try {
        TCLAP::CmdLine cmd("Matrix multiplication benchmark", ' ', BENCH_VERSION);
        TCLAP::ValueArg<std::string> method("m", "method", "Calculation method", true, "SIMPLE", "string");

        cmd.parse(argc, argv);


    } catch (TCLAP::ArgException &e) {
        std::cerr << "ERROR: " << e.error() << " in command line argument " << e.argId() << std::endl;
        return 1;
    }
}
