#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QMessageBox msgBox;

    QSqlDatabase d=QSqlDatabase::addDatabase("QODBC");
    db=&d;

    db->setHostName("120.25.3.98");
    db->setPort(3306);
    db->setDatabaseName("Mysql1");
    db->setUserName("IoTagriDB");
    db->setPassword("200243");


    bool ok = db->open();
    if (ok){
        msgBox.setText( "link success");
    }
    else {
        msgBox.setText( "link failed");
        qDebug()<<"error open database because"<<db->lastError().text();
    }
    msgBox.exec();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_insert_clicked()
{
    QString username =ui->idLineEdit->text();
    QString password =ui->pdLineEdit->text();

    QString sql= QString("insert into User values('%1', '%2');").arg(username).arg(password);
    QSqlQuery query;
    if(query.exec(sql))
    {
        QMessageBox::information(this,"注册提示","注册成功");
    }
    else{
        QMessageBox::information(this,"注册提示","注册失败");
    }
}





void Widget::on_login_clicked()
{
    QSqlQuery query;
    QString username =ui->idLineEdit->text();
    QString password =ui->pdLineEdit->text();

    query.exec("select * from User");
    qDebug()<< query.value(0);
    while (query.next()){
        if(query.value(0)==username){
            if(query.value(1)==password){
                QMessageBox::information(this,"登录提示","登录成功");
                this->hide();
                Iot *i= new Iot(db);    //堆空间创建对象
                i->show();
            }                //登陆成功
            else{
                QMessageBox::information(this,"登录提示","登录失败，用户名或密码错误");
            }
        }
    }
}

