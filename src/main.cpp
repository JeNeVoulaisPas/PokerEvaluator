//
// Created by paulo on 17/02/2025.
//

#include <iostream>
#include "MonteCarloEvaluator.h"
#include "MT.h"

int main() {
    init_genrand(4539UL);
//    int nb_simulations = 1000000;
    int nb_simulations = 10;
    MonteCarloEvaluator evaluator;

    // Main du joueur (exemple : As-Roi)
    Hand playerHand = { {TWO, HEARTS}, {ACE, CLUBS} };

    int numOpponents;
    std::cout << "Entrez le nombre d'adversaires : ";
    std::cin >> numOpponents;

    // Calcul de la force avec Monte-Carlo
    double handStrength = evaluator.evaluateHandStrength(playerHand, nb_simulations, numOpponents);

    std::cout << "Probabilité de gagner contre " << numOpponents << " adversaire(s) : "
              << handStrength * 100 << " %" << std::endl;

    return 0;
}


