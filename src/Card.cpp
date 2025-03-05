//
// Created by paulo on 17/02/2025.
//

#include "Card.h"

Card::Card(const std::string& r, const std::string& s) : rank(r), suit(s) {}

bool Card::operator<(const Card& other) const {
    static const std::string ranks = "23456789TJQKA";
    return ranks.find(rank) < ranks.find(other.rank);
}
