//
// Created by Ponanoix on 20.01.2024.
//

#include "graph-representation.h"
#include<iostream>

GraphRepresentation::GraphRepresentation(int nodeSize) : nodeSize(nodeSize) {

    adjacency_matrix = new int *[nodeSize];

    for(int i = 0; i < nodeSize; i++){
        adjacency_matrix[i] = new int[nodeSize];

        for(int j = 0; j < nodeSize; j++){
            adjacency_matrix[i][j] = 0;
        }
    }
}

void GraphRepresentation::addConnection(int start, int end, int weight) {

    if(start < 0 || start >= nodeSize || end < 0 || end >= nodeSize ) throw std::invalid_argument("Invalid nodes were passed (either smaller than 0 or greater than the number of them)");

    adjacency_matrix[start][end] = weight;
}

void GraphRepresentation::print() {
    std::cout<<'\n';
    std::cout<<'\n';

    for (int i = 0; i < nodeSize; i++) {
        for (int j = 0; j < nodeSize; j++) {
            std::cout << adjacency_matrix[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << ">------------------------------------------------------------------------------|" << '\n';
}

void GraphRepresentation::printTriangle(){
    std::cout<<'\n';
    std::cout<<'\n';

    for (int i = 0; i < nodeSize; i++) {
        for (int j = 0; j < i + 1; j++) {
            std::cout << adjacency_matrix[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << ">------------------------------------------------------------------------------|" << '\n';
}


int GraphRepresentation::getNodeSize() const {
    return nodeSize;
}

int GraphRepresentation::getWeight(int start, int end) {
    return adjacency_matrix[start][end];
}

void GraphRepresentation::setNodeSize(int n) {

    for(int i = 0; i < nodeSize; i++){
        delete[] this -> adjacency_matrix[i];
    }

    delete[] this -> adjacency_matrix;

    this -> nodeSize = n;

    adjacency_matrix = new int *[nodeSize];

    for(int i = 0; i < nodeSize; i++){
        adjacency_matrix[i] = new int[nodeSize];

        for(int j = 0; j < nodeSize; j++){
            adjacency_matrix[i][j] = 0;
        }
    }
}
