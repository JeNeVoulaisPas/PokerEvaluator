//
// Created by paulo on 17/02/2025.
//

#ifndef POKERHANDEVALUATOR_DECK_H
#define POKERHANDEVALUATOR_DECK_H


#include <vector>
#include "Card.h"

class Deck {
public:
    std::vector<Card> cards;

    Deck();
    void shuffle();
    Card draw();
};


#endif //POKERHANDEVALUATOR_DECK_H
