#include "bench.hpp"

void MatrixMultSimple(float *a, float *b, float *c, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            c[i * n + j] = 0.f;
            for (size_t k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}