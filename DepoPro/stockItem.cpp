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

    //Item price
    priceSpinBox = new QDoubleSpinBox();    
    priceSpinBox->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white; max-height: 32.5px; max-width:95px;");
    priceSpinBox->setMaximum(999999);

    //Item category text
    itemCategory = new QTextEdit();
    itemCategory->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white; max-height: 32.5px;max-width:65px;");
    itemCategory->setText("Enter product category");

    //Price label
    QLabel* priceLabel = new QLabel();
    priceLabel->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white; max-height: 15px;max-width:90px;");
    priceLabel->setText("Price: (PLN)");

    //Setting the vertical layout
    QVBoxLayout* itemLayout = new QVBoxLayout();
    itemLayout->addWidget(priceLabel);
    itemLayout->addWidget(priceSpinBox);

    //Frame (as a spacer)
    QFrame* spacerFrame = new QFrame();
    spacerFrame->setStyleSheet("border:none;max-width:95px;background-color:rgba(45,45,45,200);");
    spacerFrame->setLayout(itemLayout);

    //Adding everything to the item widget
    this->stockItemWidget->layout()->addWidget(itemName);
    this->stockItemWidget->layout()->addWidget(spacerFrame);
    this->stockItemWidget->layout()->addWidget(spinBox);
}


//Destructor
stockItem::~stockItem()
{

}
