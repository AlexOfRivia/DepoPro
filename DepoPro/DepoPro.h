#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DepoPro.h"
#include "stockItem.h"

class DepoPro : public QMainWindow
{
    Q_OBJECT

public:
    DepoPro(QWidget* parent = nullptr);
    ~DepoPro();


private:
    Ui::DepoProClass ui;

    int arrElementAmount=0;
    stockItem stockArray[100];
    void addNewItem();
    void removeItem();
    void loadFromFile();
    void saveToFile();
};
