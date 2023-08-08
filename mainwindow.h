#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GPIBPort.h"

#include <QtWidgets>
#include "qcustomplot.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
	void HELP() {
		QMessageBox *msg = new QMessageBox();
        msg->setWindowTitle("Keithley");
		msg->setWindowIcon(QIcon(":/images/k_2002.jpg"));
        msg->setText("Version 1.3.2, 2017      ");
		msg->show();
	}
	void CHECK();
	void OPEN();
	void START();
	void STOP();
	void READ();

private:
    Ui::MainWindow *ui;

    GPIBPort *port = new GPIBPort();
    GPIBPort *port2 = new GPIBPort();
    GPIBPort *port3 = new GPIBPort();
    GPIBPort *port4 = new GPIBPort();

	QDialog dialog;
	QSpinBox *deviceSpinBox = new QSpinBox();
    QCheckBox *checkBox = new QCheckBox();
    QCheckBox *checkBox2 = new QCheckBox();
    QCheckBox *checkBox3 = new QCheckBox();
    QCheckBox *checkBox4 = new QCheckBox();
	QSpinBox *adresSpinBox = new QSpinBox();
	QSpinBox *adresSpinBox2 = new QSpinBox();
    QSpinBox *adresSpinBox3 = new QSpinBox();
    QSpinBox *adresSpinBox4 = new QSpinBox();
	QComboBox *measurementComboBox = new QComboBox();
	QComboBox *measurementComboBox2 = new QComboBox();
    QComboBox *measurementComboBox3 = new QComboBox();
    QComboBox *measurementComboBox4 = new QComboBox();
    QComboBox *freqComboBox = new QComboBox();
    QDoubleSpinBox *freqSpeedDoubleSpinBox = new QDoubleSpinBox();
	QSpinBox *digitsSpinBox = new QSpinBox();
	QLineEdit *saveFileLineEdit = new QLineEdit();
	QPushButton *connectButton = new QPushButton("&connect");

	QCPCurve *curve;
	QCPCurve *curve2;
    QCPCurve *curve3;
    QCPCurve *curve4;

    QTimer *timerRead = new QTimer();
	QTime timeStart;
	QTextStream stream;

    bool bool_1k,bool_2k,bool_3k,bool_4k;
    QByteArray data;
    bool endBool;
};
#endif // MAINWINDOW_H
