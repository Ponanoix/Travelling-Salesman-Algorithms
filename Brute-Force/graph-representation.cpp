//
// Created by Ponanoix on 17.10.2023.
//
#include<iostream>
#include"graph-representation.h"

GraphRepresentation::GraphRepresentation(int nodeSize, int startingNode) : nodeSize(nodeSize), startingNode(startingNode) {
    adjacencyMatrix = new int *[nodeSize];
    for(int i = 0; i < nodeSize; i++){
        adjacencyMatrix[i] = new int[nodeSize];
        for(int j = 0; j < nodeSize; j++){
            adjacencyMatrix[i][j] = 0;
        }
    }
}

void GraphRepresentation::addConnection(int begin, int end, int weight) {
    if(begin < 0 || begin > nodeSize || end < 0 || end > nodeSize) throw std::invalid_argument("Invalid nodes were passed.");
    if(adjacencyMatrix[begin][end] == 0 && weight != 0) currentEdgeSize++;
    if(adjacencyMatrix[begin][end] != 0 && weight == 0) currentEdgeSize--;
    adjacencyMatrix[begin][end] = weight;
}

void GraphRepresentation::setNodeSize(int n) {
    for(int i = 0; i < nodeSize; i++){
        delete[] this -> adjacencyMatrix[i];
    }
    delete[] this -> adjacencyMatrix;
    this -> nodeSize = n;
    adjacencyMatrix = new int *[nodeSize];
    for(int i = 0; i < nodeSize; i++){
        adjacencyMatrix[i] = new int[nodeSize];
        for(int j = 0; j < nodeSize; j++){
            adjacencyMatrix[i][j] = 0;
        }
    }
}

void GraphRepresentation::setEdgeSize(int n) {
    this -> currentEdgeSize = 0;
    this -> totalEdgeSize = n;
}

int GraphRepresentation::getNodeSize() const {
    return nodeSize;
}

int GraphRepresentation::getWeight(int i, int j) {
    return adjacencyMatrix[i][j];
}

void GraphRepresentation::print() {
    std::cout<<std::endl;
    std::cout<<std::endl;
    for(int i = 0; i < nodeSize; i++){
        for(int j = 0; j < nodeSize; j++){
            std::cout<<adjacencyMatrix[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<">------------------------------------------------------------------------------|"<<std::endl;
}
