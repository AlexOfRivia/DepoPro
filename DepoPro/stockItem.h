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
class stockItem
{

public:
	//Public parameters
	QWidget* stockItemWidget;
	QTextEdit* itemName;
	QTextEdit* itemCategory;
	QDoubleSpinBox* priceSpinBox;
	QSpinBox* spinBox;

	//Constructor & Destructor
	stockItem();
	~stockItem();


private:
	
};

