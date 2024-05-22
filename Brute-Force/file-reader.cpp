//
// Created by Ponanoix on 17.10.2023.
//

#include"file-reader.h"

int FileReader::readNextVal() {
    int nextVal;
    if(input.is_open()){
        input >> nextVal;
        if(input.fail()){
            throw std::runtime_error("File error - stopping the program");
        }
        if(input.eof()){
            input.close();
        }
        return nextVal;
    }
    throw std::runtime_error("File not opened - perhaps it was already opened?");
}

FileReader::FileReader(const std::string &fileName) : fileName(fileName), input(fileName){
    input >> nodeSize;
    if(!input.is_open()){
        throw std::runtime_error("Could not read the file");
    }
}

void FileReader::readToAdjMatrix(GraphRepresentation *graph) {
    graph -> setNodeSize(nodeSize);
    graph -> setEdgeSize(edgeSize);
    int from, to, distance;
    for(int i = 0; i < nodeSize; i++){
        from = i;
        for(int j = 0; j < nodeSize; j++){
            to = j;
            distance = readNextVal();
            graph -> addConnection(from, to, distance);
        }
    }
}
