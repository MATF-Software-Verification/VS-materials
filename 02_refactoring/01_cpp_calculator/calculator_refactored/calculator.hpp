#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <cmath>

void showChoices(std::ostream & ostr);
bool readChoice(std::istream & istr, int *x);

void readOperands(std::istream & istr, float *x, float *y);
void calculate(int choice, float x, float y, float *result);
void printResults(std::ostream & ostr, int choice, float result);

float add(float, float);
float subtract(float, float);
float multiply(float, float);
float divide(float, float);

#endif				// CALCULATOR_H
