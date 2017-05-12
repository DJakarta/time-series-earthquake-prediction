#ifndef EVENT_H
#define EVENT_H
#include <QDate>

using namespace std;

class Event {
private:
	float magnitude;
	float latitude;
	float longitude;
	float depth;
	QDate date;

public:
	Event(float magnitude, float latitude, float longitude, float depth, string date);
	Event(float magnitude, float latitude, float longitude, float depth, QDate date);
	Event(const Event &ev);
	Event();

	~Event();

	float getMagnitude();

	float getLongitude();

	float getLatitude();

	QDate getDate();

	float getDepth();

	static bool magnitudeLessThan(Event &ev1, Event &ev2);
	static bool magnitudeGreaterThan(Event &ev1, Event &ev2);
	static bool dateLessThan(Event &ev1, Event &ev2);
	static bool dateGreaterThan(Event &ev1, Event &ev2);
};

#endif // EVENT_H
