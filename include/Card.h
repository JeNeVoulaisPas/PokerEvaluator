//
// Created by paulo on 17/02/2025.
//

#ifndef POKERHANDEVALUATOR_CARD_H
#define POKERHANDEVALUATOR_CARD_H

#include <string>

enum Rank { TWO = 0, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

struct Card {
    Rank rank;
    Suit suit;

    std::string toString() const; // Ajout de la méthode toString()
};

#endif // POKERHANDEVALUATOR_CARD_H
