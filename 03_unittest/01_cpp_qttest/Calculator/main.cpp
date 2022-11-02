#include "calculator.h"

int main()
{
	float x, y, result;
	int choice;

	showChoices(cout);
	while (!readChoice(cin, &choice))
		cerr << "Invalid choice" << endl;

	while (choice != 5) {
		cout << "Enter two numbers: ";
		readOperands(cin, &x, &y);

		calculate(choice, x, y, &result);
		printResults(cout, choice, result);

		showChoices(cout);
		while (!readChoice(cin, &choice))
			cerr << "Invalid choice" << endl;
	}
	return 0;
}

//    do
//    {
//        // showChoices(cout);

//        // cin >> choice;
//        switch (choice)
//        {
//        case 1:
//            cout << "Enter two numbers: ";
//            cin >> x >> y;
//            cout << "Sum " << add(x,y) <<endl;
//            break;
//        case 2:
//            cout << "Enter two numbers: ";
//            cin >> x >> y;
//            cout << "Difference " << subtract(x,y) <<endl;
//            break;
//        case 3:
//            cout << "Enter two numbers: ";
//            cin >> x >> y;
//            cout << "Product " << multiply(x,y) <<endl;
//            break;
//        case 4:
//            cout << "Enter two numbers: ";
//            cin >> x >> y;
//            cout << "Quotient " << divide(x,y) <<endl;
//            break;
//        case 5:
//            break;
//        default:
//            cout << "Invalid input" << endl;
//        }
//    }while (choice != 5);

//          return 0;
//}
