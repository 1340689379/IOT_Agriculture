#ifndef IOTMAIN_H
#define IOTMAIN_H

#include <QWidget>
#include <QSqlDatabase>
namespace Ui {
class IotMain;
}

class IotMain : public QWidget
{
    Q_OBJECT

public:
    explicit IotMain(QSqlDatabase *dbase,QWidget *parent = nullptr);
    ~IotMain();

private:
    Ui::IotMain *ui;
    QSqlDatabase *db;
};

#endif // IOTMAIN_H
