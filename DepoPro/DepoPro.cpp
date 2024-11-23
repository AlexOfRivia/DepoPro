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
    //Creating a new ListWidgetItem, which is the selected (clicked) item in the list
    QListWidgetItem* selectedItem = ui.itemList->takeItem(ui.itemList->currentRow()); //Take item takes care of deleting the selected item 
    
    //Deleting the selected item object
    delete selectedItem; 
    
}

DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(
        ui.addButton, &QPushButton::clicked,this,&DepoPro::addNewItem //Connecting the adding method to a button in the ui
    );
    QObject::connect(
        ui.removeButton, &QPushButton::clicked,this,&DepoPro::removeItem //Connecting the removing method to a button in the ui
    );

    ui.itemList->hide();
    ui.frame->hide();
}

DepoPro::~DepoPro()
{}
