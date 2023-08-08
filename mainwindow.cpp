#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	setWindowIcon(QIcon(":/images/k_2002.jpg"));
    setWindowTitle("KEITHLEY 2002");

	QFile *file = new QFile(this);
	stream.setDevice(file);
    connect (saveFileLineEdit,&QLineEdit::textChanged,file,&QFile::setFileName);

//---------------------настройка графика--------------------//
    ui->widget->setBackground(palette().window());//Заливка фона
    ui->widget->xAxis->grid()->setZeroLinePen(Qt::NoPen);//Скрытие нулевой линии (вертикальной)
    ui->widget->xAxis->grid()->setPen(QPen(Qt::black,1.0,Qt::DotLine));//Кисть для отрисовки основных линий (вертикальных)
    ui->widget->xAxis->grid()->setSubGridVisible(true);//Отображение побочных линий (вертикальных)
    ui->widget->xAxis->grid()->setSubGridPen(QPen(Qt::gray,0.5,Qt::DotLine));//Кисть для отрисовки побочных линий (вертикальных)
	ui->widget->yAxis->grid()->setZeroLinePen(Qt::NoPen);
	ui->widget->yAxis->grid()->setPen(QPen(Qt::black,1.0,Qt::DotLine));
	ui->widget->yAxis->grid()->setSubGridVisible(true);
    ui->widget->yAxis->grid()->setSubGridPen(QPen(Qt::gray,0.5,Qt::DotLine));
    ui->widget->axisRect()->setupFullAxesBox(true);//Дублирование основных осей побочными (верхняя ось дублирует нижнюю, правая - левую)
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);//Добавление возможности ручного масштабирования
    connect (ui->widget,&QCustomPlot::mouseRelease,[&](QMouseEvent *event) {
		if (event->button() == Qt::RightButton) {
			ui->widget->rescaleAxes();
			ui->widget->replot();
		}
	});
    ui->widget->legend->setVisible(true);
    curve = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);
    curve->setName("1ch");
	curve2 = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);
    curve2->setName("2ch");
    curve3 = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);
    curve3->setName("3ch");
    curve4 = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);
    curve4->setName("4ch");

    QPen pen(Qt::red);
	curve->setPen(pen);
    pen.setColor(Qt::blue);
	curve2->setPen(pen);
    pen.setColor(Qt::green);
    curve3->setPen(pen);
    pen.setColor(Qt::black);
    curve4->setPen(pen);

    curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    curve2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    curve3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    curve4->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
//---------------------end--------------------//

	deviceSpinBox->setMaximum(10);

	adresSpinBox->setMinimum(1);
    adresSpinBox->setMaximum(99);
	adresSpinBox2->setMinimum(1);
    adresSpinBox2->setMaximum(99);
    adresSpinBox3->setMinimum(1);
    adresSpinBox3->setMaximum(99);
    adresSpinBox4->setMinimum(1);
    adresSpinBox4->setMaximum(99);

    adresSpinBox->setValue(1);
    adresSpinBox2->setValue(2);
    adresSpinBox3->setValue(3);
    adresSpinBox4->setValue(4);

    freqComboBox->addItem("0.1");
    freqComboBox->addItem("0.5");
    freqComboBox->addItem("1");
    freqComboBox->addItem("2");
    freqComboBox->addItem("4");
    freqComboBox->addItem("5");
    freqComboBox->addItem("10");
    freqComboBox->setCurrentIndex(2);

    freqSpeedDoubleSpinBox->setValue(1);
    freqSpeedDoubleSpinBox->setEnabled(false);

	digitsSpinBox->setMinimum(4);
    digitsSpinBox->setMaximum(8);
    digitsSpinBox->setValue(8);

    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(1000000000);
    ui->spinBox->setSuffix("  min");

    saveFileLineEdit->setMaxLength(30);
    saveFileLineEdit->setPlaceholderText("test.txt");

    ui->checkBox->setChecked(true);


    dialog.setWindowTitle("Settings");
	dialog.setWindowIcon(QIcon(":/images/k_2002.jpg"));

	QStringList measurementStringList;
	measurementStringList << "DC Voltage" << "AC Voltage" << "DC Current" << "AC Current" << "Resistance 2" << "Resistance 4" << "FREQ" << "TEMP";
	measurementComboBox->addItems(measurementStringList);
	measurementComboBox2->addItems(measurementStringList);
    measurementComboBox3->addItems(measurementStringList);
    measurementComboBox4->addItems(measurementStringList);

	QFormLayout *parametersLayout = new QFormLayout;
	parametersLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    parametersLayout->addRow("Device:",deviceSpinBox);
    parametersLayout->addRow("1ch on/off",checkBox);
    parametersLayout->addRow("2ch on/off",checkBox2);
    parametersLayout->addRow("3ch on/off",checkBox3);
    parametersLayout->addRow("4ch on/off",checkBox4);
    parametersLayout->addRow("Address 1ch:",adresSpinBox);
    parametersLayout->addRow("Address 2ch:",adresSpinBox2);
    parametersLayout->addRow("Address 3ch:",adresSpinBox3);
    parametersLayout->addRow("Address 4ch:",adresSpinBox4);
    parametersLayout->addRow("Function 1ch:",measurementComboBox);
    parametersLayout->addRow("Function 2ch:",measurementComboBox2);
    parametersLayout->addRow("Function 3ch:",measurementComboBox3);
    parametersLayout->addRow("Function 4ch:",measurementComboBox4);
    parametersLayout->addRow("Freq: [Hz]",freqComboBox);
    parametersLayout->addRow("Speed:",freqSpeedDoubleSpinBox);
	parametersLayout->addRow("Digits:",digitsSpinBox);
	parametersLayout->addRow("File name:",saveFileLineEdit);

	QVBoxLayout *settingsLayout = new QVBoxLayout(&dialog);
	settingsLayout->setSizeConstraint(QLayout::SetFixedSize);
	settingsLayout->addLayout(parametersLayout);
	settingsLayout->addWidget(connectButton);

    ui->menuFile->addAction("Settings",&dialog,SLOT(show()));
    ui->menuFile->addAction("&Exit",this,SLOT(close()));

    ui->menuHelp->addAction("О программе...",this,SLOT(HELP()));

    connect (saveFileLineEdit,&QLineEdit::textChanged,this,&MainWindow::CHECK);
    connect (checkBox,&QCheckBox::clicked,this,&MainWindow::CHECK);
    connect (checkBox2,&QCheckBox::clicked,this,&MainWindow::CHECK);
    connect (checkBox3,&QCheckBox::clicked,this,&MainWindow::CHECK);
    connect (checkBox4,&QCheckBox::clicked,this,&MainWindow::CHECK);

    connect (connectButton,SIGNAL(clicked()),SLOT(OPEN()));
    connect (ui->pushButton,SIGNAL(clicked()),SLOT(START()));
    connect (ui->pushButton_2,SIGNAL(clicked()),SLOT(STOP()));
    connect (timerRead,SIGNAL(timeout()),SLOT(READ()));

	connectButton->setEnabled(false);
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setEnabled(false);
}
MainWindow::~MainWindow() {
    if (port->open()) port->write(":SYST:PRES");
    if (port2->open()) port2->write(":SYST:PRES");
    if (port3->open()) port3->write(":SYST:PRES");
    if (port4->open()) port4->write(":SYST:PRES");

    delete port;
    delete port2;
    delete port3;
    delete port4;

	delete ui;
}
void MainWindow::CHECK() {
    connectButton->setEnabled(!saveFileLineEdit->text().isEmpty() && (checkBox->isChecked() || checkBox2->isChecked() || checkBox3->isChecked() || checkBox4->isChecked()));
}
void MainWindow::OPEN() {
	bool_1k = false;
	bool_2k = false;
    bool_3k = false;
    bool_4k = false;

    if (checkBox->isChecked()) {
        port->setAddresses(adresSpinBox->value(),0,deviceSpinBox->value(),11);
        if (port->open()) {
            port->write("*IDN?");
            data.clear();
            if (port->read(data)) {
                port->close();
                bool_1k = true;

                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("DEVICE 1ch");
                msg->setText(data);
                msg->show();

                port->setAddresses(adresSpinBox->value(),0,deviceSpinBox->value(),15);
                port->open();

                port->write("*RST");

                if (measurementComboBox->currentIndex() == 0) {
                    port->write(":CONFigure:VOLTage:DC");
                    port->write(QString(":VOLTage:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port->write(":VOLTage:DC:NPLCycles:AUTO OFF");
                    port->write(QString(":VOLTage:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":VOLTage:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 1) {
                    port->write(":CONFigure:VOLTage:AC");
                    port->write(QString(":VOLTage:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":VOLTage:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 2) {
                    port->write(":CONFigure:CURRent:DC");
                    port->write(QString(":CURRent:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port->write(":CURRent:DC:NPLCycles:AUTO OFF");
                    port->write(QString(":CURRent:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":CURRent:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 3) {
                    port->write(":CONFigure:CURRent:AC");
                    port->write(QString(":CURRent:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":CURRent:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 4) {
                    port->write(":CONFigure:RESistance");
                    port->write(QString(":RESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port->write(":RESistance:NPLCycles:AUTO OFF");
                    port->write(QString(":RESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":RESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 5) {
                    port->write(":CONFigure:FRESistance");
                    port->write(QString(":FRESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port->write(":FRESistance:NPLCycles:AUTO OFF");
                    port->write(QString(":FRESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":FRESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 6) {
                    port->write(":CONFigure:FREQuency");
                    //str = QString(":FREQuency:DIGits %1").arg(digitsSpinBox->value());
                    //port->write(str.toUtf8());
                    //port->write(":FREQuency:DIGits:AUTO OFF");
                }
                if (measurementComboBox->currentIndex() == 7) {
                    port->write(":CONFigure:TEMPerature");
                    port->write(QString(":TEMPerature:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port->write(":TEMPerature:NPLCycles:AUTO OFF");
                    port->write(QString(":TEMPerature:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port->write(":TEMPerature:DIGits:AUTO OFF");
                }

                ui->widget->yAxis->setLabel(measurementComboBox->currentText().append(' ') + measurementComboBox2->currentText().append(' ') + measurementComboBox3->currentText().append(' ') + measurementComboBox4->currentText());
                ui->widget->xAxis->setLabel("TIME, [s]");

                ui->widget->replot();
                dialog.close();
            } else {
                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("Предупреждение");
                msg->setText("Мультиметр на канале 1 не найден \nпроверте параметры: ус-во и адрес");
                msg->show();
            }
        } else {
            QMessageBox *msg = new QMessageBox();
            msg->setWindowTitle("Предупреждение");
            msg->setText("Мультиметр на канале 1 не найден \nпроверте параметры: ус-во и адрес");
            msg->show();
        }
    }

    if (checkBox2->isChecked()) {
        port2->setAddresses(adresSpinBox2->value(),0,deviceSpinBox->value(),11);
        if (port2->open()) {
            port2->write("*IDN?");
            data.clear();
            if (port2->read(data)) {
                port2->close();
                bool_2k = true;

                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("DEVICE 2ch");
                msg->setText(data);
                msg->show();

                port2->setAddresses(adresSpinBox2->value(),0,deviceSpinBox->value(),15);
                port2->open();

                port2->write("*RST");

                if (measurementComboBox2->currentIndex() == 0) {
                    port2->write(":CONFigure:VOLTage:DC");
                    port2->write(QString(":VOLTage:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port2->write(":VOLTage:DC:NPLCycles:AUTO OFF");
                    port2->write(QString(":VOLTage:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":VOLTage:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 1) {
                    port2->write(":CONFigure:VOLTage:AC");
                    port2->write(QString(":VOLTage:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":VOLTage:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 2) {
                    port2->write(":CONFigure:CURRent:DC");
                    port2->write(QString(":CURRent:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port2->write(":CURRent:DC:NPLCycles:AUTO OFF");
                    port2->write(QString(":CURRent:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":CURRent:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 3) {
                    port2->write(":CONFigure:CURRent:AC");
                    port2->write(QString(":CURRent:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":CURRent:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 4) {
                    port2->write(":CONFigure:RESistance");
                    port2->write(QString(":RESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port2->write(":RESistance:NPLCycles:AUTO OFF");
                    port2->write(QString(":RESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":RESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 5) {
                    port2->write(":CONFigure:FRESistance");
                    port2->write(QString(":FRESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port2->write(":FRESistance:NPLCycles:AUTO OFF");
                    port2->write(QString(":FRESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":FRESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 6) {
                    port2->write(":CONFigure:FREQuency");
                    //str = QString(":FREQuency:DIGits %1").arg(digitsSpinBox->value());
                    //port2->write(str.toUtf8());
                    //port2->write(":FREQuency:DIGits:AUTO OFF");
                }
                if (measurementComboBox2->currentIndex() == 7) {
                    port2->write(":CONFigure:TEMPerature");
                    port2->write(QString(":TEMPerature:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port2->write(":TEMPerature:NPLCycles:AUTO OFF");
                    port2->write(QString(":TEMPerature:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port2->write(":TEMPerature:DIGits:AUTO OFF");
                }

                ui->widget->yAxis->setLabel(measurementComboBox->currentText().append(' ') + measurementComboBox2->currentText().append(' ') + measurementComboBox3->currentText().append(' ') + measurementComboBox4->currentText());
                ui->widget->xAxis->setLabel("TIME, [s]");

                ui->widget->replot();
                dialog.close();

            } else {
                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("Предупреждение");
                msg->setText("Мультиметр на канале 2 не найден \nпроверте параметры: ус-во и адрес");
                msg->show();
            }
        } else {
            QMessageBox *msg = new QMessageBox();
            msg->setWindowTitle("Предупреждение");
            msg->setText("Мультиметр на канале 2 не найден \nпроверте параметры: ус-во и адрес");
            msg->show();
        }
    }

    if (checkBox3->isChecked()) {
        port3->setAddresses(adresSpinBox3->value(),0,deviceSpinBox->value(),11);
        if (port3->open()) {
            port3->write("*IDN?");
            data.clear();
            if (port3->read(data)) {
                port3->close();
                bool_3k = true;

                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("DEVICE 3ch");
                msg->setText(data);
                msg->show();

                port3->setAddresses(adresSpinBox3->value(),0,deviceSpinBox->value(),15);
                port3->open();

                port3->write("*RST");

                if (measurementComboBox3->currentIndex() == 0) {
                    port3->write(":CONFigure:VOLTage:DC");
                    port3->write(QString(":VOLTage:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port3->write(":VOLTage:DC:NPLCycles:AUTO OFF");
                    port3->write(QString(":VOLTage:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":VOLTage:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 1) {
                    port3->write(":CONFigure:VOLTage:AC");
                    port3->write(QString(":VOLTage:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":VOLTage:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 2) {
                    port3->write(":CONFigure:CURRent:DC");
                    port3->write(QString(":CURRent:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port3->write(":CURRent:DC:NPLCycles:AUTO OFF");
                    port3->write(QString(":CURRent:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":CURRent:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 3) {
                    port3->write(":CONFigure:CURRent:AC");
                    port3->write(QString(":CURRent:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":CURRent:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 4) {
                    port3->write(":CONFigure:RESistance");
                    port3->write(QString(":RESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port3->write(":RESistance:NPLCycles:AUTO OFF");
                    port3->write(QString(":RESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":RESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 5) {
                    port3->write(":CONFigure:FRESistance");
                    port3->write(QString(":FRESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port3->write(":FRESistance:NPLCycles:AUTO OFF");
                    port3->write(QString(":FRESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":FRESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 6) {
                    port3->write(":CONFigure:FREQuency");
                    //str = QString(":FREQuency:DIGits %1").arg(digitsSpinBox->value());
                    //port3->write(str.toUtf8());
                    //port3->write(":FREQuency:DIGits:AUTO OFF");
                }
                if (measurementComboBox3->currentIndex() == 7) {
                    port3->write(":CONFigure:TEMPerature");
                    port3->write(QString(":TEMPerature:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port3->write(":TEMPerature:NPLCycles:AUTO OFF");
                    port3->write(QString(":TEMPerature:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port3->write(":TEMPerature:DIGits:AUTO OFF");
                }

                ui->widget->yAxis->setLabel(measurementComboBox->currentText().append(' ') + measurementComboBox2->currentText().append(' ') + measurementComboBox3->currentText().append(' ') + measurementComboBox4->currentText());
                ui->widget->xAxis->setLabel("TIME, [s]");

                ui->widget->replot();
                dialog.close();

            } else {
                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("Предупреждение");
                msg->setText("Мультиметр на канале 3 не найден \nпроверте параметры: ус-во и адрес");
                msg->show();
            }
        } else {
            QMessageBox *msg = new QMessageBox();
            msg->setWindowTitle("Предупреждение");
            msg->setText("Мультиметр на канале 3 не найден \nпроверте параметры: ус-во и адрес");
            msg->show();
        }
    }

    if (checkBox4->isChecked()) {
        port4->setAddresses(adresSpinBox4->value(),0,deviceSpinBox->value(),11);
        if (port4->open()) {
            port4->write("*IDN?");
            data.clear();
            if (port4->read(data)) {
                port4->close();
                bool_4k = true;

                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("DEVICE 4ch");
                msg->setText(data);
                msg->show();

                port4->setAddresses(adresSpinBox4->value(),0,deviceSpinBox->value(),15);
                port4->open();

                port4->write("*RST");

                if (measurementComboBox4->currentIndex() == 0) {
                    port4->write(":CONFigure:VOLTage:DC");
                    port4->write(QString(":VOLTage:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port4->write(":VOLTage:DC:NPLCycles:AUTO OFF");
                    port4->write(QString(":VOLTage:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":VOLTage:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 1) {
                    port4->write(":CONFigure:VOLTage:AC");
                    port4->write(QString(":VOLTage:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":VOLTage:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 2) {
                    port4->write(":CONFigure:CURRent:DC");
                    port4->write(QString(":CURRent:DC:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port4->write(":CURRent:DC:NPLCycles:AUTO OFF");
                    port4->write(QString(":CURRent:DC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":CURRent:DC:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 3) {
                    port4->write(":CONFigure:CURRent:AC");
                    port4->write(QString(":CURRent:AC:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":CURRent:AC:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 4) {
                    port4->write(":CONFigure:RESistance");
                    port4->write(QString(":RESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port4->write(":RESistance:NPLCycles:AUTO OFF");
                    port4->write(QString(":RESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":RESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 5) {
                    port4->write(":CONFigure:FRESistance");
                    port4->write(QString(":FRESistance:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port4->write(":FRESistance:NPLCycles:AUTO OFF");
                    port4->write(QString(":FRESistance:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":FRESistance:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 6) {
                    port4->write(":CONFigure:FREQuency");
                    //port4->write(QString(":FREQuency:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    //port4->write(":FREQuency:DIGits:AUTO OFF");
                }
                if (measurementComboBox4->currentIndex() == 7) {
                    port4->write(":CONFigure:TEMPerature");
                    port4->write(QString(":TEMPerature:NPLCycles %1").arg(freqSpeedDoubleSpinBox->value()).toUtf8());
                    port4->write(":TEMPerature:NPLCycles:AUTO OFF");
                    port4->write(QString(":TEMPerature:DIGits %1").arg(digitsSpinBox->value()).toUtf8());
                    port4->write(":TEMPerature:DIGits:AUTO OFF");
                }

                ui->widget->yAxis->setLabel(measurementComboBox->currentText().append(' ') + measurementComboBox2->currentText().append(' ') + measurementComboBox3->currentText().append(' ') + measurementComboBox4->currentText());
                ui->widget->xAxis->setLabel("TIME, [s]");

                ui->widget->replot();
                dialog.close();

            } else {
                QMessageBox *msg = new QMessageBox();
                msg->setWindowTitle("Предупреждение");
                msg->setText("Мультиметр на канале 4 не найден \nпроверте параметры: ус-во и адрес");
                msg->show();
            }
        } else {
            QMessageBox *msg = new QMessageBox();
            msg->setWindowTitle("Предупреждение");
            msg->setText("Мультиметр на канале 4 не найден \nпроверте параметры: ус-во и адрес");
            msg->show();
        }
    }

    ui->pushButton ->setEnabled(bool_1k || bool_2k || bool_3k || bool_4k);
}
void MainWindow::START() {
    if (bool_1k || bool_2k || bool_3k || bool_4k) {
        ui->pushButton->setEnabled(false);
		ui->pushButton_2->setEnabled(true);
		ui->menuBar->setEnabled(false);
        curve->data().data()->clear();
        curve2->data().data()->clear();
        curve3->data().data()->clear();
        curve4->data().data()->clear();

        qobject_cast<QFile*>(stream.device())->open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
        if (bool_1k) port->write(":DISP:ENAB OFF");
        if (bool_2k) port2->write(":DISP:ENAB OFF");
        if (bool_3k) port3->write(":DISP:ENAB OFF");
        if (bool_4k) port4->write(":DISP:ENAB OFF");

        timeStart.restart();
        timerRead->setTimerType(Qt::PreciseTimer);
        switch (freqComboBox->currentIndex()) {
        case 0:
            timerRead->start(10000);
            break;
        case 1:
            timerRead->start(5000);
            break;
        case 2:
            timerRead->start(1000);
            break;
        case 3:
            timerRead->start(500);
            break;
        case 4:
            timerRead->start(250);
            break;
        case 5:
            timerRead->start(200);
            break;
        case 6:
            timerRead->start(100);
            break;
        }

        QDateTime startDateTime;
        QDateTime endDateTime;
        startDateTime = QDateTime::currentDateTime();
        endDateTime = startDateTime.addSecs(ui->spinBox->value() * 60);
        endBool = true;
        while (QDateTime::currentDateTime() < endDateTime && endBool) {
            endDateTime = startDateTime.addSecs(ui->spinBox->value() * 60);
            qApp->processEvents();
        }
        if (endBool)
            STOP();
        ui->pushButton->setEnabled(true);
	}
}
void MainWindow::STOP() {
    endBool = false;
	ui->menuBar->setEnabled(true);
	timerRead->stop();
    qobject_cast<QFile*>(stream.device())->flush();
	qobject_cast<QFile*>(stream.device())->close();
    if (bool_1k) port->write(":DISP:ENAB ON");
    if (bool_2k) port2->write(":DISP:ENAB ON");
    if (bool_3k) port3->write(":DISP:ENAB ON");
    if (bool_4k) port4->write(":DISP:ENAB ON");
}
void MainWindow::READ() {
    if (bool_1k) port->write(":READ?");
    if (bool_2k) port2->write(":READ?");
    if (bool_3k) port3->write(":READ?");
    if (bool_4k) port4->write(":READ?");

    if (bool_1k) {
        data.clear();
        port->read(data);
        stream << QString("%1").arg(QString::number(data.simplified().toDouble(),'f',digitsSpinBox->value())).append(' ');
        curve->addData(timeStart.elapsed() / 1000.0,data.simplified().toDouble());
    }
    if (bool_2k) {
        data.clear();
        port2->read(data);
        stream << QString("%1").arg(QString::number(data.simplified().toDouble(),'f',digitsSpinBox->value())).append(' ');
        curve2->addData(timeStart.elapsed() / 1000.0,data.simplified().toDouble());
    }
    if (bool_3k) {
        data.clear();
        port3->read(data);
        stream << QString("%1").arg(QString::number(data.simplified().toDouble(),'f',digitsSpinBox->value())).append(' ');
        curve3->addData(timeStart.elapsed() / 1000.0,data.simplified().toDouble());
    }
    if (bool_4k) {
        data.clear();
        port4->read(data);
        stream << QString("%1").arg(QString::number(data.simplified().toDouble(),'f',digitsSpinBox->value())).append(' ');
        curve4->addData(timeStart.elapsed() / 1000.0,data.simplified().toDouble());
    }

    if (ui->checkBox->isChecked()) {
        ui->widget->xAxis->setRange(timeStart.elapsed() / 1000.0,timeStart.elapsed() / 1000.0,Qt::AlignRight);
        ui->widget->replot();
    }

    if (bool_1k || bool_2k || bool_3k || bool_4k)
        stream << QString("%1 %2").arg(timeStart.currentTime().toString("hh:mm:ss:zzz")).arg(QString::number(timeStart.elapsed() / 1000.0,'f',3)) << endl;
}
