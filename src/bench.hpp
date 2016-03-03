#ifndef BENCH_HPP
#define BENCH_HPP

#include <iostream>

enum Method
{
    SIMPLE,
};

std::istream & operator>>(std::istream &is, Method &m);

void MatrixMult(float *a, float *b, float *c, size_t n);

#endif
