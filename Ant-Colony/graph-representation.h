//
// Created by Ponanoix on 20.01.2024.
//

#ifndef PEA_4_GRAPH_REPRESENTATION_H
#define PEA_4_GRAPH_REPRESENTATION_H

class GraphRepresentation{
protected:
    // Matrix to store the distances between nodes
    int **adjacency_matrix;

    // Number of nodes in the graph
    int nodeSize;

    // Starting node in an iteration
    int startingNode{};
public:
    // Constructor
    explicit GraphRepresentation(int nodeSize);

    // Adds connection between two nodes
    virtual void addConnection(int start, int end, int weight);

    // Prints the adjacency matrix
    void print();

    // Prints the triangular matrix (for triangle files)
    void printTriangle();

    // Returns the number of nodes
    [[nodiscard]] int getNodeSize() const;

    // Returns the weight between two nodes
    int getWeight(int start, int end);

    // Sets the number of nodes
    void setNodeSize(int n);
};

#endif //PEA_4_GRAPH_REPRESENTATION_H
