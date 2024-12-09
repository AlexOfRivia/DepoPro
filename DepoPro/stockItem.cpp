#include "stockItem.h"


//Constructor
stockItem::stockItem()
{
    //Creating the item widget
	stockItemWidget = new QWidget;
	stockItemWidget->setLayout(new QHBoxLayout(stockItemWidget)); //Creating the main layout
	stockItemWidget->setStyleSheet("border:none; background-color:rgba(45,45,45,200);");

    //SpinBox
    spinBox = new QSpinBox();
    spinBox->setStyleSheet("max-width:50px; color: white;");
    spinBox->setMaximum(999);

    //Item name text
    itemName = new QTextEdit();
    itemName->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 12pt 'Arial';  color: white; max-height: 65px; max-width:375px;");
    itemName->setText("Enter product name");

    //Item price text
    itemPrice = new QTextEdit();
    itemPrice->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white; max-height: 65px; max-width:130px;");
    itemPrice->setText("Enter product price");

    //Item category text
    itemCategory = new QTextEdit();
    itemCategory->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white; max-height: 65px; max-width:130px;");
    itemPrice->setText("Enter product category");

    //Frame (as a spacer)
    QFrame* spacerFrame = new QFrame();
    spacerFrame->setStyleSheet("width:130px;background-color:rgba(45,45,45,200);");

    //Adding everything to the item widget
    this->stockItemWidget->layout()->addWidget(itemName);
    this->stockItemWidget->layout()->addWidget(spacerFrame); //Category and price layout will go here instead
    this->stockItemWidget->layout()->addWidget(spinBox);
}


//Destructor
stockItem::~stockItem()
{

}
