#ifndef POKEREVALUATOR_MONTECARLOEVALUATOR_H
#define POKEREVALUATOR_MONTECARLOEVALUATOR_H

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

static long iter = 0;

class MonteCarloEvaluator {
public:
    MonteCarloEvaluator(); // Constructeur

    double evaluateHandStrength(const Hand& playerHand, long numSimulations, int numOpponents = 1);

    static const int HANDS_CATEGORY_POINT = 4826809; // 13^6

private:
    Deck deck; // Deck de cartes


    static long long evaluateHand(const std::vector<Card>& hand);
    Hand dealHand();
    std::vector<Card> dealCommunityCards();
    void displayCommunityCards(const std::vector<Card>& communityCards);
};

#endif // POKEREVALUATOR_MONTECARLOEVALUATOR_H
