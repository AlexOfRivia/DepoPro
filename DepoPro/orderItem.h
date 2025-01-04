#pragma once
#include <iostream>
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QLabel>

class orderItem
{
	//Public parameters
	QWidget* orderItemWidget;
	QTextEdit* itemName;
	int orderID;
	int date;
	int clientInfo;
	QString address;

	QTextEdit* itemCategory;
	QDoubleSpinBox* priceSpinBox;
	QSpinBox* amountSpinBox;

	//Constructor & Destructor
	orderItem();
	~orderItem();
};

