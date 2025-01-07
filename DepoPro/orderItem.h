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
#include <cstdlib>

//Libraries for reading time and date
#include <chrono>
#include <iomanip>

class orderItem
{
	public:
		//Public parameters
		QWidget* orderItemWidget;
		QLabel* itemNames;
		int orderID;
		int orderDate;
		QString clientInfo;
		QString address;
		//QTextEdit* itemCategory;

		std::vector<QLabel*> items;
		std::vector<QSpinBox*> orderedAmounts;

		//Constructor & Destructor
		orderItem();
		~orderItem();
};

