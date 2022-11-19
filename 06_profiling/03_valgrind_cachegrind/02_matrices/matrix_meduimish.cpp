#include <iostream>

#define N 1000

using namespace std;

float dotProduct(float *A, float *B, int size)
{
	float curr = 0;

	for (int i = 0; i < size; i++)
		curr += A[i] * B[i];

	return curr;
}

void multiply(float *A, float *B, float *out, int size)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = i + 1; j < size; j++)
			std::swap(B[i * size + j], B[j * size + i]);

	for (int col = 0; col < size; col++)
		for (int row = 0; row < size; row++)
			out[row * size + col] = dotProduct(&A[row], &B[row], size);	// uses function above for dot product.
}

int main()
{
	float *A = new float[N * N];
	float *B = new float[N * N];
	float *C = new float[N * N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			A[i * N + j] = (i + j) % 5;

		}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			B[i * N + j] = ((i + j) * (j + i)) % 5;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			C[i * N + j] = 0.0;

	multiply(A, B, C, N);

	delete[]A;
	delete[]B;
	delete[]C;
	return 0;
}
