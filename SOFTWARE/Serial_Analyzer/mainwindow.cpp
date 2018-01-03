#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = new Console(NUM_AXES,DOWN_AXIS,UP_AXIS);
    console->setEnabled(false);

    consoleGyro = new Console(1,-180,180);
    consoleGyro->setEnabled(false);

    ui->TwoGraphsLayout->addWidget(console);

    serial = new QSerialPort(this);
    serialGyro = new QSerialPort(this);

    settings = new SettingsDialog("COM10","115200");
    settingsGyro = new SettingsDialog("COM4","115200");
    flagGyro = 0;

ui->actionConnect->setEnabled(true);
    ui->actionConnectGyro->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionDisconnectGyro->setEnabled(false);

    ui->actionQuit->setEnabled(true);

    ui->actionConfigure->setEnabled(true);
    ui->actionConfigureGyro->setEnabled(true);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    initActionsConnections();

    this->flag_can_save = 0;
    this->counter_patient = 0;

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(serialGyro, &QSerialPort::readyRead, this, &MainWindow::readDataGyro);
}


MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::openSerialPort(SettingsDialog *s,
                                QSerialPort *port,
                                Console* c,
                                QString msg)
{
    SettingsDialog::Settings p = s->settings();
    port->setPortName(p.name);
    port->setBaudRate(p.baudRate);
    port->setDataBits(p.dataBits);
    port->setParity(p.parity);
    port->setStopBits(p.stopBits);
    port->setFlowControl(p.flowControl);
    if (port->open(QIODevice::ReadWrite)) {
        c->setEnabled(true);
        c->setLocalEchoEnabled(p.localEchoEnabled);
        if(msg == "UH" ){
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            showStatusMessage(tr("Connected to UH %1 : %2, %3, %4, %5, %6")
                              .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                              .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
        } else{
            ui->actionConnectGyro->setEnabled(false);
            ui->actionDisconnectGyro->setEnabled(true);
            ui->actionConfigureGyro->setEnabled(false);
            showStatusMessage(tr("Connected to Gyro %1 : %2, %3, %4, %5, %6")
                              .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                              .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
        }

    } else {
        QMessageBox::critical(this, tr("Error"), port->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void MainWindow::closeSerialPort(QSerialPort* port, Console *c, QString msg)
{
    if (port->isOpen())
        port->close();
    c->setEnabled(false);
    if(msg == "UH"){
        ui->actionConnect->setEnabled(true);
        ui->actionDisconnect->setEnabled(false);
        ui->actionConfigure->setEnabled(true);
    }
    else{
        ui->actionConnectGyro->setEnabled(true);
        ui->actionDisconnectGyro->setEnabled(false);
        ui->actionConfigureGyro->setEnabled(true);
    }
    showStatusMessage(tr("Disconnected"));
}

void MainWindow::closeSerialPort()
{
    closeSerialPort(serial,console,"UH");
    closeSerialPort(serialGyro,consoleGyro,"Gyro");
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::readData()
{

    quint8 receivedAxis[16*4]; //4 pic, each 8 sensors, each 2 bytes value
    int packetSize = 16*4+5; //5 bytes overhead
    int nData = 8*4;  //4 pics,  8 sensors
    QVector<float> yVec = QVector<float>(nData);
    QVector<uint16_t> temp = QVector<uint16_t>(nData);

    /*********************************************************************************
     *                      Start to collect data inside the queue                   *
     *********************************************************************************/

    QByteArray data = serial->readAll();
    for(int i = 0;i<data.length();i++){
        //qDebug() << i << ": " << QString::number(data[i],16) << "\n";
        this->bytesQueue.enqueue(data[i]);
    }

    /*********************************************************************************
     *                      Start to decode data in the queue                        *
     *********************************************************************************/

    if(bytesQueue.length() >= packetSize)
    {
        for(int offset = 0;offset < bytesQueue.length() - packetSize;offset++)
        {
            if(bytesQueue[offset] == 0x00 &&
               bytesQueue[offset+1] == 0x00 &&
               bytesQueue[offset+packetSize-3] == 0x21 &&
               bytesQueue[offset+packetSize-2] == 0x21 &&
               bytesQueue[offset+packetSize-1] == 0x21 )
            {

    /*********************************************************************************
     *         User:Manually transfer bytes from queue to the container array        *
     *********************************************************************************/

                  receivedAxis[0] = bytesQueue[offset+2];
                  receivedAxis[1] = bytesQueue[offset+3];
                  receivedAxis[2] = bytesQueue[offset+4];
                  receivedAxis[3] = bytesQueue[offset+5];
                  receivedAxis[4] = bytesQueue[offset+6];
                  receivedAxis[5] = bytesQueue[offset+7];
                  receivedAxis[6] = bytesQueue[offset+8];
                  receivedAxis[7] = bytesQueue[offset+9];
                  receivedAxis[8] = bytesQueue[offset+10];
                  receivedAxis[9] = bytesQueue[offset+11];
                  receivedAxis[10] = bytesQueue[offset+12];
                  receivedAxis[11] = bytesQueue[offset+13];
                  receivedAxis[12] = bytesQueue[offset+14];
                  receivedAxis[13] = bytesQueue[offset+15];
                  receivedAxis[14] = bytesQueue[offset+16];
                  receivedAxis[15] = bytesQueue[offset+17];
                  receivedAxis[16] = bytesQueue[offset+18];
                  receivedAxis[17] = bytesQueue[offset+19];
                  receivedAxis[18] = bytesQueue[offset+20];
                  receivedAxis[19] = bytesQueue[offset+21];
                  receivedAxis[20] = bytesQueue[offset+22];
                  receivedAxis[21] = bytesQueue[offset+23];
                  receivedAxis[22] = bytesQueue[offset+24];
                  receivedAxis[23] = bytesQueue[offset+25];
                  receivedAxis[24] = bytesQueue[offset+26];
                  receivedAxis[25] = bytesQueue[offset+27];
                  receivedAxis[26] = bytesQueue[offset+28];
                  receivedAxis[27] = bytesQueue[offset+29];
                  receivedAxis[28] = bytesQueue[offset+30];
                  receivedAxis[29] = bytesQueue[offset+31];
                  receivedAxis[30] = bytesQueue[offset+32];
                  receivedAxis[31] = bytesQueue[offset+33];
                  receivedAxis[32] = bytesQueue[offset+34];
                  receivedAxis[33] = bytesQueue[offset+35];
                  receivedAxis[34] = bytesQueue[offset+36];
                  receivedAxis[35] = bytesQueue[offset+37];
                  receivedAxis[36] = bytesQueue[offset+38];
                  receivedAxis[37] = bytesQueue[offset+39];
                  receivedAxis[38] = bytesQueue[offset+40];
                  receivedAxis[39] = bytesQueue[offset+41];
                  receivedAxis[40] = bytesQueue[offset+42];
                  receivedAxis[41] = bytesQueue[offset+43];
                  receivedAxis[42] = bytesQueue[offset+44];
                  receivedAxis[43] = bytesQueue[offset+45];
                  receivedAxis[44] = bytesQueue[offset+46];
                  receivedAxis[45] = bytesQueue[offset+47];
                  receivedAxis[46] = bytesQueue[offset+48];
                  receivedAxis[47] = bytesQueue[offset+49];
                  receivedAxis[48] = bytesQueue[offset+50];
                  receivedAxis[49] = bytesQueue[offset+51];
                  receivedAxis[50] = bytesQueue[offset+52];
                  receivedAxis[51] = bytesQueue[offset+53];
                  receivedAxis[52] = bytesQueue[offset+54];
                  receivedAxis[53] = bytesQueue[offset+55];
                  receivedAxis[54] = bytesQueue[offset+56];
                  receivedAxis[55] = bytesQueue[offset+57];
                  receivedAxis[56] = bytesQueue[offset+58];
                  receivedAxis[57] = bytesQueue[offset+59];
                  receivedAxis[58] = bytesQueue[offset+60];
                  receivedAxis[59] = bytesQueue[offset+61];
                  receivedAxis[60] = bytesQueue[offset+62];
                  receivedAxis[61] = bytesQueue[offset+63];
                  receivedAxis[62] = bytesQueue[offset+64];
                  receivedAxis[63] = bytesQueue[offset+65];

                  for(int i = 0;i<nData*2;i++){
                      qDebug("%04x",receivedAxis[i]); // << receivedAxis[i];
                  }

                  qDebug() << "---------------------------";


                //Now save the values
                for(int i = 0;i<nData;i++)
                {
                    //The reinterpret cast is needed to convert the bytes into the real number
                    //Then we cast to float to pass the correct type to putData
                    //yVec[i] = (float)*reinterpret_cast<quint16*>(&receivedAxis[2*i]);
                    temp[i] = (((uint16_t) receivedAxis[2*i+1])<<8) + receivedAxis[2*i];
                    yVec[i] = (float) (temp[i]);
                    //qDebug() << yVec[i];

                }
                console->putData(yVec);
                qDebug() << yVec;

                //Delete from the queue everything that has been used so far
                for(int del = 0; del < offset + packetSize; del ++){
                    bytesQueue.dequeue();
                }
            }
        }
    }
}


void MainWindow::readDataGyro()
{
    char received[4];
    QVector3D axisRotation(0.0f,0.0f,1.0f);

    QByteArray data = serialGyro->readAll();
    for(int i = 0;i<data.length();i++){
        //qDebug() << i << ": " << QString::number(data[i],16) << "\n";
        this->bytesQueueGyro.enqueue(data[i]);
    }

    //stesso motivo di sotto, se è più piccolo del frame nn parte neanche il for
    if(bytesQueueGyro.length() >= (3+2+4) ){
        //tolgo la lunghezza del frame perchè nn ha senso e andrei outofbonds
        for(int offset = 0;offset <= bytesQueueGyro.length() - (3+2+4); offset++){
            if( bytesQueueGyro[offset]==0x00 &&
                bytesQueueGyro[offset+1] == 0x00 &&
                bytesQueueGyro[offset+6] == 0x21 &&
                bytesQueueGyro[offset+7] == 0x21 &&
                bytesQueueGyro[offset+8] == 0x21 ){

                    received[3] = bytesQueueGyro[offset+5];
                    received[2] = bytesQueueGyro[offset+4];
                    received[1] = bytesQueueGyro[offset+3];
                    received[0] = bytesQueueGyro[offset+2];

                    //Save the value
                    currentAngle[0] = *(reinterpret_cast<float*>(received));
                    //Plot the angle
                    qDebug() << currentAngle;
                    consoleGyro->putData(currentAngle);

                    //Clean the queue up to the offset + the frame
                    for(int i = 0;i<offset+(3+2+4);i++) bytesQueueGyro.dequeue();
            }
        }
    }
}

void MainWindow::openUH()
{
    openSerialPort(settings,serial,console,"UH");
}

void MainWindow::closeUH()
{
    closeSerialPort(serial,console,"UH");
}

void MainWindow::openGyro()
{
    openSerialPort(settingsGyro,serialGyro,consoleGyro,"Gyro");
}

void MainWindow::closeGyro()
{
    closeSerialPort(serialGyro,consoleGyro,"Gyro");
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}


void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openUH);
    connect(ui->actionConnectGyro, &QAction::triggered, this, &MainWindow::openGyro);

    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeUH);
    connect(ui->actionDisconnectGyro, &QAction::triggered, this, &MainWindow::closeGyro);

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->actionConfigure, &QAction::triggered, settings, &SettingsDialog::show);
    connect(ui->actionConfigureGyro, &QAction::triggered, settingsGyro, &SettingsDialog::show);

    //connect(ui->actionClear, &QAction::triggered, console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::broadcastTransformation()
{
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
