#include "MonteCarloEvaluator.h"
#include <algorithm>
#include <map>

// Constructeur : initialise le deck
MonteCarloEvaluator::MonteCarloEvaluator() {
    deck = Deck();
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

void MonteCarloEvaluator::displayCommunityCards(const std::vector<Card>& communityCards) {
    std::cout << "Community cards: ";
    for (const auto& card : communityCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;
}

long long MonteCarloEvaluator::evaluateHand(const std::vector<Card>& hand) {
    std::map<int, int> rankCount;
    std::map<Suit, int> suitCount;
    std::vector<int> values;


    for (const Card& card : hand) {
        rankCount[card.rank]++;
        suitCount[card.suit]++;
        values.push_back(card.rank);
    }

    std::sort(values.begin(), values.end(), std::greater<>());



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
    if (isFlush && isStraight) return HANDS_CATEGORY_POINT * 8 + highestInStraight;

    // Vérifier Couleur (Flush)
    if (isFlush) {
        int flushScore = HANDS_CATEGORY_POINT * 5;
        int weight = HANDS_CATEGORY_POINT / 13;
        for (int v : values) flushScore += v * weight, weight /= 13;
        return flushScore;
    }

    // Vérifier Suite (Straight)
    if (isStraight) return HANDS_CATEGORY_POINT * 4 + highestInStraight;

    // Vérifier Carré, Full House, Brelan, Paires
    int pairs = 0, three = 0, four = 0;
    int highestPair = 0, secondPair = 0, highestThree = 0, highestFour = 0;
    std::vector<int> kickers;
    for (auto& p : rankCount) {
        if (p.second == 4) { four++; highestFour = p.first; }
        if (p.second == 3) { three++; highestThree = p.first; }
        if (p.second == 2) {
            if (p.first > highestPair) {
                secondPair = highestPair;
                highestPair = p.first;
            } else if (p.first > secondPair) {
                secondPair = p.first;
            }
            pairs++;
        }
    }



    // Stocker les cartes restantes (kickers)
    for (int v : values) {
        if (v != highestFour && v != highestThree && v != highestPair && v != secondPair) {
            kickers.push_back(v);
        }
    }

    // Vérifier Carré (Four of a Kind)
    if (four) {
        int score = HANDS_CATEGORY_POINT * 7 + highestFour * HANDS_CATEGORY_POINT / 28561;
        return score;
    }

    // Vérifier Full House
    if (three && pairs) return HANDS_CATEGORY_POINT * 6 + highestThree * HANDS_CATEGORY_POINT / 2197 + highestPair;

    // Vérifier Brelan (Three of a Kind)
    if (three) {
        int score = HANDS_CATEGORY_POINT * 3 + highestThree * HANDS_CATEGORY_POINT / 2197;
        int weight = 169;
        for (int k : kickers) {
            score += k * weight;
            weight /= 13;
        }
        return score;
    }

    // Vérifier Double Paire
    if (pairs == 2) {
        int score = HANDS_CATEGORY_POINT * 2 + highestPair * HANDS_CATEGORY_POINT / 169 + secondPair * HANDS_CATEGORY_POINT / 28561 + kickers[0];
        return score;
    }

    // Vérifier Une Paire (One Pair)
    if (pairs == 1) {
        int score = HANDS_CATEGORY_POINT + highestPair * HANDS_CATEGORY_POINT / 169;
        int weight = 2197;
        for (int k : kickers) {
            score += k * weight;
            weight /= 13;
        }
        return score;
    }

    // Carte Haute (High Card)
    int score = 0;
    int weight = 371293;
    for (int k : values) {
        score += k * weight;
        weight /= 13;
    }
    return score;
}



// Simulation Monte-Carlo avec plusieurs adversaires
double MonteCarloEvaluator::evaluateHandStrength(const Hand& playerHand, long numSimulations, int numOpponents) {
    int wins = 0, total = 0;

    for (long i = 0; i < numSimulations; i++) {
        // Réinitialiser le deck et le mélanger
        deck = Deck();
        deck.shuffle();



        // Retirer les cartes du joueur du deck
        std::vector<Card> filteredDeck;
        for (const auto& card : deck.cards) {
            if ((card.rank != playerHand.cards[0].rank || card.suit != playerHand.cards[0].suit) &&
                (card.rank != playerHand.cards[1].rank || card.suit != playerHand.cards[1].suit)) {
                filteredDeck.push_back(card);
            }
        }

        deck.cards = filteredDeck;

        // Distribuer les cartes communes
        std::vector<Card> communityCards = dealCommunityCards();
        //displayCommunityCards(communityCards);

        // Générer les mains adverses
        std::vector<Hand> opponents;
        for (int j = 0; j < numOpponents; j++) {
            Hand opponentHand = dealHand();
            //opponentHand.display();
            opponents.push_back(opponentHand);
        }



        // Évaluer la main du joueur
        std::vector<Card> playerFullHand = communityCards;
        playerFullHand.push_back(playerHand.cards[0]);
        playerFullHand.push_back(playerHand.cards[1]);
        int playerScore = evaluateHand(playerFullHand);

        // Vérifier si la main du joueur est meilleure que toutes les mains adverses
        bool playerWins = true;
        for (const auto& opponentHand : opponents) {
            std::vector<Card> opponentFullHand = communityCards;
            opponentFullHand.push_back(opponentHand.cards[0]);
            opponentFullHand.push_back(opponentHand.cards[1]);
            int opponentScore = evaluateHand(opponentFullHand);

            if (opponentScore >= playerScore) {
                playerWins = false;
                //printf(("Opponent wins\n");
                //opponentHand.display();
                break; // Dès qu'un adversaire a une main égale ou meilleure, on arrête
            }
        }

        if (playerWins)
        {
            //printf("Player wins\n");
            wins++;
        }
        //else printf("Player loses\n");
        total++;
    }

    return static_cast<double>(wins) / total;
}
