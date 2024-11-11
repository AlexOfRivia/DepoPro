#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DepoPro.h"
#include "stockItem.h"

class DepoPro : public QMainWindow
{
    Q_OBJECT

public:
    DepoPro(QWidget *parent = nullptr);
    ~DepoPro();

private slots:
    void on_dashboardButton_pressed();
    void on_stockButton_pressed();

private:
    Ui::DepoProClass ui;

};
