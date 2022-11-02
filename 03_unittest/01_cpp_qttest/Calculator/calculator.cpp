#include "calculator.h"

void showChoices(ostream & ostr)
{
	ostr << "MENU" << endl;
	ostr << "1: Add " << endl;
	ostr << "2: Subtract" << endl;
	ostr << "3: Multiply " << endl;
	ostr << "4: Divide " << endl;
	ostr << "5: Exit " << endl;
	ostr << "Enter your choice :";
}

bool readChoice(istream & istr, int *x)
{
	istr >> *x;
	if (*x < 1 || *x > 5)
		return false;

	return true;
}

void readOperands(istream & istr, float *x, float *y)
{
	istr >> *x >> *y;
}

void calculate(int choice, float x, float y, float *result)
{

	if (!(choice >= 1 && choice < 5))
		throw
		    invalid_argument("Bad choice. Should be between 1 and 5.");

	switch (choice) {
	case 1:
		*result = add(x, y);
		break;
	case 2:
		*result = subtract(x, y);
		break;
	case 3:
		*result = multiply(x, y);
		break;
	case 4:
		*result = divide(x, y);
		break;
	}
}

void printResults(ostream & ostr, int choice, float result)
{
	if (!(choice >= 1 && choice < 5))
		throw
		    invalid_argument("Bad choice. Should be between 1 and 5.");

	switch (choice) {
	case 1:
		ostr << "ADD: " << result << endl;
		break;
	case 2:
		ostr << "SUBTRACT: " << result << endl;
		break;
	case 3:
		ostr << "MULTIPLY: " << result << endl;
		break;
	case 4:
		ostr << "DIVIDE: " << result << endl;
		break;
	}
}

float add(float a, float b)
{
	return a + b;
}

float subtract(float a, float b)
{
	return a - b;
}

float multiply(float a, float b)
{
	return a * b;
}

float divide(float a, float b)
{
	if (fabs(static_cast < double >(b)) < 0.0000001)
		throw invalid_argument("Division by zero");

	return a / b;
}
