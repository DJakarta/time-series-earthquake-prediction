#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "event.h"
#include <string>
#include <QVector>

using namespace std;

class DataHandler {
private:

public:
	QVector<Event> *events;
	QDate firstDate, lastDate;
	QDate zeroDate = *(new QDate(1970, 1, 1));

	QVector<Event> *plottedEvents;

	//start and end date for filtering
	QDate plottedEventsStartDate;
	QDate plottedEventsEndDate;

	//first and last dates found in vector
	QDate plottedEventsFirstDate;
	QDate plottedEventsLastDate;

	double plottedEventsMinMagnitude;
	double plottedEventsMaxMagnitude;
	QVector<double> *plottedEventsX;
	QVector<double> *plottedEventsY;

	QVector<Event> *topEvents;
	QVector<double> *topEventsMapX;
	QVector<double> *topEventsMapY;

	QVector<Event> *predictedEvents;

	//start and end date for filtering
	QDate predictedEventsStartDate;
	QDate predictedEventsEndDate;

	//first and last dates found in vector
	QDate predictedEventsFirstDate;
	QDate predictedEventsLastDate;

	double predictedEventsMinMagnitude;
	double predictedEventsMaxMagnitude;
	QVector<double> *predictedEventsX;
	QVector<double> *predictedEventsY;



	DataHandler();

	int parseXML(const string name);

	void sortByMagnitudeAsc();
	void sortByMagnitudeDesc();
	void sortByDateAsc();
	void sortByDateDesc();

	static void sortEventsByMagnitudeAsc(QVector<Event> *vector);
	static void sortEventsByMagnitudeDesc(QVector<Event> *vector);
	static void sortEventsByDateAsc(QVector<Event> *vector);
	static void sortEventsByDateDesc(QVector<Event> *vector);

	static QVector<Event> *getFilteredEvents(QVector<Event> *evs, QDate date1, QDate date2);
	static QVector<Event> *getFilteredEvents(QVector<Event> *evs, bool b, QDate date2);
	static QVector<Event> *getFilteredEvents(QVector<Event> *evs, QDate date1, bool b);
	static QVector<Event> *getFilteredEvents(QVector<Event> *evs, bool b1, bool b2);
	static QVector<Event> *getFilteredEvents(QVector<Event> *evs, double magnitude1, double magnitude2);

	static QDate getEventsFirstDate(QVector<Event> *evs);
	static QDate getEventsLastDate(QVector<Event> *evs);
	static Event getEventsClosestMapEvent(QVector<Event> *evs, double latitude, double longitude);
	static Event getEventsClosestTimeEvent(QVector<Event> *evs, QDate date);

	static QVector<double> *getEventsX(QVector<Event> *evs);
	static QVector<double> *getEventsY(QVector<Event> *evs);

	static QVector<double> *getEventsMapX(QVector<Event> *evs);
	static QVector<double> *getEventsMapY(QVector<Event> *evs);

	QDate getFirstDate();
	QDate getLastDate();

	static void getTrendLineParameters(QVector<double> v, double *a, double *b);

	static double *getEventsTimeSeries(QVector<Event> *evs, int *n);

	static double distance(double x1, double y1, double x2, double y2);
};

#endif // DATAHANDLER_H
