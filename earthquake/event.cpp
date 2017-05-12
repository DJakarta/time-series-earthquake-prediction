#include "event.h"
#include <cstdio>


QDate Event::getDate() {
	return this->date;
}

float Event::getDepth() {
	return this->depth;
}

bool Event::magnitudeLessThan(Event &ev1, Event &ev2) {
	return ev1.getMagnitude() < ev2.getMagnitude();
}

bool Event::magnitudeGreaterThan(Event &ev1, Event &ev2) {
	return ev1.getMagnitude() > ev2.getMagnitude();
}

bool Event::dateLessThan(Event &ev1, Event &ev2) {
	return ev1.getDate() < ev2.getDate();
}

bool Event::dateGreaterThan(Event &ev1, Event &ev2) {
	return ev1.getDate() > ev2.getDate();
}

Event::Event(float magnitude, float latitude, float longitude, float depth, string date) {
	int year, month, day;
	const char *str = date.c_str();

	sscanf(str, "%d-%d-%d", &year, &month, &day);

	QDate *parsedDate = new QDate(year, month, day);

	this->magnitude = magnitude;
	this->latitude = latitude;
	this->longitude = longitude;
	this->depth = depth;
	this->date = *parsedDate;
}

Event::Event(float magnitude, float latitude, float longitude, float depth, QDate date) {
	this->magnitude = magnitude;
	this->latitude = latitude;
	this->longitude = longitude;
	this->depth = depth;
	this->date = date;
}

Event::Event(const Event &ev) {
	this->magnitude = ev.magnitude;
	this->latitude = ev.latitude;
	this->longitude = ev.longitude;
	this->depth = ev.depth;
	this->date = QDate(ev.date);
}

Event::Event() {
}

Event::~Event() {
	//delete &(this->date);
}

float Event::getMagnitude() {
	return this->magnitude;
}

float Event::getLongitude() {
	return this->longitude;
}

float Event::getLatitude() {
	return this->latitude;
}
