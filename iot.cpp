#include "iot.h"
#include "ui_iot.h"
#include <QSqlQuery>
#include <QString>
#include <widget.h>
Iot::Iot(QSqlDatabase *dbase,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Iot)
{
    ui->setupUi(this);
    db=dbase;
    timer= new QTimer;
    timer->start(TIMEOUT);

    connect(timer, &QTimer::timeout,this,&Iot::onTimeOut);
}

Iot::~Iot()
{
    delete ui;
}
void Iot::onTimeOut(){
    QSqlQuery query;
    query.exec("select * from HUMIandTEMP1");
    qDebug()<< query.value(0);
    while(query.next()){
        QString time=query.value(0).toString();
        int temp=query.value(1).toInt();
        int humi=query.value(2).toInt();
        ui->time1->setText(time);
        ui->temp1->display(temp);
        ui->humi1->display(humi);
    }
}


