#include "orderItem.h"

//Constructor
orderItem::orderItem()
{
	//Generating random order ID
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	orderID = (std::rand() % 999999) + 1;

    //Creating the order widget
    orderItemWidget = new QWidget;
    orderItemWidget->setStyleSheet("border:none; background-color:rgba(45,45,45,200);");

	//Main, horizontal layout
	QHBoxLayout* mainOrderLayout = new QHBoxLayout();
	orderItemWidget->setLayout(mainOrderLayout);

	//Vertical layouts for order and client information
	QVBoxLayout* orderInfoLayout = new QVBoxLayout();
	QVBoxLayout* clientInfoLayout = new QVBoxLayout();  

	//All ordered items
	orderedItems = new QTextEdit;
    orderedItems->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 9pt 'Arial';  color: white; max-height:200px; max-width:325px;");

	//Client information
	clientInfo = new QLabel;
	clientInfo->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 7pt 'Arial';  color: white;max-height:150px;max-width:180px;");
	
	//Shipping information
	address = new QLabel;
	address->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 7pt 'Arial';  color: white;max-height:150px; max-width:180px;");

	//Order ID Label
	IDLabel = new QLabel("Order ID: " + QString::number(orderID));
	IDLabel->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white;max-height:15px;max-width:180px;");

	//Setting the client information layout 
	clientInfoLayout->addWidget(IDLabel);
	clientInfoLayout->addWidget(clientInfo);
	clientInfoLayout->addWidget(address);

	//Setting the main order layout
	mainOrderLayout->layout()->addWidget(orderedItems);
	mainOrderLayout->addLayout(clientInfoLayout);

}

//Destructor
orderItem::~orderItem()
{

}