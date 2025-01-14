#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DepoPro.h"
#include "stockItem.h"
#include "orderItem.h"

class DepoPro : public QMainWindow
{
    Q_OBJECT

public:
    //Constructor & destructor
    DepoPro(QWidget* parent = nullptr);
    ~DepoPro();

    //Public functions
    void saveStockAndOrders();
	void loadStockAndOrders();


protected:
    //Ovverriding the closeEvent function
	void closeEvent(QCloseEvent* event) override;

private:
    //App UI object
    Ui::DepoProClass ui;

    //Stock and order vectors
    std::vector<stockItem> stock;
    std::vector<orderItem> orders;
    
    //Private functions
    void addNewItem();
    void removeItem();
    void addNewOrder();
    void removeOrder();
    void loadFromFile();
    void saveToFile();
};