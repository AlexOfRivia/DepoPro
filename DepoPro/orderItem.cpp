#include "orderItem.h"

//Constructor
orderItem::orderItem()
{
    //Creating the order widget
    orderItemWidget = new QWidget;
    orderItemWidget->setStyleSheet("border:none; background-color:rgba(45,45,45,200);");

	QHBoxLayout* mainOrderLayout = new QHBoxLayout();
	orderItemWidget->setLayout(mainOrderLayout);

	QVBoxLayout* orderInfoLayout = new QVBoxLayout();
	QVBoxLayout* clientInfoLayout = new QVBoxLayout();  

	orderedItems = new QTextEdit;
    orderedItems->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white; max-height:200px; max-width:325px;");

	clientInfo = new QLabel;
	clientInfo->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 8pt 'Arial';  color: white;max-height:150px;max-width:180px;");
	
	address = new QLabel;
	address->setStyleSheet("border:none; background-color:rgba(45,45,45,255);font: 700 6pt 'Arial';  color: white;max-height:150px; max-width:180px;");


	clientInfoLayout->addWidget(clientInfo);
	clientInfoLayout->addWidget(address);


	mainOrderLayout->layout()->addWidget(orderedItems);
	mainOrderLayout->addLayout(clientInfoLayout);

}

//Destructor
orderItem::~orderItem()
{

}
