#include "forget.h"
#include "ui_forget.h"
#include <QGraphicsDropShadowEffect>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

Forget::Forget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Forget)
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
    QPixmap *pix = new QPixmap(":/new/prefix1/resources/images/forget.png");
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

Forget::~Forget()
{
    delete ui;
}

void Forget::on_set_button_clicked()
{
    QString username =ui->id_line->text();
    QString email =ui->email_line->text();
    QString password =ui->password_line->text();
    QString surepass =ui->confirm_line->text();
    QRegularExpression exp1("^[A-Za-z0-9]*$");
    //QRegularExpressionMatch match1=exp1.match(username);
    QRegularExpressionMatch match2=exp1.match(password);
    //QRegularExpression exp2("^[a-z0-9A-Z]+[- | a-z0-9A-Z . _]+@([a-z0-9A-Z]+(-[a-z0-9A-Z]+)?\\.)+[a-z]{2,}$");
    //QRegularExpressionMatch match3=exp2.match(email);
    QString sql_email = QString("select * from User where email=('%1');").arg(email);
    QString sql_username = QString("select * from User where username=('%1');").arg(username);
    QSqlQuery q1;
    QSqlQuery q2;
    q1.exec(sql_username);
    q2.exec(sql_email);

    if(username.compare("")==0 || email.compare("")==0 || password.compare("")==0 || surepass.compare("")==0){
                QMessageBox::information(this,"修改失败","输入字段不得为空！");
    }else if(!q1.next()){
                QMessageBox::information(this,"修改失败","用户名不存在，请去注册！");
    }else if(password.length()<6 || password.length()>20){
                QMessageBox::information(this,"修改失败","密码长度为8到20位！");
    }else if(!match2.hasMatch()){
                QMessageBox::information(this,"修改失败","密码只能包含英文或数字！");
    }else if(password!=surepass){
                QMessageBox::information(this,"修改失败","两次密码输入不一致!");
    }else{
        QSqlQuery query;
        query.exec("select * from User");
        qDebug()<< query.value(0);
        while (query.next()){
            if(query.value(0)==username){
                if(query.value(2)==email){
                    QMessageBox::information(this,"找回提示","修改成功");
                    QString sql=QString("update user set password=('%1') where username=('%2');").arg(password).arg(username);
                    query.exec(sql);
                }                //登陆成功
                else{
                    QMessageBox::information(this,"找回提示","找回失败，注册邮箱与用户名不匹配！");
                }
            }
        }
    }
}


void Forget::on_eye_button_1_clicked()
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


void Forget::on_eye_button_2_clicked()
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


void Forget::on_return_button_clicked()
{
    Login *l = new Login;
    l->show();
    this->close();
}


void Forget::on_close_button_clicked()
{
    this->close();
}


void Forget::on_pushButton_clicked()
{
    RegisterPage *rp = new RegisterPage;
    rp->show();
    this->close();
}

