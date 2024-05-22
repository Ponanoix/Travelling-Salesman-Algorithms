//
// Created by Ponanoix on 02.11.2023.
//

#ifndef PEA_2_HELD_KARP_H
#define PEA_2_HELD_KARP_H

#include "graph-representation.h"
#include <chrono>
#include <string>
#include <vector>

class HeldKarp {
private:
    GraphRepresentation* graph;                                                                                             // Holds the representation of the graph
    int startingNode;                                                                                                       // Holds the value of the starting node
    int numCities;                                                                                                          // Number of cities
    std::vector<std::vector<int>> costMatrix;                                                                               // Cost matrix
    std::vector<int> hamiltonCycle;                                                                                         // Currently calculated path
    int distance;                                                                                                           // Cost of the current path
    std::chrono::high_resolution_clock::time_point startTime;                                                               // Algorithm's starting time
    std::chrono::high_resolution_clock::time_point endTime;                                                                 // Algorithm's finishing time
public:
    HeldKarp(GraphRepresentation* graph, int startingNode);                                                                 // Constructor
    void Start();                                                                                                           // Starts the Held-Karp algorithm
    void InitialiseCostMatrix();                                                                                            // Initialises the cost matrix from the graph representation
    int SolveTSP(int mask, int currentCity, std::vector<bool>& visited, std::vector<std::vector<int>>& dp);                 // Recursively finds the minimum costs
    void PrintResults();                                                                                                    // Prints the results of a given instance
    void beginCounting();                                                                                                   // Function to start counting time
    void finishCounting();                                                                                                  // Function to stop counting time
    void ReconstructOptimalTour(int mask, int currentCity, std::vector<bool>& visited, std::vector<std::vector<int>>& dp);  // Reconstructs the optimal tour (Hamiltonian cycle)
    int time{};                                                                                                             // Time to finish an instance of an algorithm
    int distancePublic{};                                                                                                   // Cost of the current path
    std::vector<int> hamiltonianCycle;                                                                                      // Currently calculated path
};

#endif //PEA_2_HELD_KARP_H
