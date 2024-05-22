//
// Created by Ponanoix on 20.01.2024.
//

#ifndef PEA_4_FILE_READER_H
#define PEA_4_FILE_READER_H

#include<fstream>
#include"graph-representation.h"

class FileReader{
private:
    // Name of the input file
    std::string fileName;

    // Type of the file (coordinates, triangle, matrix)
    std::string fileType;

    // File input stream
    std::ifstream inputStream;

    // File input stream (second one, for coord files)
    std::ifstream inputStreamCoords;

    // Main checkpoint for an input stream to go back to
    std::streampos positionZero;

    // Checkpoint for an input stream to go back to in a loop
    std::streampos currentPosition;

    // Number of nodes
    int nodeSize = 0;

    // Returns the next value in the file
    float returnNextValue();
public:
    // Constructor
    explicit FileReader(const std::string &fileName);

    // Checks the contents of the file and creates a matrix accordingly
    void createAnAdjacencyMatrix(GraphRepresentation *graphRepresentation);

    // Return the file type
    std::string getTheFileType();
};

#endif //PEA_4_FILE_READER_H
