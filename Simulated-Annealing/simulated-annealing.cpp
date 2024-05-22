//
// Created by Ponanoix on 18.12.2023.
//

#include "simulated-annealing.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>
int revokedWorse = 0;
int acceptedWorse = 0;

// Constructor
SimulatedAnnealing::SimulatedAnnealing(GraphRepresentation *graph, int startingNode, CoolingSchedule cs, TemperatureMethod tm, NeighbourhoodExploration ne, NeighbourhoodSolution ns) {
    // Representation of the graph
    this -> graph = graph;

    // City (node) from which the algorithm begins
    this -> startingNode = startingNode;

    // Set the chosen values of these two enums to variables
    coolingSchedule = cs;
    temperature = tm;
    explorationMethod = ne;
    solutionMethod = ns;
}

// Main method to start the simulated annealing algorithm
void SimulatedAnnealing::Start() {
    // Initialize algorithm parameters
    std::vector<int> randomSolution;
    initializeParameters(randomSolution);

    // Start counting
    beginCounting();

    // Generate a random initial solution
    std::vector<int> currentSolution;
    generateRandomSolution(currentSolution);

    // Track the best solution
    hamiltonianCycle = currentSolution;
    distance = calculateTotalDistance(hamiltonianCycle);

    // Main simulated annealing loop
    for (int iteration = 0; iteration < maxIterations; iteration++) {
        // Update temperature based on cooling schedule
        updateTemperature();
        for(int i = 0; i < graph -> getNodeSize(); i++) {
            // Apply neighborhood solution method
            neighbourhoodSolutionMethod(currentSolution);

            // Calculate total distance of the new solution
            int currentDistance = calculateTotalDistance(currentSolution);

            // Check if the new solution is better or should be accepted probabilistically
            if (currentDistance < distance ||
                acceptanceProbability(distance, currentDistance, currentTemperature) > (rand() % 1000) / 1000.0) {
                // Update the best solution
                if(currentDistance > distance) acceptedWorse++;;
                hamiltonianCycle = currentSolution;
                distance = currentDistance;
            } else revokedWorse++;
        }
    }

    // Stop counting
    finishCounting();

    // Print the final best solution
    PrintResults();
}

// Initialize algorithm parameters
void SimulatedAnnealing::initializeParameters(std::vector<int>& solution) {
    // Set initial temperature, cooling rate, and maximum iterations
    switch (temperature) {
        case SET: {
            double chosenTemperature;
            std::cout << "Enter the initial temperature: ";
            std::cin >> chosenTemperature;
            std::cout << std::endl;
            currentTemperature = chosenTemperature;
            currentTemperature = 1000;
            break;
        }
        case ADAPTIVE: {
            float initialProbability = 0.95;
//            std::cout << "Enter the initial probability of acceptance: ";
//            std::cin >> initialProbability;
//            std::cout << std::endl;
            currentTemperature = calculateAdaptiveTemperature(solution, initialProbability);
            break;
        }
        default:
            throw std::invalid_argument("Error regarding initial temperature method");
    }
    std::cout << "Initial temperature: " << currentTemperature << std::endl;
    coolingRate = 0.95;
    maxIterations = 30000;
}

// Update temperature based on cooling schedule
void SimulatedAnnealing::updateTemperature() {
    switch (coolingSchedule){
        case GEOMETRIC: {
            currentTemperature *= (1.0 - coolingRate);
            break;
        }
        case LINEAR: {
            currentTemperature -= coolingRate;
            break;
        }
        default:
            throw std::invalid_argument("Error regarding cooling method");
    }
}

// Generate a random initial solution
void SimulatedAnnealing::generateRandomSolution(std::vector<int>& solution) {
    // Initialize solution with a random permutation of nodes
    solution.clear();
    for (int i = 0; i < graph->getNodeSize(); ++i) {
        solution.push_back(i);
    }
    std::shuffle(solution.begin(), solution.end(), std::mt19937(std::random_device()()));
}

double SimulatedAnnealing::calculateAdaptiveTemperature(std::vector<int>& solution, float initialProbability) {
    int size;
    if(graph -> getNodeSize() == 1) size = 1;
    else if(graph -> getNodeSize() == 2) size = 2;
    else if(graph -> getNodeSize() == 3) size = 6;
    else if(graph -> getNodeSize() == 4) size = 20;
    else if(graph -> getNodeSize() == 5) size = 100;
    else if(graph -> getNodeSize() == 6) size = 700;
    else if(graph -> getNodeSize() == 7) size = 5000;
    else size = 10000;

    int arrayOfSolutions[size];
    for(int i = 0; i < size; i++){
        arrayOfSolutions[i] = INT_MAX;
    }
    std::vector<int> newSolution;
    int tempDistance;
    int tempNewDistance;

    for(int i = 0; i < size; i++) {
        generateRandomSolution(solution);
        tempDistance = calculateTotalDistance(solution);
        neighbourhoodSolutionMethod(solution);
        newSolution = solution;
        tempNewDistance = calculateTotalDistance(newSolution);
        arrayOfSolutions[i] = abs(tempDistance - tempNewDistance);
    }
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += arrayOfSolutions[i];
    }
    int average = sum / size;
    double adaptiveTemperature = -average/(std::log(initialProbability));
    return std::round(adaptiveTemperature);
}

// Calculate total distance of a solution
int SimulatedAnnealing::calculateTotalDistance(const std::vector<int>& solution) {
    int totalDistance = 0;
    for (size_t i = 0; i < solution.size() - 1; ++i) {
        totalDistance += graph -> getWeight(solution[i], solution[i + 1]);
    }
    totalDistance += graph -> getWeight(solution.back(), solution.front()); // Return to starting node
    return totalDistance;
}

// Calculate acceptance probability
double SimulatedAnnealing::acceptanceProbability(int currentDistance, int newDistance, double temperature) {
    if (newDistance < currentDistance) {
        return 1.0; // Accept better solution
    } else {
        return exp((currentDistance - newDistance) / temperature);
    }
}

void SimulatedAnnealing::neighbourhoodSolutionMethod(std::vector<int> &solution) {
    switch (solutionMethod) {
        case TWO_SWAP: {
            apply2Swap(solution);
            break;
        }
        case REVERSAL: {
            applyReversal(solution);
            break;
        }
        default:
            throw std::invalid_argument("Error regarding neighbourhood solution method");
    }
}

// Apply 2-swap to the solution
void SimulatedAnnealing::apply2Swap(std::vector<int>& solution) {
    // Perform a 2-swap operation on the solution
    switch (explorationMethod){
        case RANDOM: {
            // Perform a 2-swap operation on the solution randomly
            int size = solution.size();
            int i = rand() % size;
            int j = rand() % size;
            std::swap(solution[i], solution[j]);
            break;
        }
        case GREEDY: {
            // Perform a 2-swap operation on the solution greedily
            int size = solution.size();
            int bestI, bestJ;
            int bestDelta = 0;

            // Iterate through all pairs of indices and find the best 2-swap
            for (int i = 0; i < size; ++i) {
                for (int j = i + 1; j < size; ++j) {
                    // Calculate the change in distance
                    int delta = calculateSwapDelta(solution, i, j);

                    // If the current 2-swap is better, update the best indices and delta
                    if (delta < bestDelta) {
                        bestDelta = delta;
                        bestI = i;
                        bestJ = j;
                    }
                }
            }
            std::swap(solution[bestI], solution[bestJ]);
            break;
        }
        default:
            throw std::invalid_argument("Error regarding neighbourhood exploration method");
    }
}

// Apply reversal to the solution
void SimulatedAnnealing::applyReversal(std::vector<int>& solution) {
    // Perform a reversal operation on the solution
    switch(explorationMethod) {
        case RANDOM: {
            int size = solution.size();
            int start = rand() % size;
            int end = rand() % size;
            if (start > end) {
                std::swap(start, end);
            }
            std::reverse(solution.begin() + start, solution.begin() + end);
            break;
        }
        case GREEDY: {
            // Perform a reversal operation on the solution greedily
            int size = solution.size();
            int bestStart, bestEnd;
            int bestDelta = 0;
            // Iterate through all pairs of start and end indices and find the best reversal
            for (int start = 0; start < size; ++start) {
                for (int end = start + 1; end < size; ++end) {
                    // Calculate the change in distance
                    int delta = calculateReversalDelta(solution, start, end);

                    // If the current reversal is better, update the best indices and delta
                    if (delta < bestDelta) {
                        bestDelta = delta;
                        bestStart = start;
                        bestEnd = end;
                    }
                }
            }

            // Apply the best reversal
            std::reverse(solution.begin() + bestStart, solution.begin() + bestEnd + 1);
            break;
        }
        default:
            throw std::invalid_argument("Error regarding neighbourhood exploration method");
    }
}

// Helper method to calculate the change in distance for a 2-swap
int SimulatedAnnealing::calculateSwapDelta(const std::vector<int>& solution, int i, int j) {
    // Calculate the change in distance by considering the nodes at indices i and j
    // Return the difference in distance (new distance - current distance)
    int size = solution.size();
    int prevI = (i == 0) ? size - 1 : i - 1;
    int nextI = (i == size - 1) ? 0 : i + 1;
    int prevJ = (j == 0) ? size - 1 : j - 1;
    int nextJ = (j == size - 1) ? 0 : j + 1;

    // Placeholder calculation
    int currentDistance = graph->getWeight(solution[prevI], solution[i]) +
                          graph->getWeight(solution[i], solution[nextI]) +
                          graph->getWeight(solution[prevJ], solution[j]) +
                          graph->getWeight(solution[j], solution[nextJ]);

    int newDistance = graph->getWeight(solution[prevI], solution[j]) +
                      graph->getWeight(solution[j], solution[nextI]) +
                      graph->getWeight(solution[prevJ], solution[i]) +
                      graph->getWeight(solution[i], solution[nextJ]);

    return newDistance - currentDistance;
}

// Helper method to calculate the change in distance for a reversal
int SimulatedAnnealing::calculateReversalDelta(const std::vector<int>& solution, int start, int end) {
    // Calculate the change in distance by considering the nodes in the range [start, end]
    // Return the difference in distance (new distance - current distance)
    int size = solution.size();
    int prevStart = (start == 0) ? size - 1 : start - 1;
    int nextEnd = (end == size - 1) ? 0 : end + 1;

    // Placeholder calculation
    int currentDistance = graph->getWeight(solution[prevStart], solution[start]) +
                          graph->getWeight(solution[end], solution[nextEnd]);

    int newDistance = graph->getWeight(solution[prevStart], solution[end]) +
                      graph->getWeight(solution[start], solution[nextEnd]);

    return newDistance - currentDistance;
}

void SimulatedAnnealing::PrintResults() {
    // Time
    int timeToDo;
    timeToDo = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    time = timeToDo;
    distancePublic = distance;
    hamiltonianCyclePublic = hamiltonianCycle;
    // Print the results
    std::cout << "Best Distance: " << distance << std::endl;
    std::cout << "Best Cycle: ";
    for (int node : hamiltonianCycle) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
    std::cout << "Time: " << timeToDo << " milliseconds" << std::endl;
}

// Both functions measure time which is later calculated
void SimulatedAnnealing::beginCounting() {
    startTime = std::chrono::high_resolution_clock::now();
}

void SimulatedAnnealing::finishCounting() {
    endTime = std::chrono::high_resolution_clock::now();
}