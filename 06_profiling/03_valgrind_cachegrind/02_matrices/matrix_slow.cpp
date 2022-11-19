#include <iostream>

#define N 1000

using namespace std;

// Flips first and second loops
void multiply(float *A, float *B, float *out, int size)
{
	for (int col = 0; col < size; col++)
		for (int row = 0; row < size; row++) {
			float curr = 0;	// prevents from calculating position each time through
			for (int in = 0; in < size; in++)
				curr += A[row * size + in] * B[in * size + col];
			out[row * size + col] = curr;
		}
}

int main()
{
	float *A = new float[N * N];
	float *B = new float[N * N];
	float *C = new float[N * N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			A[i * N + j] = (i + j) % 5;
			B[i * N + j] = ((i + j) * (j + i)) % 5;
			C[i * N + j] = 0.0;
		}

	multiply(A, B, C, N);

	delete[]A;
	delete[]B;
	delete[]C;
	return 0;
}
