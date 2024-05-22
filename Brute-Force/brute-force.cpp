//
// Created by Ponanoix on 18.10.2023.
//

#include "brute-force.h"
#include <iostream>
#include <vector>

// Constructor - Initialises the algorithm with a graph representation and a starting node
BruteForce::BruteForce(GraphRepresentation* graph, int startVertex) {
    this -> graph = graph;
    this -> startNode = startVertex;
    this -> permutationSize = graph -> getNodeSize() - 1;
    permutation = new int[permutationSize];
}
// Core of the algorithm. Starts by initialising future path and permutation
void BruteForce::Start() {
    beginCounting();
    int minPath = INT_MAX;
    int* minPermutation = new int[permutationSize];

    InitializePermutation();

    do {
        int currentPathLen = CalculatePathLength();


        if (currentPathLen < minPath) {
            minPath = currentPathLen;
            CopyPermutation(minPermutation);
        }
    } while (GetNextPermutation());

    finishCounting();
    PrintResults(minPath, minPermutation);
    delete[] minPermutation;
}
// Initialises permutation of nodes to be visited by the algorithm
void BruteForce::InitializePermutation() {
    int currentIndex = 0;
    for (int i = 0; i < graph -> getNodeSize(); i++) {
        if (i != startNode) {
            permutation[currentIndex++] = i;
        }
    }
}
// Computes the length of a path based on the current permutation
int BruteForce::CalculatePathLength() {
    int currentPathLen = 0;
    int prev = startNode;
    for (int i = 0; i < permutationSize; i++) {
        int t = permutation[i];
        currentPathLen += graph -> getWeight(prev, t);
        prev = t;

    }

    if (prev != startNode) currentPathLen += graph -> getWeight(prev, startNode);

    return currentPathLen;
}
// Copies the current permutation to the provided array
void BruteForce::CopyPermutation(int* destination) {
    for (int i = 0; i < graph -> getNodeSize() - 1; i++) {
        destination[i] = permutation[i];
    }
}
// Prints final results
void BruteForce::PrintResults(int minPath, int* minPermutation) {
    int timeToDo;

    if(graph -> getNodeSize() <= 9){
        timeToDo = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    } else if(graph -> getNodeSize() <= 12){
        timeToDo = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    } else{
        timeToDo = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    }
    time = timeToDo;
    hamiltonCycle.push_back(startNode);
    distance = minPath;
    std::cout << "Found min path. Path: " << startNode << " ";
    for (int i = 0; i < graph -> getNodeSize() - 1; i++) {
        hamiltonCycle.push_back(minPermutation[i]);
        std::cout << minPermutation[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Path length: " << minPath << "." << std::endl;
    if(graph -> getNodeSize() <= 9) std::cout << "Time: " << timeToDo << "ns." << std::endl;
    else if(graph -> getNodeSize() <= 12 && graph -> getNodeSize() > 9) std::cout << "Time: " << timeToDo << "ms." << std::endl;
    else if(graph -> getNodeSize() > 12) std::cout << "Time: " << timeToDo << "s." << std::endl;
}
// Generates the next permutation in lexicographical order
bool BruteForce::GetNextPermutation() {
    if (permutation == nullptr || permutationSize <= 1) return false;

    int lastIncreasing = permutationSize - 2;

    while (lastIncreasing >= 0) {
        if (permutation[lastIncreasing] < permutation[lastIncreasing + 1]) break;
        lastIncreasing--;
    }
    if (lastIncreasing < 0) return false;

    int successor = permutationSize - 1;

    for (int i = permutationSize - 1; i > lastIncreasing; i--) {
        if (permutation[i] <= permutation[lastIncreasing]) continue;
        successor = i;
        break;
    }

    int temp = permutation[successor];
    permutation[successor] = permutation[lastIncreasing];
    permutation[lastIncreasing] = temp;

    int l = 1;
    int numSwaps = (permutationSize - 1 - lastIncreasing) / 2 + lastIncreasing;
    for (int i = graph -> getNodeSize() - 2; i > numSwaps; i--) {
        int temp2 = permutation[i];
        permutation[i] = permutation[lastIncreasing + l];
        permutation[lastIncreasing + l] = temp2;
        l++;
    }

    return true;
}
// Both functions measure and record execution time
void BruteForce::beginCounting() {
    startTime = std::chrono::high_resolution_clock::now();
}

void BruteForce::finishCounting() {
    endTime = std::chrono::high_resolution_clock::now();
}
