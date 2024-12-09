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
class stockItem
{

public:
	//Public parameters
	QWidget* stockItemWidget;
	QTextEdit* itemName;
	QTextEdit* itemCategory;
	QTextEdit* itemPrice;
	QSpinBox* spinBox;

	//Constructor & Destructor
	stockItem();
	~stockItem();


private:
	
};

