//
// Created by Ponanoix on 17.10.2023.
//

#ifndef PEA_GRAPH_REPRESENTATION_H
#define PEA_GRAPH_REPRESENTATION_H

class GraphRepresentation{
protected:
    int **adjacencyMatrix;                                                          // Representation of the graph in files

    int nodeSize;                                                                   // Size of the graph

    int startingNode;                                                               // Node from which the algorithm begins

    int currentEdgeSize = 0;                                                        // Current number of edges in the graph

    int totalEdgeSize = (nodeSize * (nodeSize - 1)) / 2;                            // Total number of edges in a graph
public:
    GraphRepresentation(int nodeSize, int startingNode);                            // Constructor

    virtual void addConnection(int begin, int end, int weight);                     // Creates an edge between two nodes

    void print();                                                                   // Prints the matrix representation of the graph

    void setNodeSize(int n);                                                        // Sets the number of nodes in the graph

    void setEdgeSize(int n);                                                        // Sets the number of edges in the graph

    int getNodeSize() const;                                                        // Returns the number of nodes

    int getWeight(int i, int j);                                                    // Returns the weight of an edge
};

#endif //PEA_GRAPH_REPRESENTATION_H
