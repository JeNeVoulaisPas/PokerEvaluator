//
// Created by paulo on 17/02/2025.
//

#include <algorithm>
#include "Deck.h"
#include "MT.h"

Deck::Deck() {
    for (int r = TWO; r <= ACE; r++) {
        for (int s = HEARTS; s <= SPADES; s++) {
            cards.push_back({ static_cast<Rank>(r), static_cast<Suit>(s) });
        }
    }
}

void Deck::shuffle() {
    // Mélange du deck avec le générateur de nombres aléatoires
    for (size_t i = cards.size() - 1; i > 0; i--) {
        size_t j = genrand_int32() % (i + 1);
        std::swap(cards[i], cards[j]);
    }
}

Card Deck::draw() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

