#include "orderItem.h"

//Constructor
orderItem::orderItem()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Generate a random number in the range [0, 899999] and add 100000
    orderID =  std::rand() % 900000 + 100000;
}

//Destructor
orderItem::~orderItem()
{

}
