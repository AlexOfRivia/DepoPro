#include "DepoPro.h"

void DepoPro::addNewItem()
{
    QVBoxLayout* itemLayout = qobject_cast<QVBoxLayout*>(ui.itemFrame->layout());

    QPushButton* button = new QPushButton("Hello", ui.itemFrame);
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
        ui.addButton, &QPushButton::clicked,this,&DepoPro::addNewItem
    );

    ui.itemFrame->hide();
    ui.frame->hide();
}

DepoPro::~DepoPro()
{}
