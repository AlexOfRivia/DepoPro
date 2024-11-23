#include "stockItem.h"


//Constructor
stockItem::stockItem()
{
	stockItemWidget = new QWidget;
	stockItemWidget->setLayout(new QHBoxLayout(stockItemWidget));
	stockItemWidget->setStyleSheet("border:none; background-color:rgba(45,45,45,200);");

    //SpinBox
    QSpinBox* spinBox = new QSpinBox();
    spinBox->setStyleSheet("max-width:50px; color: white;");

    //Item text
    QTextEdit* itemName = new QTextEdit();
    itemName->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 12pt 'Arial';  color: white; max-height: 65px; max-width:375px;");

    //Frame (as a spacer)
    QFrame* spacerFrame = new QFrame();
    spacerFrame->setStyleSheet("width:130px;background-color:rgba(45,45,45,200);");

    this->stockItemWidget->layout()->addWidget(itemName);
    this->stockItemWidget->layout()->addWidget(spacerFrame);
    this->stockItemWidget->layout()->addWidget(spinBox);
}


//Destructor
stockItem::~stockItem()
{

}
