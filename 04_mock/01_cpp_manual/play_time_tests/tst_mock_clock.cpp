#include <QtTest>
#include "../MockClock/play_time.h"
#include "../MockClock/mock_clock.h"
#include "../MockClock/system_clock.h"
using namespace std;

// add necessary includes here

class MockForTest:public QObject {
 Q_OBJECT public:
	 MockForTest();
	~MockForTest();

	private slots:void play_time_test();
	void test_system_clock();
};

MockForTest::MockForTest()
{
}

MockForTest::~MockForTest()
{
}

void MockForTest::play_time_test()
{
	pt::ptime start_time( {
			     2018, 10, 24}, {
			     14, 13, 56});
	shared_ptr < mock_clock > clock =
	    make_shared < mock_clock > (start_time);
	play_time game(clock);

	game.start_session();

	pt::time_duration expected_duration(1, 12, 45, 1);
	clock->set(start_time + expected_duration);

	game.stop_session();

	QVERIFY(game.played_time() == expected_duration);
}

void MockForTest::test_system_clock()
{
	system_clock clock;

	auto before = pt::second_clock::local_time();
	auto by_clock = clock();
	auto after = pt::second_clock::local_time();

	QVERIFY(by_clock >= before && by_clock <= after);
}

QTEST_APPLESS_MAIN(MockForTest)
#include "tst_mockfortest.moc"
