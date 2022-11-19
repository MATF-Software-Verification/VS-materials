#include <limits.h>
#include <string.h>
#include <stdio.h>

// C program for Naive Pattern Searching algorithm

void search_naive(char *txt, char *pat)
{
	int M = strlen(pat);
	int N = strlen(txt);

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) {
		int j;

		/* For current index i, check for pattern match */
		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		if (j == M)	// if pat[0...M-1] = txt[i, i+1, ...i+M-1]
			printf("Pattern found at index %d n", i);
	}
}

/* Functions for Bad Character Heuristic of Boyer Moore String Matching Algorithm */

#define NO_OF_CHARS 256

// A utility function to get maximum of two integers
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS])
{
	int i;

	// Initialize all occurrences as -1
	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	// Fill the actual value of last occurrence of a character
	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

void search_boyer(char *txt, char *pat)
{
	int m = strlen(pat);
	int n = strlen(txt);

	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);

	int s = 0;		// s is shift of the pattern with respect to text
	while (s <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		if (j < 0) {
			printf("\n pattern occurs at shift = %d", s);

			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

		}

		else
			s += max(1, j - badchar[txt[s + j]]);
	}
}

// C++ program for implementation of KMP pattern searching
// algorithm
//#include<bits/stdc++.h>

void computeLPSArray(char *pat, int M, int *lps);

// Prints occurrences of txt[] in pat[]
void search_kmp(char *txt, char *pat)
{
	int M = strlen(pat);
	int N = strlen(txt);

	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	int lps[M];

	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, M, lps);

	int i = 0;		// index for txt[]
	int j = 0;		// index for pat[]
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			printf("Found pattern at index %d n", i - j);
			j = lps[j - 1];
		}
		// mismatch after j matches
		else if (i < N && pat[j] != txt[i]) {
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char *pat, int M, int *lps)
{
	// length of the previous longest prefix suffix
	int len = 0;

	lps[0] = 0;		// lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to M-1
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		} else		// (pat[i] != pat[len])
		{
			// This is tricky. Consider the example.
			// AAACAAAA and i = 7. The idea is similar
			// to search step.
			if (len != 0) {
				len = lps[len - 1];

				// Also, note that we do not increment
				// i here
			} else	// if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

/* Driver program to test above function */
int main()
{
	char txt[] =
	    "AABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAABAACBADAABBAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAAAABAACAADAABAAABAA";
	char pat[] = "AABAACEADAAB";
	int i;
	for (i = 0; i < 10; i++) {
		search_naive(txt, pat);

		search_boyer(txt, pat);

		search_kmp(txt, pat);
	}
	return 0;
}
