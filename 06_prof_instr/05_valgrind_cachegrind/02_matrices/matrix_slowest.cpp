#include <iostream>

#define N 1000

using namespace std;

void multiply(float **A, float **B, float **out, int size) {
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            for (int in = 0; in < size; in++)
                out[row][col] += A[row][in] * B[in][col];
}

int main() {
    float **A = new float *[N];
    float **B = new float *[N];
    float **C = new float *[N];

    for (int i = 0; i < N; i++) {
        A[i] = new float[N];
        B[i] = new float[N];
        C[i] = new float[N];
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = (i + j) % 5;
            B[i][j] = ((i + j) * (j + i)) % 5;
            C[i][j] = 0.0;
        }

    multiply(A, B, C, N);

    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}
