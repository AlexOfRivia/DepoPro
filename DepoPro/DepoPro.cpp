#include "DepoPro.h"

void DepoPro::addNewItem()
{
    //Adds a vertical layout to the frame
    QVBoxLayout* itemLayout = qobject_cast<QVBoxLayout*>(ui.itemFrame->layout());

    //Initializing the added withet (BUtton is for testing)
    QPushButton* button = new QPushButton("Hello", ui.itemFrame);

    //This method of inserting will add the first widget at the top
    itemLayout->insertWidget(0,button);
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
