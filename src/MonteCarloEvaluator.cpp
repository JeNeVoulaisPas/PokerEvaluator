#include "MonteCarloEvaluator.h"
#include <algorithm>
#include <map>

// Constructeur : initialise le deck
MonteCarloEvaluator::MonteCarloEvaluator() {
    deck.shuffle();
}

// Distribution d'une main de 2 cartes
Hand MonteCarloEvaluator::dealHand() {
    return { deck.draw(), deck.draw() };
}

// Distribution des cartes communes (Flop + Turn + River)
std::vector<Card> MonteCarloEvaluator::dealCommunityCards() {
    std::vector<Card> communityCards;
    for (int i = 0; i < 5; i++) {
        communityCards.push_back(deck.draw());
    }
    return communityCards;
}

// Fonction d'évaluation améliorée de la main
int MonteCarloEvaluator::evaluateHand(const std::vector<Card>& hand) {
    std::map<int, int> rankCount;
    std::map<Suit, int> suitCount;
    std::vector<int> values;

    for (const Card& card : hand) {
        rankCount[card.rank]++;
        suitCount[card.suit]++;
        values.push_back(card.rank);
    }

    std::sort(values.begin(), values.end(), std::greater<int>());

    // Vérifier une couleur (Flush)
    bool isFlush = std::any_of(suitCount.begin(), suitCount.end(), [](auto& p) { return p.second >= 5; });

    // Vérifier une suite (Straight)
    bool isStraight = false;
    int consecutive = 1, highestInStraight = values[0];
    for (size_t i = 1; i < values.size(); i++) {
        if (values[i] == values[i - 1] - 1) {
            consecutive++;
            if (consecutive >= 5) {
                isStraight = true;
                highestInStraight = values[i - 4];
                break;
            }
        } else if (values[i] != values[i - 1]) {
            consecutive = 1;
        }
    }

    // Vérifier Quinte Flush
    if (isFlush && isStraight) return 900 + highestInStraight;
    if (isFlush) return 600 + values[0];
    if (isStraight) return 500 + highestInStraight;

    // Vérifier Carré, Full House, Brelan, Paires
    int pairs = 0, three = 0, four = 0, highestPair = 0, highestThree = 0, highestFour = 0;
    for (auto& p : rankCount) {
        if (p.second == 4) { four++; highestFour = p.first; }
        if (p.second == 3) { three++; highestThree = p.first; }
        if (p.second == 2) { pairs++; highestPair = std::max(highestPair, p.first); }
    }
    if (four) return 800 + highestFour;
    if (three && pairs) return 700 + highestThree * 2 + highestPair;
    if (three) return 400 + highestThree;
    if (pairs == 2) return 300 + highestPair;
    if (pairs == 1) return 200 + highestPair;

    return 100 + values[0]; // Carte haute
}

// Simulation Monte-Carlo avec plusieurs adversaires
double MonteCarloEvaluator::evaluateHandStrength(const Hand& playerHand, int numSimulations, int numOpponents) {
    int wins = 0, total = 0;

    for (int i = 0; i < numSimulations; i++) {
        // Réinitialiser le deck et le mélanger
        deck = Deck();
        deck.shuffle();

        // Retirer les cartes du joueur du deck
        std::vector<Card> filteredDeck;
        for (const auto& card : deck.cards) {
            if ((card.rank != playerHand.card1.rank || card.suit != playerHand.card1.suit) &&
                (card.rank != playerHand.card2.rank || card.suit != playerHand.card2.suit)) {
                filteredDeck.push_back(card);
            }
        }
        deck.cards = filteredDeck;

        // Distribuer les cartes communes
        std::vector<Card> communityCards = dealCommunityCards();

        // Générer les mains adverses
        std::vector<Hand> opponents;
        for (int j = 0; j < numOpponents; j++) {
            opponents.push_back(dealHand());
        }

        // Évaluer la main du joueur
        std::vector<Card> playerFullHand = communityCards;
        playerFullHand.push_back(playerHand.card1);
        playerFullHand.push_back(playerHand.card2);
        int playerScore = evaluateHand(playerFullHand);

        // Vérifier si la main du joueur est meilleure que toutes les mains adverses
        bool playerWins = true;
        for (const auto& opponentHand : opponents) {
            std::vector<Card> opponentFullHand = communityCards;
            opponentFullHand.push_back(opponentHand.card1);
            opponentFullHand.push_back(opponentHand.card2);
            int opponentScore = evaluateHand(opponentFullHand);

            if (opponentScore >= playerScore) {
                playerWins = false;
                break; // Dès qu'un adversaire a une main égale ou meilleure, on arrête
            }
        }

        if (playerWins) wins++;
        total++;
    }

    return static_cast<double>(wins) / total;
}
