#ifndef BENCH_HPP
#define BENCH_HPP

#include <map>
#include <string>

typedef void (*MatrixMult)(float *, float *, float *, size_t);
extern std::map<std::string, MatrixMult> functions;

void MatrixMultSimple(float *a, float *b, float *c, size_t n);

#endif
