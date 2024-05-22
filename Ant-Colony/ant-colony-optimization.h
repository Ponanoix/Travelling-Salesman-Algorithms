//
// Created by Ponanoix on 21.01.2024.
//

#ifndef PEA_4_ANT_COLONY_OPTIMIZATION_H
#define PEA_4_ANT_COLONY_OPTIMIZATION_H

#include "graph-representation.h"
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

// Different pheromone generation schematics for the algorithm
enum PheromoneSchematic {
    DAS,
    QAS,
    CAS
};

// Different heuristics regarding choice of a following node
enum Heuristics {
    VISIBILITY,
    LOGARITHMIC
};

class AntColonyOptimization{
private:
    // Alpha - Coefficient of influence of the amount of pheromone
    // on the probability of choosing a node
    int alphaParameter{};

    // Beta - Coefficient of influence of distance
    // on the probability of choosing a node
    int betaParameter{};

    // Rho - Coefficient of pheromone evaporation
    float rhoParameter{};

    // Number of ants that traverse the graph during each iteration
    float numberOfAnts{};

    // Tau - Coefficient of pheromone on an edge
    std::vector<std::vector<float>> tauCoefficient{};

    //Raw value for tau coefficient to add to every edge
    float tauCoefficientValue{};

    // Eta - Heuristics of the local choice
    float etaCoefficient{};

    // Starting and ending node for an ant in an iteration
    int startingNode{};

    // High Resolution Clock's time when algorithm starts
    std::chrono::high_resolution_clock::time_point startingTime;

    // High Resolution Clock's time when algorithm ends
    std::chrono::high_resolution_clock::time_point endingTime;

    // Number of iterations the algorithm takes
    int numberOfIterations{};

    // Raw amount of pheromone an ant leaves behind
    int amountOfPheromone{};

    // Pointer to a graph
    GraphRepresentation *graphRepresentation;

    // Whether to use parameters set in advance or to have user manually input them
    bool userInput{};

    // Probability that an ant would choose this node
    float probabilityOfChoice{};

    // Variable to differentiate between pheromone schematics
    PheromoneSchematic pheromoneSchematic;

    // Type of heuristics used to determine next choice
    Heuristics heuristics;
public:
    // Constructor for the algorithm
    AntColonyOptimization(GraphRepresentation *graphRepresentation,
                          bool userInput,
                          PheromoneSchematic pS,
                          int alpha,
                          int beta,
                          float rho,
                          Heuristics hs);

    // This function uses the nearest neighbour algorithm to estimate
    // the shortest Hamiltonian cycle (used to initialise tau parameter)
    float calculateEstimatedDistance();

    // Begins the counting process, executed before everything else in the algorithm
    void beginCounting();

    // Ends the counting process, executed after the algorithm is finished
    void finishCounting();

    // Calculates the time it took for the algorithm to finish
    void printResults();

    // Randomises the starting node for the ant
    int randomiseStartingNode();

    // Starts the algorithm
    void startTheAlgorithm();

    // Cues the user with request to initialise parameters
    void initialiseParameters();

    // Randomises the next node ant will travel to
    static float randomiseNextChoice();

    // Calculates tau coefficient for every edge
    void calculateTauCoefficient();

    // Distance of the hamiltonian cycle
    int distancePublic{};

    // Time it took to execute the entire algorithm
    int time{};

    // Cycle (hamiltonian cycle)
    std::vector<int> hamiltonianCycle;

    // Variable to hold current shortest distance
    int currentBestDistance{};
};

#endif //PEA_4_ANT_COLONY_OPTIMIZATION_H
