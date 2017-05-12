#include "datahandler.h"
#include <QDomDocument>
#include <QFile>
#include <QtAlgorithms>
#include <string>
#include <cstdlib>
#include <QElapsedTimer>
#include <QtDebug>
#include <cmath>

DataHandler::DataHandler() {
}

int DataHandler::parseXML(const string name) {
    QElapsedTimer timer;
	timer.start();
	QDomDocument doc;
	Event *ev;

	this->events = new QVector<Event>();
	int x;

	QFile file(*(new QString(name.c_str())));
	if (x = (!file.open(QIODevice::ReadOnly)) || !doc.setContent(&file)) {
		//qDebug(name.c_str());
		//timer.invalidate();
		qDebug().nospace() << "File \"" << name.c_str() << "\" not found!";
		return 1;
	}

	QDomNodeList fileEvents = doc.elementsByTagName("event");
	//qDebug(to_string(fileEvents.size()).c_str());
	for (int i = 0; i < fileEvents.size(); i++) {
		QDomNode node = fileEvents.item(i);
		QDomElement magnitude = node.firstChildElement("magnitude").firstChildElement("mag");
		QDomElement origin = node.firstChildElement("origin");
		QDomElement latitude = origin.firstChildElement("latitude").firstChildElement("value");
		QDomElement longitude = origin.firstChildElement("longitude").firstChildElement("value");
		QDomElement depth = origin.firstChildElement("depth").firstChildElement("value");
		QDomElement time = origin.firstChildElement("time").firstChildElement("value");
		if (magnitude.isNull() || origin.isNull() || latitude.isNull() || longitude.isNull() ||
				depth.isNull() || time.isNull()) {
			continue;
		}

		ev = new Event(strtod(magnitude.text().toStdString().c_str(), NULL),
				strtod(latitude.text().toStdString().c_str(), NULL),
				strtod(longitude.text().toStdString().c_str(), NULL),
				strtod(depth.text().toStdString().c_str(), NULL), time.text().toStdString());
		this->events->append(*ev);
	}

	qDebug() << "Read " << this->events->length() << " events.";
	this->sortByDateAsc();
	this->firstDate = this->events->first().getDate();
	this->lastDate = this->events->last().getDate();

	qDebug() << "Parse duration: " << timer.elapsed() << " ms.";
	timer.invalidate();

	return 0;
}

QVector<Event>* DataHandler::getFilteredEvents(QVector<Event> *evs, bool b, QDate date2) {
	QVector<Event> *filtered = new QVector<Event>;
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (i->getDate() < date2) {
			filtered->append(*(new Event(*i)));
		}
	}
	return filtered;
}

QVector<Event>* DataHandler::getFilteredEvents(QVector<Event> *evs, QDate date1, bool b) {
	QVector<Event> *filtered = new QVector<Event>;
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (i->getDate() > date1) {
			filtered->append(*(new Event(*i)));
		}
	}
	return filtered;
}

QVector<Event>* DataHandler::getFilteredEvents(QVector<Event> *evs, bool b1, bool b2) {
	QVector<Event> *filtered = new QVector<Event>;
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		filtered->append(*(new Event(*i)));
	}
	return filtered;
}

QVector<Event>* DataHandler::getFilteredEvents(QVector<Event> *evs, QDate date1, QDate date2) {
	QVector<Event> *filtered = new QVector<Event>;
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (i->getDate() > date1 && i->getDate() < date2) {
			filtered->append(*(new Event(*i)));
		}
	}
	return filtered;
}

QVector<Event>* DataHandler::getFilteredEvents(QVector<Event> *evs, double magnitude1, double magnitude2) {
	QVector<Event> *filtered = new QVector<Event>;
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (i->getMagnitude() > magnitude1 && i->getMagnitude() < magnitude2) {
			filtered->append(*(new Event(*i)));
		}
	}
	return filtered;
}

QDate DataHandler::getEventsFirstDate(QVector<Event> *evs) {
	QDate first = evs->begin()->getDate();
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (i->getDate() < first) {
			first = i->getDate();
		}
	}
	return first;
}
QDate DataHandler::getEventsLastDate(QVector<Event> *evs) {
	QDate last = evs->begin()->getDate();
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (i->getDate() > last) {
			last = i->getDate();
		}
	}
	return last;
}

Event DataHandler::getEventsClosestMapEvent(QVector<Event> *evs, double latitude, double longitude) {
	Event closest = evs->first();
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (distance(i->getLongitude(), i->getLatitude(), longitude, latitude) <
				distance(closest.getLongitude(), closest.getLatitude(), longitude, latitude)) {
			closest = *i;
		}
	}
	return closest;
}

Event DataHandler::getEventsClosestTimeEvent(QVector<Event> *evs, QDate date) {
	Event closest = evs->first();
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (abs(i->getDate().daysTo(date)) < abs(closest.getDate().daysTo(date))) {
			closest = *i;
		}
	}
	return closest;
}

QVector<double>* DataHandler::getEventsX(QVector<Event> *evs) {
	QVector<double> *x = new QVector<double>;
	QVector<Event>::iterator i;
	QDate firstDate = DataHandler::getEventsFirstDate(evs);
	QDate zeroDate = *(new QDate(1970, 1, 1));
	for (i = evs->begin(); i < evs->end(); i++) {
		x->append(-(i->getDate().daysTo(zeroDate)) * 3600 * 24);
	}
	return x;
}
QVector<double>* DataHandler::getEventsY(QVector<Event> *evs) {
	QVector<double> *y = new QVector<double>;
	QVector<Event>::iterator i;
	QDate firstDate = DataHandler::getEventsFirstDate(evs);
	for (i = evs->begin(); i < evs->end(); i++) {
		y->append(i->getMagnitude());
	}
	return y;
}

QVector<double> *DataHandler::getEventsMapX(QVector<Event> *evs) {
	QVector<double> *x = new QVector<double>;
	QVector<Event>::iterator i;
	QDate firstDate = DataHandler::getEventsFirstDate(evs);
	for (i = evs->begin(); i < evs->end(); i++) {
		x->append(i->getLongitude());
	}
	return x;
}

QVector<double> *DataHandler::getEventsMapY(QVector<Event> *evs) {
	QVector<double> *y = new QVector<double>;
	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		y->append(i->getLatitude());
	}
	return y;
}

void DataHandler::sortByMagnitudeAsc() {
	DataHandler::sortEventsByMagnitudeAsc(this->events);
}
void DataHandler::sortByMagnitudeDesc() {
	qSort(this->events->begin(), this->events->end(), Event::magnitudeGreaterThan);
}

void DataHandler::sortByDateAsc() {
	qSort(this->events->begin(), this->events->end(), Event::dateLessThan);
}
void DataHandler::sortByDateDesc() {
	qSort(this->events->begin(), this->events->end(), Event::dateGreaterThan);
}

void DataHandler::sortEventsByMagnitudeAsc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::magnitudeLessThan);
}
void DataHandler::sortEventsByMagnitudeDesc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::magnitudeGreaterThan);
}

void DataHandler::sortEventsByDateAsc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::dateLessThan);
}
void DataHandler::sortEventsByDateDesc(QVector<Event> *vector) {
	qSort(vector->begin(), vector->end(), Event::dateGreaterThan);
}

QDate DataHandler::getFirstDate() {
	return this->firstDate;
}

QDate DataHandler::getLastDate() {
	return this->lastDate;
}

void DataHandler::getTrendLineParameters(QVector<double> v, double *a, double *b) {
	int i;
	double sumX = 0,
			sumY = 0,
			sumXY = 0,
			sumX2 = 0;
	for (i = 0; i < v.length(); i++) {
		sumX += i;
		sumY += v[i];
		sumXY += i * v[i];
		sumX2 += i * i;
	}
	*b = (sumXY - (sumX * sumY) / v.length()) / (sumX2 - (sumX * sumX) / v.length());
	*a = sumY / v.length() - (*b) * (sumX / v.length());
}

double *DataHandler::getEventsTimeSeries(QVector<Event> *evs, int *n) {
	QDate firstDate = DataHandler::getEventsFirstDate(evs);
	QDate lastDate = DataHandler::getEventsLastDate(evs);
	*n = firstDate.daysTo(lastDate) + 1;
	double *series = new double[*n]();

	QVector<Event>::iterator i;
	for (i = evs->begin(); i < evs->end(); i++) {
		if (series[firstDate.daysTo(i->getDate())] < i->getMagnitude()) {
			series[firstDate.daysTo(i->getDate())] = i->getMagnitude();
		}
	}

	return series;
}

double DataHandler::distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
