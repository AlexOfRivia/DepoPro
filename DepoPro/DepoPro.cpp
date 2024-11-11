#include "DepoPro.h"

void DepoPro::on_addButton_pressed()
{

}
void DepoPro::on_removeButton_pressed()
{

}

DepoPro::DepoPro(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.itemScrollArea->hide();
    ui.frame->hide();
}

DepoPro::~DepoPro()
{}
