#ifndef FORGET_H
#define FORGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <login.h>
#include <registerpage.h>

namespace Ui {
class Forget;
}

class Forget : public QWidget
{
    Q_OBJECT

public:
    explicit Forget(QWidget *parent = nullptr);
    ~Forget();

private slots:
    void on_set_button_clicked();

    void on_eye_button_1_clicked();

    void on_eye_button_2_clicked();

    void on_return_button_clicked();

    void on_close_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Forget *ui;
    QSqlDatabase *db;
    int eye1=0;
    int eye2=0;
};

#endif // FORGET_H
