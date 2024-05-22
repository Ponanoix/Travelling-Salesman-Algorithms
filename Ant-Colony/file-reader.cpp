//
// Created by Ponanoix on 20.01.2024.
//

#include"file-reader.h"
#include<cmath>

FileReader::FileReader(const std::string& fileName) : fileName(fileName), inputStream(fileName) {
    inputStream >> fileType;
    inputStream >> nodeSize;
    positionZero = inputStream.tellg();

    if(!inputStream.is_open()){
        throw std::runtime_error("Could not read the file (make sure it is located in the 'cmake-build-*' folder)!");
    }
}

float FileReader::returnNextValue() {
    float nextValue;

    if(inputStream.is_open()){
        inputStream >> nextValue;

        if(inputStream.fail()){
            throw std::runtime_error("A file error has occurred. Check the contents of it!");
        }

        if(inputStream.eof()){
            inputStream.close();
        }

        return nextValue;
    }

    throw std::runtime_error("Could not open the file. Make sure it is accessible or hasn't been opened already!");
}

void FileReader::createAnAdjacencyMatrix(GraphRepresentation *graphRepresentation) {
    graphRepresentation -> setNodeSize(nodeSize);
    int start, end, weight;

    if(fileType == "MATRIX"){
        for(int i = 0; i < nodeSize; i++){
            start = i;
            for(int j = 0; j < nodeSize; j++){
                end = j;
                weight = static_cast<int>(returnNextValue());
                graphRepresentation -> addConnection(start, end, weight);
            }
        }
    }
    else if(fileType == "TRIANGLE"){
        for(int i = 0; i < nodeSize; i++){
            start = i;
            for(int j = 0; j < j + 1; j++){
                end = j;
                weight = static_cast<int>(returnNextValue());
                graphRepresentation -> addConnection(start, end, weight);
            }
        }
    }
    else if(fileType == "REAL_COORDS"){
        float latitude, longitude, latitude2, longitude2;
        for(int i = 0; i < nodeSize; i++){

            if(i != 0) inputStream.seekg(currentPosition);
            start = i;
            returnNextValue();
            latitude = returnNextValue();
            longitude = returnNextValue();
            currentPosition = inputStream.tellg();

            for(int j = 0; j < nodeSize; j++){
                if(j == 0) inputStream.seekg(positionZero);

                end = j;
                returnNextValue();
                latitude2 = returnNextValue();
                longitude2 = returnNextValue();

                weight = 111 * static_cast<int>(sqrt(pow(longitude2 - longitude, 2) + pow(latitude2 - latitude, 2)));
                if(weight == 0 && i != j){
                    weight = 75;
                }
                graphRepresentation -> addConnection(start, end, weight);
            }
        }
    }
    else if(fileType == "COORDS"){
        float latitude, longitude, latitude2, longitude2;
        for(int i = 0; i < nodeSize; i++){

            if(i != 0) inputStream.seekg(currentPosition);
            start = i;
            returnNextValue();
            latitude = returnNextValue();
            longitude = returnNextValue();
            currentPosition = inputStream.tellg();

            for(int j = 0; j < nodeSize; j++){
                if(j == 0) inputStream.seekg(positionZero);

                end = j;
                returnNextValue();
                latitude2 = returnNextValue();
                longitude2 = returnNextValue();

                weight = static_cast<int>(sqrt(pow(longitude2 - longitude, 2) + pow(latitude2 - latitude, 2)));

                graphRepresentation -> addConnection(start, end, weight);
            }
        }
    }
}

std::string FileReader::getTheFileType() {
    return fileType;
}
