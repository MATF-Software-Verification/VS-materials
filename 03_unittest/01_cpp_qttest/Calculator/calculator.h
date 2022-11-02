#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <cmath>
using namespace std;

void showChoices(ostream & ostr);
bool readChoice(istream & istr, int *x);

void readOperands(istream & istr, float *x, float *y);
void calculate(int choice, float x, float y, float *result);
void printResults(ostream & ostr, int choice, float result);

float add(float, float);
float subtract(float, float);
float multiply(float, float);
float divide(float, float);

#endif				// CALCULATOR_H
