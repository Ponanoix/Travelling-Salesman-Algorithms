//
// Created by Ponanoix on 18.12.2023.
//

#ifndef PEA_3_SIMULATED_ANNEALING_H
#define PEA_3_SIMULATED_ANNEALING_H

#include "graph-representation.h"
#include <vector>
#include <chrono>

enum CoolingSchedule {
    GEOMETRIC,
    LINEAR
};
enum TemperatureMethod{
    SET,
    ADAPTIVE
};
enum NeighbourhoodExploration{
    RANDOM,
    GREEDY
};
enum NeighbourhoodSolution{
    TWO_SWAP,
    REVERSAL
};

class SimulatedAnnealing {
private:
    // Graph initials
    GraphRepresentation *graph;
    int startingNode;
    CoolingSchedule coolingSchedule;                                                        // Choose the cooling schedule
    TemperatureMethod temperature;                                                          // Choose the method of initialising temperature
    NeighbourhoodExploration explorationMethod;                                             // Choose the method of exploring the neighbourhood
    NeighbourhoodSolution solutionMethod;                                                   // Choose the method of generating new solution

    // Parameters and state variables
    double currentTemperature{};
    double coolingRate{};
    int maxIterations{};
    std::chrono::high_resolution_clock::time_point startTime;                               // Algorithm's starting time
    std::chrono::high_resolution_clock::time_point endTime;                                 // Algorithm's finishing time
    std::vector<int> hamiltonianCycle;
    int distance{};

    // Internal methods
    void initializeParameters(std::vector<int>& solution);                                  // Initialize algorithm parameters
    void updateTemperature();                                                               // Update temperature based on cooling schedule
    void generateRandomSolution(std::vector<int>& solution);                                // Generate a random initial solution
    int calculateTotalDistance(const std::vector<int>& solution);                           // Calculate total distance of a solution
    double acceptanceProbability(int currentDistance, int newDistance, double temperature); // Calculate acceptance probability
    int calculateSwapDelta(const std::vector<int>& solution, int i, int j);
    int calculateReversalDelta(const std::vector<int>& solution, int start, int end);
    void neighbourhoodSolutionMethod(std::vector<int>& solution);                           // Determines which NSM to choose:
    void apply2Swap(std::vector<int>& solution);                                            // Apply 2-swap to the solution
    void applyReversal(std::vector<int>& solution);                                         // Apply reversal to the solution
    double calculateAdaptiveTemperature(std::vector<int>& solution, float initialProbability); // Calculates adaptive temperature

public:
    // Constructor
    SimulatedAnnealing(GraphRepresentation *graph, int startingNode, CoolingSchedule coolingSchedule, TemperatureMethod temperature, NeighbourhoodExploration explorationMethod, NeighbourhoodSolution neighbourhoodSolution);

    void Start();                                                                           // Main method to start the simulated annealing algorithm

    void PrintResults();                                                                    // Nicely prints the results

    // Accessors for retrieving results
    // Time
    double time{};
    void beginCounting();                                                                   // Function to start counting time
    void finishCounting();                                                                  // Function to stop counting time

    // Distance
    int distancePublic{};                                                                   // Cost of the current path

    // Cycle
    std::vector<int> hamiltonianCyclePublic;                                                // Currently calculated path
};

#endif //PEA_3_SIMULATED_ANNEALING_H
