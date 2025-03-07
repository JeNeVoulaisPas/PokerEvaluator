//
// Created by paulo on 05/03/2025.
//

#ifndef POKEREVALUATOR_HAND_H
#define POKEREVALUATOR_HAND_H

#include <iostream>
#include "Card.h"
#include <vector>

struct Hand {
    std::vector<Card> cards;
    void display() const;

    public:

    Hand(Card card1, Card card2) {
        cards.push_back(card1);
        cards.push_back(card2);
    }
};

#endif // POKEREVALUATOR_HAND_H
