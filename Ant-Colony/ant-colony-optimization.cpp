//
// Created by Ponanoix on 21.01.2024.
//

#include "ant-colony-optimization.h"
#include <iostream>

AntColonyOptimization::AntColonyOptimization(GraphRepresentation *graphRepresentation, bool userInput, PheromoneSchematic pS, int alpha, int beta, float rho, Heuristics hs) {
    this -> graphRepresentation = graphRepresentation;

    if(userInput){
        initialiseParameters();
    }
    else {
        alphaParameter = alpha;
        betaParameter = beta;
        rhoParameter = rho;
        numberOfAnts = static_cast<float>(graphRepresentation -> getNodeSize());
        tauCoefficient.resize(graphRepresentation->getNodeSize(), std::vector<float>(graphRepresentation -> getNodeSize(), numberOfAnts / calculateEstimatedDistance()));
        numberOfIterations = 10;
        amountOfPheromone = 100;
    }

    pheromoneSchematic = pS;

    heuristics = hs;
}

std::vector<double> probabilities;
std::vector<std::vector<float>> visitedEdges;
std::vector<std::vector<float>> casEdges;
std::vector<int> currentBestCycle;

void AntColonyOptimization::startTheAlgorithm() {

    beginCounting();
    auto timeLimit = std::chrono::system_clock::now();
    timeLimit += std::chrono::seconds(600);

    currentBestDistance = INT_MAX;
    std::vector<int> iterations;
    int temp;
    for(int i = 0; i < numberOfIterations; i++){
        int casDistance = 0;
        for(int j = 0; j < numberOfAnts; j++){

            startingNode = randomiseStartingNode();
            int arrayOfNodes[graphRepresentation -> getNodeSize()];

            for(int k = 0; k < graphRepresentation -> getNodeSize(); k++){
                arrayOfNodes[k] = INT_MAX;
            }

            arrayOfNodes[startingNode] = startingNode;
            int numberOfElements = 0;
            bool exists = false;

            int l = startingNode;
            int currentNode = INT_MAX;

            distancePublic = 0;

            probabilities.resize(graphRepresentation -> getNodeSize(), 0);

            visitedEdges.resize(graphRepresentation->getNodeSize(), std::vector<float>(graphRepresentation->getNodeSize(), 0));

            casEdges.resize(graphRepresentation->getNodeSize(), std::vector<float>(graphRepresentation->getNodeSize(), 0));

            hamiltonianCycle.push_back(startingNode);
            while(numberOfElements + 1 != sizeof(arrayOfNodes) / sizeof(arrayOfNodes[0])) {
                float denominator = 0;
                for(int m = 0; m < graphRepresentation -> getNodeSize(); m++) {
                    for(int n = 0; n < graphRepresentation -> getNodeSize(); n++) {
                        if (arrayOfNodes[n] == m) {
                            exists = true;
                            break;
                        } else if(exists && n == graphRepresentation -> getNodeSize() - 1){
                            exists = false;
                        }
                    }
                    if(!exists) {
                        if(heuristics == VISIBILITY) {
                            denominator += static_cast<float>(pow(tauCoefficient[l][m], alphaParameter) *
                                                              pow(1.0 / graphRepresentation->getWeight(l, m),
                                                                  betaParameter));
                        } else if (heuristics == LOGARITHMIC) {
                            denominator += static_cast<float>(pow(tauCoefficient[l][m], alphaParameter) *
                                                              pow(log(graphRepresentation->getWeight(l, m)),
                                                                  betaParameter));
                        }
                    }
                }
                int o;
                for(o = 0; o < graphRepresentation -> getNodeSize(); o++){
                    probabilities[o] = INT_MAX;
                }
                for(int m = 0; m < graphRepresentation -> getNodeSize(); m++) {
                    for(int n = 0; n < graphRepresentation -> getNodeSize(); n++) {
                        if (arrayOfNodes[n] == m) {
                            exists = true;
                            break;
                        } else if(exists && n == graphRepresentation -> getNodeSize() - 1){
                            exists = false;
                        }
                    }
                    if(!exists) {
                        if(heuristics == VISIBILITY) {
                            probabilityOfChoice = static_cast<float>((pow(tauCoefficient[l][m], alphaParameter) *
                                                                      pow(1.0 / graphRepresentation->getWeight(l, m),
                                                                          betaParameter)) / denominator);
                        }
                        else if (heuristics == LOGARITHMIC){
                            probabilityOfChoice = static_cast<float>((pow(tauCoefficient[l][m], alphaParameter) *
                                                                      pow(log(graphRepresentation->getWeight(l, m)),
                                                                          betaParameter)) / denominator);
                        }
                        probabilities[m] = probabilityOfChoice;
                        o = m;
                        probabilities[o] = probabilityOfChoice;
                    }
                }

                float comparison = 0;
                float here;
                here = randomiseNextChoice();
                for(o = 0; o < graphRepresentation -> getNodeSize(); o++){
                    if(probabilities[o] != INT_MAX) {
                        comparison += static_cast<float>(probabilities[o]);
                        if (comparison > here) {
                            here = o;
                            break;
                        }
                    }
                }
                currentNode = static_cast<int>(here);
                switch(pheromoneSchematic) {
                    case QAS: {
                        visitedEdges[l][currentNode] = static_cast<float>(100) / static_cast<float>(graphRepresentation->getWeight(l,currentNode));
                    }
                    case DAS: {
                        visitedEdges[l][currentNode] = 100;
                    }
                    case CAS: {
                        visitedEdges[l][currentNode] += -1;
                    }
                }
                numberOfElements++;
                arrayOfNodes[currentNode] = currentNode;

                distancePublic += graphRepresentation -> getWeight(l, currentNode);
                hamiltonianCycle.push_back(currentNode);
                casDistance += distancePublic;


                l = currentNode;
                currentNode = INT_MAX;
            }
            if(distancePublic < currentBestDistance){
                temp = currentBestDistance;
                iterations.push_back(i);
                currentBestDistance = distancePublic;
                std::cout << "New best distance found! The distance: " << currentBestDistance << '\n';
                std::cout << "Iteration number: " << i << ", ant number: " << j <<'\n';
                std::cout << "Hamiltonian cycle: ";
                for(int q = 0; q < graphRepresentation -> getNodeSize(); q++){
                    std::cout << hamiltonianCycle[q] << " ";
                }
                std::cout << '\n' << '\n';
                currentBestCycle = hamiltonianCycle;
            }
            hamiltonianCycle.clear();
        }
        if(pheromoneSchematic == CAS){
            for(int j = 0; j < graphRepresentation -> getNodeSize(); j++){
                for(int k = 0; k < graphRepresentation -> getNodeSize(); k++){
                    if(visitedEdges[j][k] < 0) {
                        visitedEdges[j][k] = static_cast<float>(100)/static_cast<float>(casDistance);
                    }
                }
            }
        }
        if(iterations.size() == 2){
            if(iterations[1] - iterations[0] > temp - currentBestDistance){
                break;
            }
        }
        if(std::chrono::system_clock::now() > timeLimit){
            break;
        }
        calculateTauCoefficient();
    }

    finishCounting();

    printResults();
}

void AntColonyOptimization::initialiseParameters() {
    std::cout << "Please enter the values for the following variables: " << '\n';

    std::cout << "Alpha parameter: ";
    std::cin >> alphaParameter;
    std::cout << '\n';

    std::cout << "Beta parameter: ";
    std::cin >> betaParameter;
    std::cout << '\n';

    std::cout << "Rho parameter: ";
    std::cin >> rhoParameter;
    std::cout << '\n';

    std::cout << "Number of ants per iteration: ";
    std::cin >> numberOfAnts;
    std::cout << '\n';

    std::cout << "Tau coefficient: ";
    std::cin >> tauCoefficientValue;
    std::cout << '\n';

    for(int i = 0; i < graphRepresentation -> getNodeSize(); i++){
        for(int j = 0; j < graphRepresentation -> getNodeSize(); j++){
            tauCoefficient[i][j] = tauCoefficientValue;
        }
    }

    std::cout << "Eta coefficient: ";
    std::cin >> etaCoefficient;
    std::cout << '\n';

    std::cout << "Number of iterations: ";
    std::cin >> numberOfIterations;
    std::cout << '\n';

    std::cout << "Raw amount of pheromone each ant leaves behind: ";
    std::cin >> amountOfPheromone;
    std::cout << '\n';
}

float AntColonyOptimization::calculateEstimatedDistance() {
    float estimatedDistance = 0;

    startingNode = 0;
    int arrayOfNodes[graphRepresentation -> getNodeSize()];
    for(int i = 0; i < graphRepresentation -> getNodeSize(); i++){
        arrayOfNodes[i] = INT_MAX;
    }
    arrayOfNodes[0] = startingNode;
    int numberOfElements = 0;
    int currentBest = INT_MAX;
    int i = 0;
    int j;
    bool exists = false;

    while(numberOfElements + 1 != sizeof(arrayOfNodes) / sizeof(arrayOfNodes[0])) {
        for(j = 0; j < graphRepresentation -> getNodeSize(); j++) {
            for(int k = 0; k < graphRepresentation -> getNodeSize(); k++) {
                if (arrayOfNodes[k] == j) {
                    exists = true;
                    break;
                } else if(exists && k == graphRepresentation -> getNodeSize() - 1){
                    exists = false;
                }
            }
            if(!exists) {
                if (graphRepresentation->getWeight(i, j) != 0 && graphRepresentation->getWeight(i, j) < currentBest) {
                    currentBest = j;
                }
            }
        }
        numberOfElements++;
        arrayOfNodes[currentBest] = currentBest;
        estimatedDistance += static_cast<float>(graphRepresentation->getWeight(i, currentBest));
        i = currentBest;
        currentBest = INT_MAX;
    }
    return estimatedDistance;
}

int AntColonyOptimization::randomiseStartingNode() {
    std::random_device rd;

    std::mt19937 startingNodeGenerator(rd());

    std::uniform_int_distribution<> dis(0, graphRepresentation -> getNodeSize() - 1);

    startingNode = dis(startingNodeGenerator);

    return startingNode;
}

float AntColonyOptimization::randomiseNextChoice() {
    float choice;

    std::random_device rd;

    std::mt19937 nextNodeGenerator(rd());

    std::uniform_real_distribution<> dis(0, RAND_MAX);

    choice = static_cast<float>(dis(nextNodeGenerator) / RAND_MAX);

    return choice;
}

void AntColonyOptimization::printResults() {
    int timeToDo;

    timeToDo = std::chrono::duration_cast<std::chrono::milliseconds>(endingTime - startingTime).count();

    time = timeToDo;

    std::cout << "Best distance: " << currentBestDistance << '\n';
    std::cout << "Hamiltonian cycle: ";
    for(int i = 0; i < graphRepresentation -> getNodeSize(); i++){
        std::cout << currentBestCycle[i] << " ";
    }
    std::cout << '\n';
    std::cout << "Time: " << timeToDo << " milliseconds" << '\n';
}

void AntColonyOptimization::calculateTauCoefficient() {
    for(int i = 0; i < graphRepresentation -> getNodeSize(); i++){
        for(int j = 0; j < graphRepresentation -> getNodeSize(); j++){
            tauCoefficient[i][j] = rhoParameter * tauCoefficient[i][j] + visitedEdges[i][j];
        }
    }
}

void AntColonyOptimization::beginCounting() {
    startingTime = std::chrono::high_resolution_clock::now();
}

void AntColonyOptimization::finishCounting() {
    endingTime = std::chrono::high_resolution_clock::now();
}