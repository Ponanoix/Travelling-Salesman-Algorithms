//
// Created by Ponanoix on 02.11.2023.
//

#include "held-karp.h"
#include <iostream>
#include <vector>

// Constructor - Initialises the algorithm with a graph representation and a starting node
HeldKarp::HeldKarp(GraphRepresentation *graph, int startingNode) {
    // Representation of the graph
    this -> graph = graph;

    // City (node) from which the algorithm begins
    this -> startingNode = startingNode;

    // Number of cities (nodes) in a graph
    this -> numCities = graph -> getNodeSize();

    // Distances between two cities
    costMatrix.resize(numCities, std::vector<int>(numCities, 0));
}


// Core of the algorithm, calls all the functions necessary
void HeldKarp::Start() {
    // Start counting
    beginCounting();

    // Initialisation of the matrix to store distances
    InitialiseCostMatrix();

    // Create a bitmask to track visited cities, excluding the starting node
    std::vector<bool> visited(numCities, false);
    visited[startingNode] = true;

    // Initialise the memoisation table
    std::vector<std::vector<int>> dp(1 << numCities, std::vector<int>(numCities, -1));

    // Start from the starting node and recursively find the minimum cost
    distance = SolveTSP(1 << startingNode, startingNode, visited, dp);

    // Reconstruct the optimal tour (Hamiltonian cycle)
    ReconstructOptimalTour(1 << startingNode, startingNode, visited, dp);

    //Stop counting
    finishCounting();

    // Print the results
    PrintResults();
}


// This function recursively finds minimum distance between two cities
int HeldKarp::SolveTSP(int mask, int currentCity, std::vector<bool> &visited, std::vector<std::vector<int>> &dp) {
    // Check if all cities have been visited
    if(mask == (1 << numCities) - 1) return costMatrix[currentCity][startingNode];

    // Check if the result is already memoised.
    if(dp[mask][currentCity] != -1) return dp[mask][currentCity];


    int minCost = INT_MAX;
    for(int nextCity = 0; nextCity < numCities; nextCity++){
        if(!visited[nextCity]){
            visited[nextCity] = true;
            int newMask = mask | (1 << nextCity);
            int cost = costMatrix[currentCity][nextCity] + SolveTSP(newMask, nextCity, visited, dp);
            minCost = std::min(minCost, cost);
            visited[nextCity] = false;
        }
    }

    // Memoise the result
    dp[mask][currentCity] = minCost;
    return minCost;
}


// Initialises the cost matrix from the graph representation
void HeldKarp::InitialiseCostMatrix() {
    for(int i = 0; i < numCities; i++){
        for(int j = 0; j < numCities; j++){
            costMatrix[i][j] = graph -> getWeight(i, j);
        }
    }
}

// Reconstructs the optimal tour (Hamiltonian cycle)
void HeldKarp::ReconstructOptimalTour(int mask, int currentCity, std::vector<bool> &visited,
                                      std::vector<std::vector<int>> &dp) {
    // Find the next city to visit in the optimal tour
    hamiltonCycle.push_back(startingNode);
    while(true){
        int bestNextCity = -1;
        int minCost = INT_MAX;

        for(int nextCity = 0; nextCity < numCities; nextCity++){
            if(!visited[nextCity]){
                int newMask = mask | (1 << nextCity);
                int cost = costMatrix[currentCity][nextCity] + dp[newMask][nextCity];

                if(cost < minCost){
                    minCost = cost;
                    bestNextCity = nextCity;
                }
            }
        }

        if(bestNextCity == -1){
            break; // All cities have been visited
        }

        // Update the tour
        hamiltonCycle.push_back(bestNextCity);
        visited[bestNextCity] = true;
        mask |= (1 << bestNextCity);
        currentCity = bestNextCity;
    }
    hamiltonCycle.push_back(startingNode);
}


void HeldKarp::PrintResults() {
    // Time
    int timeToDo;
    if(graph -> getNodeSize() <= 12) timeToDo = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    else if(graph -> getNodeSize() <= 20) timeToDo = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    else timeToDo = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    time = timeToDo;
    distancePublic = distance;
    hamiltonianCycle = hamiltonCycle;
    // Prints the minimum cost, the optimal tour and the time
    std::cout << "Minimum cost: " << distance << std::endl;
    std::cout << "Optimal tour: ";
    for(int city : hamiltonCycle){
        std::cout << city << " ";
    }
    std::cout << std::endl;
    if(graph -> getNodeSize() <= 12) std::cout << "Time: " << timeToDo << " microseconds" << std::endl;
    else if(graph -> getNodeSize() <= 20) std::cout << "Time: " << timeToDo << " milliseconds" << std::endl;
    else std::cout << "Time: " << timeToDo << " seconds" << std::endl;
}

// Both functions measure time which is later calculated
void HeldKarp::beginCounting() {
    startTime = std::chrono::high_resolution_clock::now();
}

void HeldKarp::finishCounting() {
    endTime = std::chrono::high_resolution_clock::now();
}