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
    if (ui.itemList->count() == 0)
    {
        this->arrElementAmount = 0;
    }
    //Create an Array of stock items and add them to list Item, this might be the answer to getting the item name
    if (ui.itemList->count()<100)
    {
        QListWidgetItem* listItem = new QListWidgetItem();

        stockItem* newStockItem = new stockItem;


        listItem->setSizeHint(newStockItem->stockItemWidget->sizeHint());

        //Setting the itemWidget as a listItem, so that can be put into a list
        ui.itemList->addItem(listItem);
        ui.itemList->setItemWidget(listItem, newStockItem->stockItemWidget);

        this->stockArray[arrElementAmount] = *newStockItem;
        this->arrElementAmount++;
    }
}

//Removing an item from list
void DepoPro::removeItem()
{
    //Creating a new ListWidgetItem, which is the selected (clicked) item in the list
    QListWidgetItem* selectedItem = ui.itemList->takeItem(ui.itemList->currentRow()); //Take item takes care of deleting the selected item 
    
    for (int i = ui.itemList->currentRow();i<this->arrElementAmount;i++)
    {
        this->stockArray[i] = this->stockArray[i+1];
    }

    //Deleting the selected item object
    delete selectedItem; 
    this->arrElementAmount--;
}

//Loading a stock list to current list from file
void DepoPro::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Please, chose a file to open");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // bind it
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine(); //Creates a line of text from the txt file
            QListWidgetItem* loadedListItem = new QListWidgetItem(); //Creates a new widget item
            stockItem* loadedItem = new stockItem; //Creates a new stock item

            loadedItem->itemName->setText(line); //Sets the stock item name as the read line
            
            loadedListItem->setSizeHint(loadedItem->stockItemWidget->sizeHint());

            ui.itemList->addItem(loadedListItem); //Adds the item to the list
            ui.itemList->setItemWidget(loadedListItem, loadedItem->stockItemWidget);
            
            stockArray[arrElementAmount] = *loadedItem;
            this->arrElementAmount++;
        }

        file.close(); //Closes the file
    }
}

//Saving current stock to file
void DepoPro::saveToFile()
{
    if (ui.itemList->count()!=0 && this->arrElementAmount!=0)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Please, chose a file to open");
        if (fileName != "")
        {

            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                // bind it
                QTextStream stream(&file);
                for (int i=0;i<this->arrElementAmount;i++)
                {
                    stream << this->stockArray[i].itemName->toPlainText() << "\n";
                }

                file.close();
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

    ui.itemList->hide();
    ui.frame->hide();
}

//Destructor
DepoPro::~DepoPro()
{
   
}
