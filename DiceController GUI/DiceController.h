#ifndef DICECONTROLLER_H
#define DICECONTROLLER_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QTimer>
#include <QQueue>

class DiceController : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiceController(QWidget *parent = nullptr);
    ~DiceController();

private slots:
    void on_rollButton_clicked();
    void on_connectButton_clicked();
    void handleUsbData();
    void updatePortList();

private:
    //serial port
    QSerialPort *serial;
    QTimer *pollTimer;
    QQueue<quint8> receiveQueue;


    //UI elements
    QComboBox *portComboBox;
    QPushButton *connectButton;
    QPushButton *refreshButton;
    QPushButton *rollButton;
    QLabel *lastRollLabel;

    void setupUi();
    void initializeUsbPort();
    void sendRollCommand();
};
#endif // DICECONTROLLER_H
