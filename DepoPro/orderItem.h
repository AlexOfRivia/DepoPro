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
		QTextEdit* orderedItems;
		int orderID;
		QLabel* IDLabel;
		QLabel* clientInfo;
		QLabel* address;
		QString IDString;

		//item and amount vectors
		std::vector<QLabel*> items;
		std::vector<QLabel*> orderedAmounts;

		void setOrderID();

		//Constructor & Destructor
		orderItem();
		~orderItem();
};

