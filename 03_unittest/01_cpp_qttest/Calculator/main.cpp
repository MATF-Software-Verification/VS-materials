#include "calculator.hpp"

int main() {
    float x, y, result;
    int choice;

    showChoices(std::cout);
    while (!readChoice(std::cin, &choice))
        std::cerr << "Invalid choice" << std::endl;

    while (choice != 5) {
        std::cout << "Enter two numbers: ";
        readOperands(std::cin, &x, &y);

        calculate(choice, x, y, &result);
        printResults(std::cout, choice, result);

        showChoices(std::cout);
        while (!readChoice(std::cin, &choice))
            std::cerr << "Invalid choice" << std::endl;
    }

    return 0;
}
