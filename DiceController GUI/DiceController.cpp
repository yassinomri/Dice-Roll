#include "DiceController.h"

#include <QMessageBox>
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

DiceController::DiceController(QWidget *parent)
    : QMainWindow(parent)
    , serial(new QSerialPort(this))
    , pollTimer(new QTimer(this))
{
    setupUi();

    //initialize serial port
    initializeUsbPort();

    updatePortList();

    //connect serial port
    connect(pollTimer, &QTimer::timeout, this, &DiceController::handleUsbData);
    pollTimer->start(50); // Poll every 50ms

    //update port list
    connect(refreshButton, &QPushButton::clicked, this, &DiceController::updatePortList);

}


DiceController::~DiceController()
{
    if (serial->isOpen()) {
        serial->close();
    }
}

void DiceController::setupUi()
{
    //set window properties and layouts
    resize(400, 300);
    setWindowTitle("Digital Dice Controller");
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *portLayout = new QHBoxLayout();
    QLabel *portLabel = new QLabel("Port:", this);
    portComboBox = new QComboBox(this);
    refreshButton = new QPushButton("Refresh", this);
    connectButton = new QPushButton("Connect", this);
    portLayout->addWidget(portLabel);
    portLayout->addWidget(portComboBox);
    portLayout->addWidget(refreshButton);
    portLayout->addWidget(connectButton);

    // create roll button
    rollButton = new QPushButton("Roll Dice!", this);
    rollButton->setEnabled(false);
    rollButton->setMinimumHeight(100);
    QFont buttonFont = rollButton->font();
    buttonFont.setPointSize(16);
    buttonFont.setBold(true);
    rollButton->setFont(buttonFont);

    // create last roll label
    lastRollLabel = new QLabel("Last Roll: -", this);
    QFont labelFont = lastRollLabel->font();
    labelFont.setPointSize(14);
    lastRollLabel->setFont(labelFont);
    lastRollLabel->setAlignment(Qt::AlignCenter);


    //add status bar
    statusBar()->showMessage("Not Connected");

   // add widgets to main layout
    mainLayout->addLayout(portLayout);
    mainLayout->addWidget(rollButton);
    mainLayout->addWidget(lastRollLabel);

    // set central widget
    setCentralWidget(centralWidget);

    //connect button signal
    connect(rollButton, &QPushButton::clicked, this, &DiceController::on_rollButton_clicked);
    connect(connectButton, &QPushButton::clicked, this, &DiceController::on_connectButton_clicked);
}

void DiceController::updatePortList()
{
    portComboBox->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        portComboBox->addItem(port.portName());
    }
}

void DiceController::initializeUsbPort()
{
    serial->setPortName(portComboBox->currentText());
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        connectButton->setText("Disconnect");
        statusBar()->showMessage("Connected to " + serial->portName());
        rollButton->setEnabled(true);
    } else {
        QMessageBox::critical(this, "Error", "Cannot open serial port!");
    }
}

void DiceController::on_connectButton_clicked()
{
    if (!serial->isOpen()) {
        initializeUsbPort();
    } else {
        serial->close();
        connectButton->setText("Connect");
        statusBar()->showMessage("Disconnected");
        rollButton->setEnabled(false);
    }
}

void DiceController::on_rollButton_clicked()
{
    sendRollCommand();
    rollButton->setEnabled(false);        //disable until roll is complete
    QTimer::singleShot(1500, this, [this]() {
        rollButton->setEnabled(true);  // delay before re-enabling the roll button
    });
}

void DiceController::sendRollCommand()
{
    if (serial->isOpen()) {
        qDebug() << "Sending roll command...";
        serial->write("R");
        //small delay to ensure command is sent
        serial->waitForBytesWritten(100);
        qDebug() << "Command sent";
    } else {
        qDebug() << "Serial port not open!";
    }
}

void DiceController::handleUsbData()
{
    if (serial->bytesAvailable()) {
        QByteArray data = serial->readAll();
        for (const auto& byte : data) {
            //update last roll display if it's a number
            if (byte >= 1 && byte <= 6) {
                lastRollLabel->setText("Last Roll: " + QString::number(byte));
            }
        }
    }
}
