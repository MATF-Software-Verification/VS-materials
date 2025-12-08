#include "calculator.hpp"

void showChoices(std::ostream &ostr) {
    ostr << "MENU" << std::endl;
    ostr << "1: Add " << std::endl;
    ostr << "2: Subtract" << std::endl;
    ostr << "3: Multiply " << std::endl;
    ostr << "4: Divide " << std::endl;
    ostr << "5: Exit " << std::endl;
    ostr << "Enter your choice: ";
}

// If we want to keep the old interface:
// void showChoices() {
//     return showChoices(std::cout);
// }

// We can also use an enum for the op:
// typedef enum Operation {
//     OP_INVALID  = 0,
//     OP_ADD      = 1,
//     OP_SUBTRACT = 2,
//     OP_MULTIPLY = 3,
//     OP_DIVIDE   = 4,
//     OP_EXIT     = 5,
// } Operation;
//
// Operation readChoice(std::istream &istr) {
//     int opcode;
// 
//     istr >> opcode;
//     if (opcode < 1 || opcode > 5)
//         opcode = 0;
// 
//     Operation op = (Operation) opcode; 
//     return op;
// }
//
// Operation op = OP_INVALID;
// while ((op == readChoice(std::cin)) == OP_INVALID) {
//     cout << "Invalid input" << endl;
// }

bool readChoice(std::istream &istr, int *x) {
    istr >> *x;
    if (*x < 1 || *x > 5)
        return false;

    return true;
}

void readOperands(std::istream &istr, float *x, float *y) { istr >> *x >> *y; }

void calculate(int choice, float x, float y, float *result) {
    /* macro_assert(isValid(op))  */

    if (!(choice >= 1 && choice < 5))
        throw std::invalid_argument("Bad choice. Should be between 1 and 5.");

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

void printResults(std::ostream &ostr, int choice, float result) {
    if (!(choice >= 1 && choice < 5))
        throw std::invalid_argument("Bad choice. Should be between 1 and 5.");

    switch (choice) {
    case 1:
        ostr << "ADD: " << result << std::endl;
        break;
    case 2:
        ostr << "SUBTRACT: " << result << std::endl;
        break;
    case 3:
        ostr << "MULTIPLY: " << result << std::endl;
        break;
    case 4:
        ostr << "DIVIDE: " << result << std::endl;
        break;
    }
}

float add(float a, float b) { return a + b; }

float subtract(float a, float b) { return a - b; }

float multiply(float a, float b) { return a * b; }

float divide(float a, float b) {
    if (fabs(static_cast<double>(b)) < 0.0000001)
        throw std::invalid_argument("Division with zero");

    return a / b;
}
