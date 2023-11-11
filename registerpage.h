#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QSqlDatabase>
#include <login.h>


namespace Ui {
class RegisterPage;
}

class RegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = nullptr);
    ~RegisterPage();

private slots:
    void on_register_button_clicked();

    void on_return_button_clicked();

    void on_close_button_clicked();


    void on_eye_button_1_clicked();

    void on_eye_button_2_clicked();

private:
    Ui::RegisterPage *ui;
    QSqlDatabase *db;
    int eye1=0;
    int eye2=0;
};

#endif // REGISTERPAGE_H
