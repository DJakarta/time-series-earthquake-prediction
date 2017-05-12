#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qcustomplot.h>
#include <holt.h>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	//settings
	string fileName = "events.xml";

	//load data
	dataH = new DataHandler();
	dataH->parseXML(fileName);
	dataH->sortByDateAsc();
	dataH->firstDate = DataHandler::getEventsFirstDate(dataH->events);
	dataH->lastDate = DataHandler::getEventsLastDate(dataH->events);

	//set the plots
	configurePlots();

	//plot initial data
	changePlottedEvents(dataH->firstDate, dataH->lastDate, 0, 10);
	changePredictedEvents(dataH->firstDate, dataH->lastDate, 0, 10);

	//temp tests

	//connects
	connect(ui->map, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mapMouseMove(QMouseEvent*)));
	connect(ui->plot1, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plot1MouseMove(QMouseEvent*)));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::configurePlots() {
	//plot 1
	ui->plot1->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
	ui->plot1->axisRect()->setRangeZoom(Qt::Horizontal);
	ui->plot1->axisRect()->setRangeDrag(Qt::Horizontal);

	QColor barColor(120, 120, 255);

	plottedBars = new QCPBars(ui->plot1->xAxis, ui->plot1->yAxis);
	plottedBars->setAntialiased(false);
	plottedBars->setName("Evenimentele produse filtrate");
	plottedBars->setPen(QPen(barColor));
	plottedBars->setBrush(barColor);

	QColor highlightColor(255, 200, 120);

	highlightBars = new QCPBars(ui->plot1->xAxis, ui->plot1->yAxis);
	highlightBars->setAntialiased(false);
	highlightBars->setName("Evenimentul selectat");
	highlightBars->setPen(QPen(highlightColor));
	highlightBars->setBrush(highlightColor);

	QBrush *backgroundBrush = new QBrush(QColor(0, 0, 0));
	ui->plot1->setBackground(*backgroundBrush);

	QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
	dateTicker->setDateTimeFormat("dd.MM.yyyy");
	ui->plot1->xAxis->setTicker(dateTicker);

	QColor axisColor(70, 70, 70);
	QPen *axisPen = new QPen(axisColor);
	ui->plot1->xAxis->setBasePen(*axisPen);
	ui->plot1->xAxis->setTickPen(*axisPen);
	ui->plot1->xAxis->setSubTickPen(*axisPen);
	ui->plot1->xAxis->setTickLabelColor(axisColor);

	ui->plot1->yAxis->setBasePen(*axisPen);
	ui->plot1->yAxis->setTickPen(*axisPen);
	ui->plot1->yAxis->setSubTickPen(*axisPen);
	ui->plot1->yAxis->setTickLabelColor(axisColor);

	ui->plot1->xAxis->grid()->setVisible(false);
	ui->plot1->yAxis->grid()->setVisible(false);

	ui->plot1->xAxis->setRange(dataH->zeroDate.daysTo(dataH->firstDate) * 3600 * 24,
							   dataH->zeroDate.daysTo(dataH->lastDate) * 3600 * 24);
	ui->plot1->yAxis->setRange(0, 8);

	//plot 2
	ui->plot2->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
	ui->plot2->axisRect()->setRangeZoom(Qt::Horizontal);
	ui->plot2->axisRect()->setRangeDrag(Qt::Horizontal);
	ui->plot2->setBackground(*backgroundBrush);

	ui->plot2->xAxis->setTicker(dateTicker);

	ui->plot2->xAxis->setBasePen(*axisPen);
	ui->plot2->xAxis->setTickPen(*axisPen);
	ui->plot2->xAxis->setSubTickPen(*axisPen);
	ui->plot2->xAxis->setTickLabelColor(axisColor);

	ui->plot2->yAxis->setBasePen(*axisPen);
	ui->plot2->yAxis->setTickPen(*axisPen);
	ui->plot2->yAxis->setSubTickPen(*axisPen);
	ui->plot2->yAxis->setTickLabelColor(axisColor);

	ui->plot2->xAxis->grid()->setVisible(false);
	ui->plot2->yAxis->grid()->setVisible(false);

	ui->plot2->xAxis->setRange(dataH->zeroDate.daysTo(dataH->firstDate) * 3600 * 24,
							   dataH->zeroDate.daysTo(dataH->lastDate) * 3600 * 24);
	ui->plot2->yAxis->setRange(0, 8);

	//map plot
	ui->map->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
	ui->map->xAxis->setVisible(false);
	ui->map->yAxis->setVisible(false);
	ui->map->axisRect()->setAutoMargins(QCP::msNone);
	ui->map->axisRect()->setMargins(QMargins(0, 0, 0, 0));

	//QPixmap map(QString("1-43,5-48,5-20-30.png"));
	//ui->map->setBackground(map, true, Qt::KeepAspectRatioByExpanding);

	QCPItemPixmap *pixmap=new QCPItemPixmap(ui->map);
	pixmap->setPixmap(QPixmap("map2.jpg"));
	pixmap->setScaled(true);
	pixmap->topLeft->setCoords(20, 48.5);
	pixmap->bottomRight->setCoords(30, 43.5);

	ui->map->xAxis->setRange(20, 30);
	ui->map->yAxis->setRange(43.5, 48.5);

	ui->map->addGraph(ui->map->xAxis, ui->map->yAxis);
	ui->map->graph(0)->setScatterStyle(QCPScatterStyle(QPixmap("highEvent.png")));

	ui->map->addGraph(ui->map->xAxis, ui->map->yAxis);
	ui->map->graph(1)->setScatterStyle(QCPScatterStyle(QPixmap("event.png")));
	QPen emptyPen;
	emptyPen.setStyle(Qt::DashLine);
	emptyPen.setWidth(0);
	emptyPen.setColor(QColor(180, 180, 180, 0));
	ui->map->graph(1)->setPen(emptyPen);
}

void MainWindow::changePlottedEvents(QDate d1, QDate d2, double mag1, double mag2) {
	dataH->plottedEventsStartDate = d1;
	dataH->plottedEventsEndDate = d2;
	dataH->plottedEventsMinMagnitude = mag1;
	dataH->plottedEventsMaxMagnitude = mag2;

	dataH->plottedEvents = DataHandler::getFilteredEvents(dataH->events, d1, d2);
	dataH->plottedEvents = DataHandler::getFilteredEvents(dataH->plottedEvents, mag1, mag2);

	dataH->plottedEventsX = DataHandler::getEventsX(dataH->plottedEvents);
	dataH->plottedEventsY = DataHandler::getEventsY(dataH->plottedEvents);

	plottedBars->setData(*dataH->plottedEventsX, *dataH->plottedEventsY);

	int topEventsNo = 25;
	dataH->topEvents = DataHandler::getFilteredEvents(dataH->plottedEvents, false, false);
	DataHandler::sortEventsByMagnitudeDesc(dataH->topEvents);
	dataH->topEvents->remove(topEventsNo, dataH->topEvents->length() - topEventsNo);
	dataH->topEventsMapX = DataHandler::getEventsMapX(dataH->topEvents);
	dataH->topEventsMapY = DataHandler::getEventsMapY(dataH->topEvents);

	ui->map->graph(1)->setData(*dataH->topEventsMapX, *dataH->topEventsMapY);

	qDebug() << "Plotted events changed!";
}

void MainWindow::changePredictedEvents(QDate d1, QDate d2, double mag1, double mag2) {
	dataH->predictedEventsStartDate = d1;
	dataH->predictedEventsEndDate = d2;
	dataH->predictedEventsMinMagnitude = mag1;
	dataH->predictedEventsMaxMagnitude = mag2;

	forecast();

	dataH->predictedEvents = DataHandler::getFilteredEvents(dataH->plottedEvents, d1, d2);
	dataH->predictedEvents = DataHandler::getFilteredEvents(dataH->predictedEvents, mag1, mag2);

	dataH->predictedEventsX = DataHandler::getEventsX(dataH->predictedEvents);
	dataH->predictedEventsY = DataHandler::getEventsY(dataH->predictedEvents);

	qDebug() << "Predicted events changed!";
}

void MainWindow::changeHighlightedEvent(Event ev) {
	ui->highDate->setText(ev.getDate().toString("dd.MM.yyyy"));
	ui->highMag->setText(QString::asprintf("%.1lf", ev.getMagnitude()));
	ui->highLat->setText(QString::asprintf("%.4lf", ev.getLatitude()));
	ui->highLong->setText(QString::asprintf("%.4lf", ev.getLongitude()));
	ui->highDepth->setText(QString::asprintf("%.1lf", ev.getDepth()/1000));

	QVector<double> mapHighlightX, mapHighlightY;
	mapHighlightX.append(ev.getLongitude());
	mapHighlightY.append(ev.getLatitude());
	ui->map->graph(0)->setData(mapHighlightX, mapHighlightY);
	ui->map->replot();

	QVector<double> highlightX, highlightY;
	highlightX.append(dataH->zeroDate.daysTo(ev.getDate()) * 3600 * 24);
	highlightY.append(ev.getMagnitude());
	highlightBars->setData(highlightX, highlightY);
	ui->plot1->replot();
}

void MainWindow::forecast() {
	ofstream fout("arima.out");
	qDebug() << "Forecast in progress!";
	int i, n;
	double *series = DataHandler::getEventsTimeSeries(dataH->plottedEvents, &n);
	for (i = 0; i < n; i++) {
		fout << series[i] << " ";
	}
	qDebug() << "Forecast completed.";
}

void MainWindow::mapMouseMove(QMouseEvent *event) {
	double mouseLatitude = ui->map->yAxis->pixelToCoord(event->y());
	double mouseLongitude = ui->map->xAxis->pixelToCoord(event->x());

	Event closest = DataHandler::getEventsClosestMapEvent(dataH->topEvents, mouseLatitude, mouseLongitude);

	changeHighlightedEvent(closest);
}

void MainWindow::plot1MouseMove(QMouseEvent *event) {
	QDate mouseDate = dataH->zeroDate.addDays(ui->plot1->xAxis->pixelToCoord(event->x()) / (3600 * 24));

	Event closest = DataHandler::getEventsClosestTimeEvent(dataH->plottedEvents, mouseDate);

	changeHighlightedEvent(closest);
}
