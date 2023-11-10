#include "login.h"
#include "ui_login.h"
#include <QGraphicsDropShadowEffect>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <registerpage.h>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //QMessageBox msgBox;
    //固定窗口大小
    setFixedSize(this->width(),this->height());
    //隐藏边框
    setWindowFlag(Qt::FramelessWindowHint);
    //开启关闭按钮
    setWindowFlag(Qt::WindowCloseButtonHint);
    //this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));");
    QPixmap *pix = new QPixmap(":/new/prefix1/resources/images/login.jpg");
    //设置图片
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));
    pix=new QPixmap(":/new/prefix1/resources/icons/IOT.svg");
    sz = ui->windows_icon->size();
    ui->windows_icon->setPixmap(pix->scaled(sz));
    //设置图片阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);

    QSqlDatabase d=QSqlDatabase::addDatabase("QODBC");
    db=&d;

    db->setHostName("127.0.0.1");
    db->setPort(3306);
    db->setDatabaseName("Mysql");
    db->setUserName("root");
    db->setPassword("root");


    bool ok = db->open();
    if (ok){
        qDebug("本地数据库连接成功！");
    }
    else {
        qDebug("本地数据库连接失败！");
        qDebug()<<"error open database because"<<db->lastError().text();
    }
    //msgBox.exec();
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_button_clicked()
{
    QSqlQuery query;
    QRegularExpression regx("");
    QString username =ui->idLineEdit->text();
    QString password =ui->pdLineEdit->text();
    if(username.compare("")==0||password.compare("")==0){
        QMessageBox::information(this,"登录提示","用户名或密码不得为空!");
    }else{
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
}

void Login::on_register_button_clicked()
{
    this->close();
    RegisterPage *r = new RegisterPage;
    r->show();
}


void Login::on_close_button_clicked()
{
    this->close();
}


void Login::on_eye_button_clicked()
{
    if(eye == 0){
        eye=1;
        ui->eye_button->setIcon(QIcon(":/new/prefix1/resources/icons/eye_open.svg"));
        ui->pdLineEdit->setEchoMode(QLineEdit::Normal);
    }else{
        eye=0;
        ui->eye_button->setIcon(QIcon(":/new/prefix1/resources/icons/eye_close.svg"));
        ui->pdLineEdit->setEchoMode(QLineEdit::Password);
    }
}

