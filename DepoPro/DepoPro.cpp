#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QSaveFile>


//Adding a new item to list
void DepoPro::addNewItem()
{
        QListWidgetItem* listItem = new QListWidgetItem(); //Creating a new list item

        stockItem* newStockItem = new stockItem; //Creating a new stockItem object

        this->stock.push_back(*newStockItem); //Adding new element to the vector

        listItem->setSizeHint(newStockItem->stockItemWidget->sizeHint());

        //Setting the itemWidget as a listItem, so that can be put into a list
        ui.itemList->addItem(listItem);
        ui.itemList->setItemWidget(listItem, newStockItem->stockItemWidget);
}

//Removing an item from list
void DepoPro::removeItem()
{
    // Get the index of the selected item
    int index = ui.itemList->currentRow(); //Getting the list item index

    // Remove the item from the list and the stock vector
    QListWidgetItem* selectedItem = ui.itemList->takeItem(index); //Removing the selected item from the list
    this->stock.erase(this->stock.begin() + index); //Erasing the vector item

    // Delete the selected item object
    delete selectedItem;
}

//Loading a stock list to current list from file
void DepoPro::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Please, chose a file to open"); //Opens a file dialog box
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // bind it
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine(); //Creates a line of text from the txt file
            QStringList lineList = line.split(";"); //Splits the currently read line after ;
            QString stockItemName = lineList.value(0); //Setting the item name to the first value in string list
            QString stockItemAmountStr = lineList.value(1); //Setting the item name to the second value in string list
            int stockItemAmount = stockItemAmountStr.toInt(); //Converting the read amount to int

            QListWidgetItem* loadedListItem = new QListWidgetItem(); //Creates a new widget item
            stockItem* loadedItem = new stockItem; //Creates a new stock item

            loadedItem->itemName->setText(stockItemName); //Sets the stock item name as the split name
            loadedItem->spinBox->setValue(stockItemAmount); //Sets the stock item amount as the converted int value

            this->stock.push_back(*loadedItem); //Adding a new element to a vector

            
            loadedListItem->setSizeHint(loadedItem->stockItemWidget->sizeHint());

            ui.itemList->addItem(loadedListItem); //Adds the item to the list
            ui.itemList->setItemWidget(loadedListItem, loadedItem->stockItemWidget);
            
        }

        file.close(); //Closes the file
    }
}

//Saving current stock to file
void DepoPro::saveToFile()
{
    if (ui.itemList->count()!=0)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Please, chose a file to open"); //Opening a file dialog box
        if (fileName != "") //If file name is not empty
        {

            QFile file(fileName); //Open file
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                // bind it
                QTextStream stream(&file); //Create a stream
                for (int i=0;i<stock.size();i++)
                {
                    stream << this->stock[i].itemName->toPlainText() << ";" << this->stock[i].spinBox->value() << "\n"; //Write into stream
                }

                file.close(); //Closing the file after writing 
            }
        }

    }
}

//Constructor
DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{
    //this->arrElementAmount = 0;
    ui.setupUi(this);

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

    //Hiding the frame and itemList upon startup
    ui.itemList->hide();
    ui.frame->hide();
}

//Destructor
DepoPro::~DepoPro()
{
    
}
