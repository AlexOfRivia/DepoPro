#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QListWidgetItem>

void DepoPro::addNewItem()
{
    QListWidgetItem* listItem = new QListWidgetItem();
    

    //Widget and widget layout
    QWidget* itemWidget = new QWidget();
    itemWidget->setLayout(new QHBoxLayout(itemWidget));
    itemWidget->setStyleSheet("border:none; background-color:rgba(45,45,45,200);");
    
    //Adding things to the item Widget:

    //SpinBox
    QSpinBox* spinBox = new QSpinBox();
    spinBox->setStyleSheet("max-width:50px; color: white;");
    
    //Item text
    QTextEdit* itemName = new QTextEdit();
    itemName->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 12pt 'Arial';  color: white; max-height: 65px; max-width:375px;");
    
    //Checkbox
    QCheckBox* checkBox = new QCheckBox();
    checkBox->setStyleSheet("max-width:25px;background-color:rgba(45,45,45,200);");

    //Frame (as a spacer)
    QFrame* spacerFrame = new QFrame();
    spacerFrame->setStyleSheet("width:130px;background-color:rgba(45,45,45,200);");
    
    itemWidget->layout()->addWidget(checkBox);
    itemWidget->layout()->addWidget(itemName);
    itemWidget->layout()->addWidget(spacerFrame);
    itemWidget->layout()->addWidget(spinBox);
    listItem->setSizeHint(itemWidget->sizeHint());

    //Setting the itemWidget as a listItem, so that can be put into a list
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
