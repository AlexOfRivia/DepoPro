#include "orderItem.h"

//Constructor
orderItem::orderItem()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Generate a random number in the range [0, 899999] and add 100000
    orderID =  std::rand() % 900000 + 100000;


    //Creating the order widget
    orderItemWidget = new QWidget;
    orderItemWidget->setLayout(new QHBoxLayout(orderItemWidget)); //Creating the main layout
    orderItemWidget->setStyleSheet("border:none; background-color:rgba(45,45,45,200);");

	//TODO: Add the rest of the widgets
    itemNames = new QLabel;
    itemNames->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 12pt 'Arial';  color: white; max-height: 65px; max-width:375px;");


}

//Destructor
orderItem::~orderItem()
{

}
