#include "registerpage.h"
#include "ui_registerpage.h"
#include <QGraphicsDropShadowEffect>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

RegisterPage::RegisterPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterPage)
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
    QPixmap *pix = new QPixmap(":/new/prefix1/resources/images/register.jpg");
    //设置图片
    QSize sz = ui->image_label->size();
    ui->image_label->setPixmap(pix->scaled(sz));
    //设置图片阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->image_label->setGraphicsEffect(shadow);

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

RegisterPage::~RegisterPage()
{
    delete ui;
}

void RegisterPage::on_register_button_clicked()
{
    QString username =ui->id_line->text();
    QString password =ui->password_line->text();
    QString surepass =ui->confirm_line->text();
    if(password == surepass)
    {
        QString sql= QString("insert into User values('%1', '%2');").arg(username).arg(password);
        QSqlQuery query;
        if(query.exec(sql))
        {
            QMessageBox::information(this,"注册提示","注册成功");
        }
        else{
            QMessageBox::information(this,"注册提示","注册失败");
        }
    }else{
        QMessageBox::information(this,"注册认证","两次密码输入不一致");
    }
}


void RegisterPage::on_return_button_clicked()
{
    Login *l = new Login;
    l->show();
    this->close();
}


void RegisterPage::on_close_button_clicked()
{
    this->close();
}


void RegisterPage::on_eye_button_1_clicked()
{
    if(eye1 == 0){
        eye1=1;
        ui->eye_button_1->setIcon(QIcon(":/new/prefix1/resources/icons/eye_open.svg"));
        ui->password_line->setEchoMode(QLineEdit::Normal);
    }else{
        eye1=0;
        ui->eye_button_1->setIcon(QIcon(":/new/prefix1/resources/icons/eye_close.svg"));
        ui->password_line->setEchoMode(QLineEdit::Password);
    }
}


void RegisterPage::on_eye_button_2_clicked()
{
    if(eye2 == 0){
        eye2=1;
        ui->eye_button_2->setIcon(QIcon(":/new/prefix1/resources/icons/eye_open.svg"));
        ui->confirm_line->setEchoMode(QLineEdit::Normal);
    }else{
        eye2=0;
        ui->eye_button_2->setIcon(QIcon(":/new/prefix1/resources/icons/eye_close.svg"));
        ui->confirm_line->setEchoMode(QLineEdit::Password);
    }
}

