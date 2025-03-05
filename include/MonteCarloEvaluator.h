#ifndef POKEREVALUATOR_MONTECARLOEVALUATOR_H
#define POKEREVALUATOR_MONTECARLOEVALUATOR_H

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

class MonteCarloEvaluator {
public:
    MonteCarloEvaluator(); // Constructeur

    double evaluateHandStrength(const Hand& playerHand, int numSimulations = 10000, int numOpponents = 1);

private:
    Deck deck; // Deck de cartes

    int evaluateHand(const std::vector<Card>& hand);
    Hand dealHand();
    std::vector<Card> dealCommunityCards();
    void displayCommunityCards(const std::vector<Card>& communityCards);
};

#endif // POKEREVALUATOR_MONTECARLOEVALUATOR_H
