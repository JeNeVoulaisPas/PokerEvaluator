//
// Created by paulo on 05/03/2025.
//

#include "Hand.h"

void Hand::display() const {
    std::cout << "[" << card1.toString() << "] [" << card2.toString() << "]" << std::endl;
}

