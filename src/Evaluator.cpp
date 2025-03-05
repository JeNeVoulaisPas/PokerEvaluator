//
// Created by paulo on 17/02/2025.
//

#include "Evaluator.h"
#include <unordered_map>
#include <iostream>
#include <random>

// Fonction pour compter les occurrences de chaque rang dans la main
std::unordered_map<char, int> Evaluator::getRankCounts(const std::vector<Card>& hand) const {
    std::unordered_map<char, int> rankCounts;
    for (const auto& card : hand) {
        rankCounts[card.rank[0]]++;
    }
    return rankCounts;
}

// Fonction pour vérifier si la main contient une suite
bool Evaluator::hasStraight(const std::vector<Card>& hand) const {
    std::string ranks = "23456789TJQKA";
    std::vector<int> rankIndices;
    for (const auto& card : hand) {
        rankIndices.push_back(ranks.find(card.rank));
    }
    std::sort(rankIndices.begin(), rankIndices.end());
    for (size_t i = 0; i < rankIndices.size() - 1; ++i) {
        if (rankIndices[i] + 1 != rankIndices[i + 1]) {
            return false;
        }
    }
    return true;
}

// Fonction pour vérifier si la main contient une couleur
bool Evaluator::hasFlush(const std::vector<Card>& hand) const {
    std::unordered_map<char, int> suitCounts;
    for (const auto& card : hand) {
        suitCounts[card.suit[0]]++;
    }
    for (const auto& pair : suitCounts) {
        if (pair.second >= 5) {
            return true;
        }
    }
    return false;
}

// Fonction pour évaluer la force d'une main de 5 cartes
int Evaluator::evaluateHand(const std::vector<Card>& hand) const {
    auto rankCounts = getRankCounts(hand);
    bool straight = hasStraight(hand);
    bool flush = hasFlush(hand);

    // Vérifier les combinaisons de poker
    if (straight && flush) {
        return 9; // Straight Flush
    }
    for (const auto& pair : rankCounts) {
        if (pair.second == 4) {
            return 8; // Four of a Kind
        }
    }
    if (rankCounts.size() == 2) {
        return 7; // Full House
    }
    if (flush) {
        return 6; // Flush
    }
    if (straight) {
        return 5; // Straight
    }
    if (rankCounts.size() == 3) {
        for (const auto& pair : rankCounts) {
            if (pair.second == 3) {
                return 4; // Three of a Kind
            }
        }
        return 3; // Two Pair
    }
    if (rankCounts.size() == 4) {
        return 2; // One Pair
    }
    return 1; // High Card
}

// Fonction pour générer toutes les combinaisons possibles de cartes restantes
void Evaluator::generateCombinations(const std::vector<Card>& remainingCards, std::vector<Card>& combination, int start, int depth, std::vector<std::vector<Card>>& combinations) const {
    if (depth == 0) {
        combinations.push_back(combination);
        return;
    }
    for (int i = start; i <= remainingCards.size() - depth; ++i) {
        combination.push_back(remainingCards[i]);
        generateCombinations(remainingCards, combination, i + 1, depth - 1, combinations);
        combination.pop_back();
    }
}

// Fonction pour sélectionner la meilleure main de 5 cartes parmi les 7 disponibles
std::vector<Card> Evaluator::getBestHand(const std::vector<Card>& playerCards, const std::vector<Card>& board) const {
    std::vector<Card> allCards = playerCards;
    allCards.insert(allCards.end(), board.begin(), board.end());
    std::vector<Card> combination;
    std::vector<std::vector<Card>> combinations;
    generateCombinations(allCards, combination, 0, 5, combinations);

    std::vector<Card> bestHand;
    int bestScore = 0;
    for (const auto& comb : combinations) {
        int score = evaluateHand(comb);
        if (score > bestScore) {
            bestScore = score;
            bestHand = comb;
        }
    }
    return bestHand;
}

// Fonction pour calculer les probabilités de victoire en utilisant une approche brute-force
double Evaluator::calculateWinProbability(const std::vector<Card>& playerHand, int numOpponents) const {
    Deck deck;
    std::vector<Card> remainingCards;
    std::cout << "Calculating win probability..." << std::endl;
    for (const auto& card : deck.cards) {
        bool found = false;
        for (const auto& playerCard : playerHand) {
            if (card.rank == playerCard.rank && card.suit == playerCard.suit) {
                found = true;
                break;
            }
        }
        if (!found) {
            remainingCards.push_back(card);
        }
    }
    std::cout << "Remaining cards: " << remainingCards.size() << std::endl;

    std::vector<Card> combination;
    std::vector<std::vector<Card>> combinations;
    generateCombinations(remainingCards, combination, 0, 5, combinations);

    int wins = 0;
    int total = combinations.size();

    std::cout << "Total combinations: " << total << std::endl;

    for (const auto& board : combinations) {
        std::vector<Card> bestPlayerHand = getBestHand(playerHand, board);
        int playerScore = evaluateHand(bestPlayerHand);
        bool playerWins = true;

        for (int i = 0; i < numOpponents; ++i) {
            std::vector<Card> opponentHand;
            std::vector<Card> tempRemainingCards = remainingCards;
            std::shuffle(tempRemainingCards.begin(), tempRemainingCards.end(), std::mt19937{std::random_device{}()});
            opponentHand.push_back(tempRemainingCards.back());
            tempRemainingCards.pop_back();
            opponentHand.push_back(tempRemainingCards.back());
            tempRemainingCards.pop_back();

            std::vector<Card> bestOpponentHand = getBestHand(opponentHand, board);
            int opponentScore = evaluateHand(bestOpponentHand);
            if (opponentScore >= playerScore) {
                playerWins = false;
                break;
            }
        }

        if (playerWins) {
            wins++;
        }
    }

    std::cout << "Wins: " << wins << std::endl;

    return static_cast<double>(wins) / total;
}

