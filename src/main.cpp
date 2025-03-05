//
// Created by paulo on 17/02/2025.
//

#include <iostream>
#include "Evaluator.h"
#include "Card.h"

int main() {
    Evaluator evaluator;
    std::vector<Card> playerHand = {Card("2", "s"), Card("7", "h")};
    int numOpponents = 3;

    double winProbability = evaluator.calculateWinProbability(playerHand, numOpponents);
    std::cout << "Win probability: " << winProbability * 100 << "%" << std::endl;

    return 0;
}

