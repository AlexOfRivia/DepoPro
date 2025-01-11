#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DepoPro.h"
#include "stockItem.h"
#include "orderItem.h"

class DepoPro : public QMainWindow
{
    Q_OBJECT

public:
    DepoPro(QWidget* parent = nullptr);
    ~DepoPro();

    void saveStockAndOrders();
	void loadStockAndOrders();


private:
    Ui::DepoProClass ui;
    std::vector<stockItem> stock;
    std::vector<orderItem> orders;
    
    void addNewItem();
    void removeItem();

    void addNewOrder();
    void removeOrder();
    void loadFromFile();
    void saveToFile();
};