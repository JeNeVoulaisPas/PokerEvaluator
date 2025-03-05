//
// Created by paulo on 17/02/2025.
//

#include "Deck.h"
#include <algorithm>
#include <random>

#include "Deck.h"
#include <algorithm>
#include <random>

Deck::Deck() {
    std::string ranks = "23456789TJQKA";
    std::string suits = "hdcs";
    for (char suit : suits) {
        for (char rank : ranks) {
            cards.emplace_back(std::string(1, rank), std::string(1, suit));
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::draw() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

