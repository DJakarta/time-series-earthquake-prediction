#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <datahandler.h>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	DataHandler *dataH;

	QCPBars *plottedBars, *highlightBars;
	void configurePlots();

	void changePlottedEvents(QDate d1, QDate d2, double mag1, double mag2);
	void changePredictedEvents(QDate d1, QDate d2, double mag1, double mag2);

	void changeHighlightedEvent(Event ev);

	void forecast();

public slots:
	void mapMouseMove(QMouseEvent *event);
	void plot1MouseMove(QMouseEvent *event);

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
