#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QListWidgetItem>

void DepoPro::addNewItem()
{
    QListWidgetItem* listItem = new QListWidgetItem();
    
    stockItem* newStockItem = new stockItem;

    listItem->setSizeHint(newStockItem->stockItemWidget->sizeHint());

    //Setting the itemWidget as a listItem, so that can be put into a list
    ui.itemList->addItem(listItem);
    ui.itemList->setItemWidget(listItem, newStockItem->stockItemWidget);
    
    
}
void DepoPro::removeItem()
{

}

DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(
        ui.addButton, &QPushButton::clicked,this,&DepoPro::addNewItem //Connecting the adding method to a button in the 
    );

    ui.itemList->hide();
    ui.frame->hide();
}

DepoPro::~DepoPro()
{}
