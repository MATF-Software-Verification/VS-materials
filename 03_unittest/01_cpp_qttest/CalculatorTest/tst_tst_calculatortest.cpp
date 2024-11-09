#include "../Calculator/calculator.hpp"
#include <QtTest>
#include <sstream>
using namespace std;

class tst_calculatorTest : public QObject {
    Q_OBJECT public : tst_calculatorTest();
    ~tst_calculatorTest();

  private slots:
    void testAdd();
    void testSubtract();
    void testMultiply();
    void testDivide();

    void testCalculate();

    void testShowChoices();
    void testReadChoices();
};

tst_calculatorTest::tst_calculatorTest() {}

tst_calculatorTest::~tst_calculatorTest() {}

void tst_calculatorTest::testAdd() { QCOMPARE(add(2, 3), 5); }

void tst_calculatorTest::testSubtract() { QCOMPARE(subtract(2, 3), -1); }

void tst_calculatorTest::testMultiply() { QCOMPARE(multiply(2, 3), 6); }

void tst_calculatorTest::testDivide() {
    QVERIFY(fabs(static_cast<double>(divide(2, 3)) - 2 / 3.0) < 0.0001);
    QVERIFY_EXCEPTION_THROWN(divide(2, 0), invalid_argument);
}

void tst_calculatorTest::testCalculate() {
    float result = 0;

    QVERIFY_EXCEPTION_THROWN(calculate(0, 2, 3, &result), invalid_argument);
    QVERIFY_EXCEPTION_THROWN(calculate(5, 2, 3, &result), invalid_argument);

    // check addition
    calculate(1, 2, 3, &result);
    QCOMPARE(result, 5.0);

    // check subtraction
    calculate(2, 12, 12, &result);
    QCOMPARE(result, 0.0);

    // check multiplication
    calculate(3, 12, 12, &result);
    QCOMPARE(result, 144.0);

    // check division
    calculate(4, 12, 12, &result);
    QCOMPARE(result, 1.0);
}

void tst_calculatorTest::testShowChoices() {
    ostringstream osstr;
    showChoices(osstr);
    QVERIFY(osstr && osstr.str() == "MENU\n\
1: Add \n\
2: Subtract\n\
3: Multiply \n\
4: Divide \n\
5: Exit \n\
Enter your choice :");
}

void tst_calculatorTest::testReadChoices() {
    istringstream isstr;
    isstr.str("1\n");

    int choice;
    QCOMPARE(readChoice(isstr, &choice), true);

    QCOMPARE(choice, 1);

    isstr.str(string("2\n"));
    QCOMPARE(isstr.str(), "2\n");

    QCOMPARE(readChoice(isstr, &choice), true);

    QCOMPARE(choice, 2);

    isstr.str(string("-2\n"));
    QCOMPARE(readChoice(isstr, &choice), false);
}

QTEST_APPLESS_MAIN(tst_calculatorTest)
#include "tst_tst_calculatortest.moc"
