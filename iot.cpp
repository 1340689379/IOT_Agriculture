#include "iot.h"
#include "ui_iot.h"
#include <QSqlQuery>
#include <QString>
#include <login.h>
#include <QMessageBox>
#include <QSqlError>
Iot::Iot(QSqlDatabase *dbase,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Iot)
{
    ui->setupUi(this);
    QMessageBox msgBox;
    //db=dbase;
    timer= new QTimer;
    timer->start(TIMEOUT);



    db=QSqlDatabase::addDatabase("QODBC","connection1");

    db.setHostName("120.25.3.98");
    db.setPort(3306);
    db.setDatabaseName("Mysql1");
    db.setUserName("IoTagriDB");
    db.setPassword("200243");


    bool ok = db.open();
    if (ok){
        msgBox.setText( "link success");
    }
    else {
        msgBox.setText( "link failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
    msgBox.exec();

    dblocal=QSqlDatabase::addDatabase("QODBC","connection2");
    dblocal.setHostName("127.0.0.1");
    dblocal.setPort(3306);
    dblocal.setDatabaseName("Mysql");
    dblocal.setUserName("root");
    dblocal.setPassword("root");
    ok = dblocal.open();
    if (ok){
        msgBox.setText( "link success");
    }
    else {
        msgBox.setText( "link failed");
        qDebug()<<"error open database because"<<dblocal.lastError().text();
    }
    msgBox.exec();

    connect(timer, &QTimer::timeout,this,&Iot::onTimeOut);
}

Iot::~Iot()
{
    delete ui;
}
void Iot::onTimeOut(){
    // if (db->open()){
    // }
    // else {
    //     qDebug()<<"error open database because"<<db->lastError().text();
    // }
    QSqlQuery query(db);
    //QSqlQuery query;
    QSqlQuery queryl(dblocal);
    int ok;
    //QSqlQuery queryl(*dblocal);
    queryl.exec("delete from HUMIandTEMP1");
    query.exec("select * from HUMIandTEMP1");
    while(query.next()){
        QString time=query.value(0).toString();
        int temp=query.value(1).toInt();
        int humi=query.value(2).toInt();
        ui->time1->setText(time);
        ui->temp1->display(temp);
        ui->humi1->display(humi);
        queryl.prepare("INSERT INTO HUMIandTEMP1(timeset,humi,temp) "
                       "VALUES(:timeset,:humi,:temp)");
        queryl.bindValue(":timeset", time);
        queryl.bindValue(":humi", query.value(1).toString());
        queryl.bindValue(":temp", query.value(2).toString());
        ok=queryl.exec();
        if (!ok) {
            qDebug() << "Insert data into local database error: " << queryl.lastError().text();
        }
        else{
            //qDebug()<< ok;
        }

    }

    queryl.exec("delete from HUMIandTEMP2");
    query.exec("select * from HUMIandTEMP2");
    while(query.next()){
        QString time=query.value(0).toString();
        int temp=query.value(1).toInt();
        int humi=query.value(2).toInt();
        ui->time2->setText(time);
        ui->temp2->display(temp);
        ui->humi2->display(humi);

        queryl.prepare("INSERT INTO HUMIandTEMP2(timeset,humi,temp) "
                       "VALUES(:timeset,:humi,:temp)");
        queryl.bindValue(":timeset", time);
        queryl.bindValue(":humi", query.value(1).toString());
        queryl.bindValue(":temp", query.value(2).toString());
        ok=queryl.exec();
        if (!ok) {
            qDebug() << "Insert data into local database error: " << queryl.lastError().text();
        }
        else{
            //qDebug()<< ok;
        }
    }

    // queryl.prepare("INSERT OR REPLACE INTO HUMIandTEMP2(timeset,humi,temp)" "VALUES(:timeset,:humi,:temp)");
    // queryl.bindValue(":timeset", query.value("timeset"));
    // queryl.bindValue(":humi", query.value("humi"));
    // queryl.bindValue(":temp", query.value("temp"));
    queryl.exec("delete from HUMIandTEMP3");
    query.exec("select * from HUMIandTEMP3");
    while(query.next()){
        QString time=query.value(0).toString();
        int temp=query.value(1).toInt();
        int humi=query.value(2).toInt();
        ui->time3->setText(time);
        ui->temp3->display(temp);
        ui->humi3->display(humi);
        queryl.prepare("INSERT INTO HUMIandTEMP3(timeset,humi,temp) "
                       "VALUES(:timeset,:humi,:temp)");
        queryl.bindValue(":timeset", time);
        queryl.bindValue(":humi", query.value(1).toString());
        queryl.bindValue(":temp", query.value(2).toString());
        ok=queryl.exec();
        if (!ok) {
            qDebug() << "Insert data into local database error: " << queryl.lastError().text();
        }
        else{
            //qDebug()<< ok;
        }
    }

    queryl.exec("delete from CO2");
    query.exec("select * from CO2");
    while(query.next()){
        QString time=query.value(0).toString();
        int CO2=query.value(1).toInt();
        ui->time4->setText(time);
        ui->co2->display(CO2);
        queryl.prepare("INSERT INTO CO2(timeset,CO2ct) "
                       "VALUES(:timeset,:CO2)");
        queryl.bindValue(":timeset", time);
        queryl.bindValue(":CO2", query.value(1).toString());
        ok=queryl.exec();
        if (!ok) {
            qDebug() << "Insert data into local database error: " << queryl.lastError().text();
        }
        else{
            //qDebug()<< ok;
        }
    }
    queryl.exec("delete from Light");
    query.exec("select * from Light");
    while(query.next()){
        QString time=query.value(0).toString();
        int light=query.value(1).toInt();
        ui->time5->setText(time);
        ui->light->display(light);
        queryl.prepare("INSERT INTO Light(timeset,light) "
                       "VALUES(:timeset,:light)");
        queryl.bindValue(":timeset", time);
        queryl.bindValue(":light", query.value(1).toString());
        ok=queryl.exec();
        if (!ok) {
            qDebug() << "Insert data into local database error: " << queryl.lastError().text();
        }
        else{
            //qDebug()<< ok;
        }
    }
    //db->close();
}


