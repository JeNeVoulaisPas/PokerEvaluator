//
// Created by paulo on 05/03/2025.
//

#ifndef POKEREVALUATOR_HAND_H
#define POKEREVALUATOR_HAND_H

#include <iostream>
#include "Card.h"

struct Hand {
    Card card1;
    Card card2;

    void display() const;
};

#endif // POKEREVALUATOR_HAND_H
