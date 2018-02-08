/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>

#include <QQueue>
#include <QVector>
#include <QFile>
#include <QTextStream>

//#define NCHANNEL 8
#define NUM_AXES 32
#define UP_AXIS 3000
#define DOWN_AXIS 1000
//#define CHECK_FRAME(buf) ((buf[0] == 0x00) && (buf[5] == 0x21) && (buf[6] == 0x21) && (buf[7] == 0x21) )

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void about();


    void readData();
    void readDataGyro();

    void openUH();
    void closeUH();

    void openGyro();
    void closeGyro();

    void save_on();
    void save_off();

    void handleError(QSerialPort::SerialPortError error);

    void broadcastTransformation();

private:
    /*Connects the required signals and slots*/
    void initActionsConnections();
    /*Open the serial port "port" relative to "msg" using the settings in "s", enabling the console "c"*/
    void openSerialPort(SettingsDialog *s, QSerialPort *port, Console *c, QString msg);
    /*Close the serial port "port" relative to "msg" and disable the console "c"*/
    void closeSerialPort(QSerialPort *port, Console *c, QString msg);
    //in case of an error both the ports must be closed
    void closeSerialPort();

private:
    void showStatusMessage(const QString &message);

    int flagGyro;
    int flagSave;
    typedef enum label_type {CLOSE, OPEN, UP, DOWN, LEFT, RIGHT} labelt;
    labelt label;
    typedef struct {
        int cntclose;
        int cntopen;
        int cntup;
        int cntdown;
        int cntleft;
        int cntright;
    } cnttype;

    cnttype cntMovements = {0};

    int n_saved;

    Ui::MainWindow *ui;
    QLabel *status;
    Console *console;
    Console *consoleGyro;
    QFile *savedData;
    QTextStream *out;
    SettingsDialog *settings;
    SettingsDialog *settingsGyro;
    QSerialPort *serial;
    QSerialPort *serialGyro;    
    QQueue<quint8> bytesQueue;
    QQueue<quint8> bytesQueueGyro;

    //Fix this thing with a template, we need an instance of putData in the console
    //That is able to take any kind of data.
    //QVector<float> yVec = QVector<float>(NCHANNEL);
    QVector<float> currentAngle = QVector<float>(1);

    int flag_can_save;
    int counter_patient;
    QString filename;
    QFile *recording;


};

#endif // MAINWINDOW_H
