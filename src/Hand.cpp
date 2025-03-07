//
// Created by paulo on 05/03/2025.
//

#include "Hand.h"

void Hand::display() const {
    for (const auto& card : cards) {
        std::cout << card.toString() << " ";
    }
}

