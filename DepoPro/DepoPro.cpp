#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <QListWidgetItem>


//Adding a new item to list
void DepoPro::addNewItem()
{
    QListWidgetItem* listItem = new QListWidgetItem();
    
    stockItem* newStockItem = new stockItem;

    listItem->setSizeHint(newStockItem->stockItemWidget->sizeHint());

    //Setting the itemWidget as a listItem, so that can be put into a list
    ui.itemList->addItem(listItem);
    ui.itemList->setItemWidget(listItem, newStockItem->stockItemWidget);
    
    
}

//Removing an item from list
void DepoPro::removeItem()
{
    //Creating a new ListWidgetItem, which is the selected (clicked) item in the list
    QListWidgetItem* selectedItem = ui.itemList->takeItem(ui.itemList->currentRow()); //Take item takes care of deleting the selected item 
    
    //Deleting the selected item object
    delete selectedItem; 
    
}

//Loading a list from file
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
        }

        file.close(); //Closes the file
    }
}

//Constructor
DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(
        ui.addButton, &QPushButton::clicked,this,&DepoPro::addNewItem //Connecting the adding method to a button in the ui
    );
    QObject::connect(
        ui.removeButton, &QPushButton::clicked,this,&DepoPro::removeItem //Connecting the removing method to a button in the ui
    );
    QObject::connect(
        ui.loadButton, &QPushButton::clicked,this,&DepoPro::loadFromFile
    );

    ui.itemList->hide();
    ui.frame->hide();
}

//Destructor
DepoPro::~DepoPro()
{}
