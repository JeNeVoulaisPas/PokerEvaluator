cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(PokerEvaluator)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 20)

# Ajouter les dossiers include
include_directories(include)

# Ajouter les fichiers sources
set(SOURCES
        src/Card.cpp
        src/Deck.cpp
        src/Evaluator.cpp
        src/main.cpp
)

# Ajouter l'exécutable
add_executable(PokerEvaluator ${SOURCES})
