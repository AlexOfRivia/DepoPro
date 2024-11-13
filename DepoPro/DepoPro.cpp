#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidgetItem>

void DepoPro::addNewItem()
{
    QListWidgetItem* listItem = new QListWidgetItem();
    

    //Widget and widget layout
    QWidget* itemWidget = new QWidget();
    itemWidget->setLayout(new QHBoxLayout(itemWidget));
    
    //Adding things to the item Widget
    QSpinBox* spinBox = new QSpinBox();
    
    QTextEdit* itemName = new QTextEdit();
    itemName->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 14pt 'Arial';  color: white; ");
    itemWidget->layout()->addWidget(itemName);
    itemWidget->layout()->addWidget(spinBox);
    listItem->setSizeHint(itemWidget->sizeHint());


    ui.itemList->addItem(listItem);
    ui.itemList->setItemWidget(listItem, itemWidget);
    
    
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
