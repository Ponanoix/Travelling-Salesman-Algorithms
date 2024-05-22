//
// Created by Ponanoix on 18.10.2023.
//

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "graph-representation.h"
#include <chrono>
#include <string>
#include <vector>

class BruteForce {
private:
    int* permutation;                                           // Holds data regarding the current permutation

    GraphRepresentation* graph;                                 // Holds the representation of the graph

    int startNode;                                              // Holds the value of the starting node

    int permutationSize;                                        // Holds the size of the current permutation


public:
    BruteForce(GraphRepresentation* graph, int startVertex);    // Constructor of the BruteForce algorithm class

    void Start();                                               // Starts the algorithm and prepares data

    void InitializePermutation();                               // Begins the first permutation in the problem

    int CalculatePathLength();                                  // Calculates the cost of a given path

    void CopyPermutation(int *destination);                     // Duplicates the current permutation

    void PrintResults(int minPath, int *minPermutation);        // Prints the results regarding a given instance

    std::chrono::high_resolution_clock::time_point startTime;   // Starting time

    std::chrono::high_resolution_clock::time_point endTime;     // Ending time

    void beginCounting();                                       // Function to start counting

    void finishCounting();                                      // Function to stop counting

    std::vector<int> hamiltonCycle;                             // Currently calculated path

    int time{};                                                 // Time to finish one instance

    int distance{};                                             // Cost of the current path
private:
    bool GetNextPermutation();                                  // Generates next permutation of cities
};

#endif // BRUTE_FORCE_H
