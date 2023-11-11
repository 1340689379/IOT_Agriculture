#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <iot.h>
//#include <registerpage.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_login_button_clicked();

    void on_register_button_clicked();

    void on_close_button_clicked();

    void on_eye_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase *db;
    int eye=0;
};
#endif // LOGIN_H
