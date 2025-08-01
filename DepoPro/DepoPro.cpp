#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QSaveFile>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSettings>


//Saving the stock and orders to a file while closing the app
void DepoPro::saveStockAndOrders()
{

	QString fileName = "DepoProStockSave.txt"; //Setting the file name

	QFile file(fileName); //Opening the file
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) //Checking if the file is opened
	{
		QTextStream stream(&file); //Creating a stream
		for (const auto& item : stock) //Writing the stock to the file
		{
			stream << item.itemName->toPlainText() << ";" //Writing the item name into stream
				<< item.priceSpinBox->value() << ";" //Writing the item price into stream
				<< item.spinBox->value() << "\n"; //Writing the item amount into stream
		}
		file.close(); //Closing the file after writing
	}
	else
	{
		QMessageBox::warning(this, "Error", "Failed to save the file.");
		return;
	}

    QSettings settings("AB", "DepoPro"); // Creating a settings object

    settings.beginGroup("OrdersSave"); // Creating a group for orders
    settings.remove(""); // Clear previous orders

    for (int i = 0; i < orders.size(); ++i)
    {
        const orderItem& order = orders[i];
        QString orderGroup = QString("Order%1").arg(i); // Creating a group for each order

        settings.beginGroup(orderGroup); // Beginning group
        settings.setValue("OrderID", order.IDString); // Setting the order ID
        settings.setValue("OrderedItems", order.orderedItems->toPlainText()); // Setting the ordered items
        settings.setValue("ClientInfo", order.clientInfo->text()); // Setting the client info
        settings.setValue("Address", order.address->text()); // Setting the address
        settings.endGroup(); // Ending the group
    }
    settings.endGroup(); // Ending the OrdersSave group

    settings.beginGroup("NotepadSave"); // Saving the notes from the notepad
    settings.remove(""); // Clearing previous notes
    settings.setValue("NotepadText", ui.textEdit->toPlainText()); // Saving the notes
    settings.endGroup(); // Ending the NotepadSave group
}

//loadfing the stock and orders upon initializing the app
void DepoPro::loadStockAndOrders()
{
    QString fileName = "DepoProStockSave.txt"; //Setting the file name
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Handle file open error
        QMessageBox::warning(this, "Error", "Failed to open the file.");
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine(); //Creates a line of text from the txt file
        QStringList lineList = line.split(";"); //Splits the currently read line after ;
        if (lineList.size() < 3)
        {
            //Handle parsing error
            QMessageBox::warning(this, "Error", "Invalid line format in the file.");
            continue;
        }

        QString stockItemName = lineList.value(0); //Setting the item name to the first value in string list
        QString stockItemPriceStr = lineList.value(1); //Setting the item price to the second value in string list
        QString stockItemAmountStr = lineList.value(2); //Setting the item amount to the third value in string list

        bool amountOk, priceOk;
        int stockItemAmount = stockItemAmountStr.toInt(&amountOk); //Converting the read amount to int
        float stockItemPrice = stockItemPriceStr.toFloat(&priceOk); //Converting the read price to float

        if (!amountOk || !priceOk)
        {
            //Handle conversion error
            QMessageBox::warning(this, "Error", "Invalid stock amount or price in the file.");
            continue;
        }

        auto loadedListItem = std::make_unique<QListWidgetItem>(); //Creates a new widget item
        auto loadedItem = std::make_unique<stockItem>(); //Creates a new stock item

        loadedItem->itemName->setText(stockItemName); //Sets the stock item name as the split name
        loadedItem->priceSpinBox->setValue(stockItemPrice); //Sets the stock item price as the converted float value
        loadedItem->spinBox->setValue(stockItemAmount); //Sets the stock item amount as the converted int value

        this->stock.push_back(*loadedItem); //Adding a new element to a vector

        ui.listWidget_2->addItem(loadedItem->itemName->toPlainText()); //Adding a new item to the stock widget on the dashboard


        loadedListItem->setSizeHint(loadedItem->stockItemWidget->sizeHint());

        ui.itemList->addItem(loadedListItem.release()); //Adds the item to the list
        ui.itemList->setItemWidget(ui.itemList->item(ui.itemList->count() - 1), loadedItem->stockItemWidget);
    }

    file.close(); //Closes the file

    QSettings settings("AB", "DepoPro"); //Oppening the settings object

    settings.beginGroup("OrdersSave"); //Creating the Orders group
	QStringList orderGroups = settings.childGroups(); //Getting the child groups

    for (const QString& orderGroup : orderGroups)
    {
		settings.beginGroup(orderGroup); //Beggining the group

        bool isIDOK;
        int orderID = settings.value("OrderID").toInt(&isIDOK);
        if (!isIDOK)
        {
            //Handle orderID conversion error
            QMessageBox::warning(this, "Error", "Invalid order ID in the settings.");
			settings.endGroup(); //Ending the group
            continue;
        }

        QString orderedItems = settings.value("OrderedItems").toString(); //Getting the ordered items
        QString clientInfo = settings.value("ClientInfo").toString(); //Getting the client info
        QString address = settings.value("Address").toString(); //Getting the order address

        auto loadedOrder = std::make_unique<orderItem>(); //Creating a unique loadedOrder pointer
		loadedOrder->IDString = QString::number(orderID); //Setting the order ID
		loadedOrder->IDLabel->setText("Order ID: " + loadedOrder->IDString); //Setting the order ID label
        loadedOrder->orderedItems->setText(orderedItems); //Loading the ordered items
        loadedOrder->clientInfo->setText(clientInfo); //Loading the client into
        loadedOrder->address->setText(address); //Loading the address

        //Add order ID to the list widget
        ui.listWidget->addItem("Order ID: " + loadedOrder->IDString);

        orders.push_back(*loadedOrder); //Adding the created item to the orders vector

		auto orderListItem = std::make_unique<QListWidgetItem>(); //Creating a new list item
		orderListItem->setSizeHint(loadedOrder->orderItemWidget->sizeHint()); //Setting the size hint

		ui.orderList->addItem(orderListItem.release()); //Adding the item to the list
		ui.orderList->setItemWidget(ui.orderList->item(ui.orderList->count() - 1), loadedOrder->orderItemWidget); //Setting the item widget

		settings.endGroup(); //Ending the group
    }
	settings.endGroup(); //Ending the OrdersSave group
	settings.beginGroup("NotepadSave"); //Loading the notes from the notepad
	
    QString notepadText = settings.value("NotepadText").toString(); //Getting the notes

	ui.textEdit->setText(notepadText); //Setting the notes to the notepad
	settings.endGroup(); //Ending the group
}


//Overriding the close event to save the stock and orders while closing the app
void DepoPro::closeEvent(QCloseEvent* event)
{
    saveStockAndOrders();
}


//Adding a new item to list
void DepoPro::addNewItem()
{
        QListWidgetItem* listItem = new QListWidgetItem(); //Creating a new list item

        stockItem* newStockItem = new stockItem; //Creating a new stockItem object

        this->stock.push_back(*newStockItem); //Adding new element to the vector

        listItem->setSizeHint(newStockItem->stockItemWidget->sizeHint()); 

        ui.listWidget_2->addItem(newStockItem->itemName->toPlainText()); //Adding a new item to the stock widget on the dashboard

        //Setting the itemWidget as a listItem, so that can be put into a list
        ui.itemList->addItem(listItem);
        ui.itemList->setItemWidget(listItem, newStockItem->stockItemWidget);
}

//Removing an item from list
void DepoPro::removeItem()
{
    int index = ui.itemList->currentRow(); //Get the index of the selected item
    if (index != -1) //Check if an item is selected
    {
        //Remove the item from the list and the stock vector
        QListWidgetItem* selectedItem = ui.itemList->takeItem(index); //Removing the selected item from the list
        QListWidgetItem* selectedStockItem = ui.listWidget_2->takeItem(index); //Removing the selected item from the stock widget
        this->stock.erase(this->stock.begin() + index); //Erasing the vector item

        //Delete the selected item object
        delete selectedItem;
	}
    else
    {
		QMessageBox::warning(this, "Error", "No item selected."); //Return an error message if no item is selected
    }
}

//Adding a new order to the order list
void DepoPro::addNewOrder()
{
        if (ui.itemList->count() == 0 || this->stock.empty()) //Checking if empty
        {
            QMessageBox::warning(this, "Error", "You currently have no items in stock.");
            return;
        }

        QDialog dialog(this);
        dialog.setWindowTitle("Select Items for New Order");

        QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);

        std::vector<QCheckBox*> checkBoxes;
        std::vector<QSpinBox*> spinBoxes;
        std::vector<QLabel*> labels;

        //Writing the elements from the stock vector to the dialog box
        for (size_t i = 0; i < stock.size(); ++i)
        {
            QHBoxLayout* itemLayout = new QHBoxLayout;

            QCheckBox* checkBox = new QCheckBox(stock[i].itemName->toPlainText(), &dialog);
            QSpinBox* spinBox = new QSpinBox(&dialog);
            spinBox->setRange(1, stock[i].spinBox->value()); //Setting the range based on available stock
            QLabel* nameLabel = new QLabel(QString::number(stock[i].spinBox->value()), &dialog);

            itemLayout->addWidget(checkBox);
            itemLayout->addWidget(new QLabel("\tOrdered Amount:", &dialog));
            itemLayout->addWidget(spinBox);
            itemLayout->addWidget(new QLabel("\tMax Amount: ", &dialog));
            itemLayout->addWidget(nameLabel);

            mainLayout->addLayout(itemLayout);
            checkBoxes.push_back(checkBox);
            spinBoxes.push_back(spinBox);
        }

        QLabel* clientInformation = new QLabel("Client Information: ", &dialog);
        QTextEdit* clientInfoInput = new QTextEdit(&dialog);
        QLabel* clientAddress = new QLabel("Client Address: ", &dialog);
        QTextEdit* clientAddressInput = new QTextEdit(&dialog);
        mainLayout->addWidget(clientInformation);
        mainLayout->addWidget(clientInfoInput);
        mainLayout->addWidget(clientAddress);
        mainLayout->addWidget(clientAddressInput);

        QPushButton* okButton = new QPushButton("OK", &dialog);
        connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
        mainLayout->addWidget(okButton);

        if (dialog.exec() == QDialog::Accepted)
        {
            auto newOrderItem = std::make_unique<orderItem>(); //Creating a new orderItem object
			newOrderItem->setOrderID(); //Setting the order ID
            for (size_t i = 0; i < checkBoxes.size(); ++i)
            {
                if (checkBoxes[i]->isChecked())
                {
                    QLabel* itemLabel = new QLabel(stock[i].itemName->toPlainText(), &dialog);
                    QLabel* amountLabel = new QLabel(QString::number(spinBoxes[i]->value()), &dialog);
                    stock[i].spinBox->setValue(stock[i].spinBox->value() - spinBoxes[i]->value());
                    newOrderItem->orderedAmounts.push_back(amountLabel);
                    newOrderItem->items.push_back(itemLabel);
                }
            }

            //Writing the information from the dialog box to the orderItem object
            for (size_t i = 0; i < newOrderItem->items.size(); ++i)
            {
                if (newOrderItem->orderedItems)
                {
                    newOrderItem->orderedItems->setText(newOrderItem->orderedItems->toPlainText() + newOrderItem->items[i]->text() + ", Quantity: " + newOrderItem->orderedAmounts[i]->text() + "\n");
                }
            }

            //Add order ID to the list widget
            ui.listWidget->addItem("Order ID: " + QString::number(newOrderItem->orderID));

            newOrderItem->clientInfo->setText("Client:\n" + clientInfoInput->toPlainText());
            newOrderItem->address->setText("Address:\n" + clientAddressInput->toPlainText());
            this->orders.push_back(*newOrderItem); //Adding new element to the vector

            auto orderListItem = std::make_unique<QListWidgetItem>();
            orderListItem->setSizeHint(newOrderItem->orderItemWidget->sizeHint());

            //Setting the itemWidget as a listItem, so that can be put into a list
            ui.orderList->addItem(orderListItem.release());
            ui.orderList->setItemWidget(ui.orderList->item(ui.orderList->count() - 1), newOrderItem->orderItemWidget);
        }

        
}

//Removing the order from the list
void DepoPro::removeOrder()
{
    int index = ui.orderList->currentRow(); //Get the index of the selected item
    if (index != -1) //Check if an item is selected
    {
        //Remove the item from the list and the stock vector
        QListWidgetItem* selectedItem = ui.orderList->takeItem(index); //Removing the selected item from the list
		QListWidgetItem* selectedOrder = ui.listWidget->takeItem(index); //Removing the selected order ID from the list
        this->orders.erase(this->orders.begin() + index); //Erasing the vector item

        //Delete the selected item object
        delete selectedItem;
    }
    else
    {
        QMessageBox::warning(this, "Error", "No item selected."); //Return an error message if no item is selected
    }
}

//Loading a stock list to current list from file
void DepoPro::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Please, choose a file to open"); //Opens a file dialog box
    if (fileName.isEmpty()) 
    {
        return; //if no file is selected, return early
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        // Handle file open error
        QMessageBox::warning(this, "Error", "Failed to open the file.");
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) 
    {
        QString line = in.readLine(); //Creates a line of text from the txt file
        QStringList lineList = line.split(";"); //Splits the currently read line after ;
        if (lineList.size() < 3) 
        {
            //Handle parsing error
            QMessageBox::warning(this, "Error", "Invalid line format in the file.");
            continue;
        }

        QString stockItemName = lineList.value(0); //Setting the item name to the first value in string list
        QString stockItemPriceStr = lineList.value(1); //Setting the item price to the second value in string list
        QString stockItemAmountStr = lineList.value(2); //Setting the item amount to the third value in string list

        bool amountOk, priceOk;
        int stockItemAmount = stockItemAmountStr.toInt(&amountOk); //Converting the read amount to int
        float stockItemPrice = stockItemPriceStr.toFloat(&priceOk); //Converting the read price to float

        if (!amountOk || !priceOk)
        {
            //Handle conversion error
            QMessageBox::warning(this, "Error", "Invalid stock amount or price in the file.");
            continue;
        }

        auto loadedListItem = std::make_unique<QListWidgetItem>(); //Creates a new widget item
        auto loadedItem = std::make_unique<stockItem>(); //Creates a new stock item

        loadedItem->itemName->setText(stockItemName); //Sets the stock item name as the split name
        loadedItem->priceSpinBox->setValue(stockItemPrice); //Sets the stock item price as the converted float value
        loadedItem->spinBox->setValue(stockItemAmount); //Sets the stock item amount as the converted int value

        this->stock.push_back(*loadedItem); //Adding a new element to a vector

        ui.listWidget_2->addItem(loadedItem->itemName->toPlainText()); //Adding a new item to the stock widget on the dashboard

        loadedListItem->setSizeHint(loadedItem->stockItemWidget->sizeHint());

        ui.itemList->addItem(loadedListItem.release()); //Adds the item to the list
        ui.itemList->setItemWidget(ui.itemList->item(ui.itemList->count() - 1), loadedItem->stockItemWidget);
    }

    file.close(); //Closes the file
}

//Saving current stock to file
void DepoPro::saveToFile()
{
	if (ui.itemList->count() != 0 && !this->stock.empty()) //Checking if the stock is not empty
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Please, chose a file to open"); //Opening a file dialog box
        if (fileName != "") //If file name is not empty
        {

            QFile file(fileName); //Open file
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
            {
                QTextStream stream(&file); //Create a stream
                for (const auto& item : stock)
                {
                    stream << item.itemName->toPlainText() << ";" //Writing the item name into stream
						<< item.priceSpinBox->value() << ";" //Writing the item price into stream
                        << item.spinBox->value() << "\n"; //Writing the item amount into stream
                }

                file.close(); //Closing the file after writing 
                QMessageBox::information(this, "Success", "Stock saved successfully.");

            }
            else {
				QMessageBox::warning(this, "Error", "Failed to save the file.");
				return;
            }
        }
    }
    else {
        QMessageBox::warning(this, "Error", "No items to save.");
        return;
    }
}

//Constructor
DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{


    ui.setupUi(this);
	//setFixedSize(800, 500); //Setting the fixed size of the window
    loadStockAndOrders(); //loading stock and orders
    
    QObject::connect(
        ui.addButton, &QPushButton::clicked,this,&DepoPro::addNewItem //Connecting the adding method to a button in the ui
    );
    QObject::connect(
        ui.removeButton, &QPushButton::clicked,this,&DepoPro::removeItem //Connecting the removing method to a button in the ui
    );
    QObject::connect(
        ui.loadButton, &QPushButton::clicked,this,&DepoPro::loadFromFile //Connecting the loading method to a button in the ui
    );
    QObject::connect(
        ui.saveButton, &QPushButton::clicked,this,&DepoPro::saveToFile //Connecting the saving method to a button in the ui
    );
    QObject::connect(
		ui.addOrderButton,& QPushButton::clicked,this,& DepoPro::addNewOrder //Connecting the adding order method to a button in the ui
	);
    QObject::connect(
        ui.removeOrderButton,&QPushButton::clicked,this,&DepoPro::removeOrder //Connecting the removing order method to a button in the ui
    );


    ui.stackedWidget->setCurrentIndex(1); //Setting the default page to the dashboard
    
    QObject::connect(
        ui.orderButton, &QPushButton::clicked, [this]() { ui.stackedWidget->setCurrentIndex(0); } //Showing the order page upon button click
    );

    QObject::connect(
        ui.dashboardButton, &QPushButton::clicked, [this]() { ui.stackedWidget->setCurrentIndex(1); } //Showing the main dashboard uppon button click
    );

    QObject::connect(
        ui.stockButton, &QPushButton::clicked, [this]() { ui.stackedWidget->setCurrentIndex(2); } //Showing the stock pge upon button click
    );


}

//Destructor
DepoPro::~DepoPro()
{
    
}