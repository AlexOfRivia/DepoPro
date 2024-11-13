#include "DepoPro.h"
#include <QLineEdit>
#include <QTextEdit>

void DepoPro::addNewItem()
{
    //Adds a vertical layout to the frame
    QVBoxLayout* itemLayout = qobject_cast<QVBoxLayout*>(ui.itemFrame->layout());

    //Initializing the added withet (BUtton is for testing)
    QPushButton* button = new QPushButton("Hello", ui.itemFrame);
    

    //Widget and widget layout
    QWidget* itemWidget = new QWidget(ui.itemFrame);
    itemWidget->setLayout(new QHBoxLayout(itemWidget));
    
    //Adding things to the item Widget
    QSpinBox* spinBox = new QSpinBox();
    
    QTextEdit* itemName = new QTextEdit();
    itemName->setStyleSheet("border:none; font: 700 14pt 'Arial';  color: white; ");
    itemWidget->layout()->addWidget(itemName);
    itemWidget->layout()->addWidget(spinBox);


    
    //This method of inserting will add the first widget at the top
    itemLayout->insertWidget(0,itemWidget);
    
    
}
void DepoPro::removeItem()
{

}

DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject::connect(
        ui.addButton, &QPushButton::clicked,this,&DepoPro::addNewItem //Connecting the adding method to a button in the 
    );

    ui.itemFrame->hide();
    ui.frame->hide();
}

DepoPro::~DepoPro()
{}
