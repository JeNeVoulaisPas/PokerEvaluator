//
// Created by paulo on 17/02/2025.
//

#ifndef POKERHANDEVALUATOR_CARD_H
#define POKERHANDEVALUATOR_CARD_H


#include <string>

struct Card {
    std::string rank;
    std::string suit;

    Card(const std::string& r, const std::string& s);
    bool operator<(const Card& other) const;
};


#endif //POKERHANDEVALUATOR_CARD_H
