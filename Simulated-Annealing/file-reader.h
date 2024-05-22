//
// Created by Ponanoix on 18.12.2023.
//

#ifndef PEA_3_FILE_READER_H
#define PEA_3_FILE_READER_H

#include<fstream>
#include"graph-representation.h"

class FileReader{
private:
    std::string fileName;                               // Name of the input file

    std::ifstream input;                                // File input stream

    int nodeSize = 0;                                   // Number of nodes the graph has

    int edgeSize = (nodeSize * (nodeSize - 1)) / 2;     // Number of edges the graph has

    int readNextVal();                                  // Returns the next value from the file
public:
    explicit FileReader(const std::string &fileName);   // Creates a new instance of this class

    void readToAdjMatrix(GraphRepresentation *graph);   // Loads data and prints the matrix representation
};

#endif //PEA_3_FILE_READER_H
