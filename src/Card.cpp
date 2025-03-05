//
// Created by paulo on 17/02/2025.
//

#include "Card.h"

std::string Card::toString() const {
    std::string rankStr;
    switch (rank) {
        case TWO: rankStr = "2"; break;
        case THREE: rankStr = "3"; break;
        case FOUR: rankStr = "4"; break;
        case FIVE: rankStr = "5"; break;
        case SIX: rankStr = "6"; break;
        case SEVEN: rankStr = "7"; break;
        case EIGHT: rankStr = "8"; break;
        case NINE: rankStr = "9"; break;
        case TEN: rankStr = "10"; break;
        case JACK: rankStr = "J"; break;
        case QUEEN: rankStr = "Q"; break;
        case KING: rankStr = "K"; break;
        case ACE: rankStr = "A"; break;
    }

    std::string suitStr;
    switch (suit) {
        case HEARTS: suitStr = "♥"; break;
        case DIAMONDS: suitStr = "♦"; break;
        case CLUBS: suitStr = "♣"; break;
        case SPADES: suitStr = "♠"; break;
    }

    return rankStr + suitStr;
}

