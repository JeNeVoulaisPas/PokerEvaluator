//
// Created by paulo on 17/02/2025.
//

#ifndef POKERHANDEVALUATOR_EVALUATOR_H
#define POKERHANDEVALUATOR_EVALUATOR_H

#include <vector>
#include <unordered_map>
#include "Card.h"
#include "Deck.h"

class Evaluator {
public:
    int evaluateHand(const std::vector<Card>& hand) const;
    double calculateWinProbability(const std::vector<Card>& playerHand, int numOpponents) const;

private:
    std::unordered_map<char, int> getRankCounts(const std::vector<Card>& hand) const;
    bool hasStraight(const std::vector<Card>& hand) const;
    bool hasFlush(const std::vector<Card>& hand) const;
    void generateCombinations(const std::vector<Card>& remainingCards, std::vector<Card>& combination, int start, int depth, std::vector<std::vector<Card>>& combinations) const;
    std::vector<Card> getBestHand(const std::vector<Card>& playerCards, const std::vector<Card>& board) const;
};


#endif //POKERHANDEVALUATOR_EVALUATOR_H
