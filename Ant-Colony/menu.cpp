//
// Created by Ponanoix on 20.01.2024.
//

#include "menu.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include "ant-colony-optimization.h"

Menu::Menu() {
    printMenu();
}

void Menu::printMenu() {
    while(true){
        std::cout << "Your choice: " << '\n';
        std::cout << "\t1 - Load a graph from a file" << '\n';
        std::cout << "\t2 - Print the loaded graph" << '\n';
        std::cout << "\t3 - Execute a single instance of the algorithm" << '\n';
        std::cout << "\t4 - Begin a .ini file benchmark" << '\n';
        std::cout << "\t0 - Shutdown the program" << '\n';
        std::cout << '\n';

        int input = getIntegerInput("Your choice: ");
        std::cout << '\n';
        std::cout << ">------------------------------------------------------------------------------|" << '\n';
        switch(input){
            case 1: {
                loadAGraphFromAFile();
                break;
            }
            case 2: {
                printAGraph();
                break;
            }
            case 3: {
                antColonyOptimization();
                break;
            }
            case 4: {
                benchmark();
                break;
            }
            case 0: {
                std::cout << "Shutting down..." << '\n';
                exit(0);
            }
            default: {
                std::cout << "Unknown input! Choose between 0 and 4!" << '\n';
            }
        }
    }
}

int Menu::getIntegerInput(const std::string &message) {
    bool isNum = false;
    int value;

    while(!isNum){
        std::cout << message;
        std::string input;
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);

        try {
            size_t pos;
            value = std::stoi(input, &pos);


            if (pos == input.length()) {
                isNum = true;


                if (value >= 0) {
                } else {
                    std::cout << "Please enter a positive integer!" << std::endl;
                }
            } else {
                std::cout << "Invalid input! Not an integer!" << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input! Not a number!" << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Invalid input! Out of range!" << std::endl;
        }
    }
    return value;
}

void Menu::printException(std::exception &e) {
    std::cout << "X-----------------------------X\n";
    std::cout << "WARNING: An error has occurred:\n";
    std::cerr << e.what() << "\n";
    std::cout << "X-----------------------------X\n";
}

void Menu::loadAGraphFromAFile() {
    std::cout << "Please enter the file's name: ";
    std::cin >> loadedFileName;
    std::cout << std::endl;
    std::cout << "Loading data from the file..." << std::endl;
    try {
        FileReader fileReader(loadedFileName);
        graphRepresentation = new GraphRepresentation(0);
        fileReader.createAnAdjacencyMatrix(graphRepresentation);
    } catch (std::runtime_error &e) {
        printException(e);
        Sleep(200);
        return;
    }
    std::cout << "Data loaded successfully!" << std::endl << std::endl;
    std::cout << ">------------------------------------------------------------------------------|" << std::endl;
}

void Menu::printAGraph() {
    try {
        if (graphRepresentation == nullptr) throw std::invalid_argument("There is nothing to read from!");
        FileReader fileReader(loadedFileName);
        if(fileReader.getTheFileType() == "MATRIX" || fileReader.getTheFileType() == "COORDS" || fileReader.getTheFileType() == "REAL_COORDS") graphRepresentation -> print();
        else if(fileReader.getTheFileType() == "TRIANGLE") graphRepresentation -> printTriangle();
    } catch (std::invalid_argument &e) {
        printException(e);
        Sleep(200);
        return;
    }
}

void Menu::antColonyOptimization() {
    PheromoneSchematic pS;
    int alphaInput;
    int betaInput;
    float rhoInput;
    Heuristics hs;
    std::cout << "Please enter the alpha, beta and rho parameters (preferably 1, 3 and 0.5):" << '\n';
    std::cout << "Alpha: ";
    std::cin >> alphaInput;
    std::cout << '\n';
    std::cout << "Beta: ";
    std::cin >> betaInput;
    std::cout << '\n';
    std::cout << "Rho: ";
    std::cin >> rhoInput;
    std::cout << '\n';
    std::cout << "Choose evaporation schematic: " << '\n';
    std::cout << "0 - Density Ant System (DAS)" << '\n';
    std::cout << "1 - Density Ant System (QAS)" << '\n';
    std::cout << "2 - Density Ant System (CAS)" << '\n';
    int input1 = getIntegerInput("Your choice: ");
    switch(input1){
        case 0: {
            pS = DAS;
            break;
        }
        case 1: {
            pS = QAS;
            break;
        }
        case 2: {
            pS = CAS;
            break;
        }
        default: {
            std::cout << "Unknown input! Choose between 0 and 2!" << '\n';
            break;
        }
    }
    std::cout << '\n';
    std::cout << "Choose next node choice heuristics: " << '\n';
    std::cout << "0 - VISIBILITY  ( 1 / distance)" << '\n';
    std::cout << "1 - LOGARITHMIC [ ln(distance)]" << '\n';
    int input2 = getIntegerInput("Your choice: ");
    switch(input2){
        case 0: {
            hs = VISIBILITY;
            break;
        }
        case 1: {
            hs = LOGARITHMIC;
            break;
        }
        default: {
            std::cout << "Unknown input! Choose between 0 and 1!" << '\n';
        }
    }
    AntColonyOptimization antColonyOptimization(graphRepresentation, false, pS, alphaInput, betaInput, rhoInput, hs);
    antColonyOptimization.startTheAlgorithm();
}

void Menu::benchmark() {
    try {
        std::string iniFile;
        std::cout << "Please enter the name of the .ini file: " << std::endl;
        std::cin >> iniFile;
        readAnIniFile(iniFile);
    } catch (std::invalid_argument &e) {
        printException(e);
        Sleep(200);
        return;
    }
}

void Menu::readAnIniFile(std::string &fileName) {
    std::cout << fileName << std::endl;
    std::vector<int> numbersOfCalls;
    std::vector<float> costs;
    std::vector<std::string> graphFiles;
    std::vector<std::vector<int>> correctCycles;
    std::string csvFile;

    std::ifstream inputFile(fileName, std::ios::in);

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
            int numberOfCalls;
            float cost;
            std::istringstream iniStream(line);
            std::string graphFile;
            std::vector<int> correctCycle;
            if (iniStream >> graphFile >> numberOfCalls >> cost) {
                graphFiles.push_back(graphFile);
                numbersOfCalls.push_back(numberOfCalls);
                costs.push_back(cost);

                int number;
                while (iniStream >> number) {
                    correctCycle.push_back(number);
                }
                correctCycles.push_back(correctCycle);
            }
        }
        std::istringstream csvStream(line);
        csvStream >> csvFile;
        inputFile.close();
    } else {
        std::cerr << "Could not read the input file" << std::endl;
    }
    std::ofstream outputFile(csvFile);
    if (!outputFile.is_open()) {
        std::cerr << "Could not open the output file" << std::endl;
    }
    PheromoneSchematic pS;
    int alphaInput;
    int betaInput;
    float rhoInput;
    Heuristics hs;
    std::cout << "Please enter the alpha, beta and rho parameters (preferably 1, 3 and 0.5):" << '\n';
    std::cout << "Alpha: ";
    std::cin >> alphaInput;
    std::cout << '\n';
    std::cout << "Beta: ";
    std::cin >> betaInput;
    std::cout << '\n';
    std::cout << "Rho: ";
    std::cin >> rhoInput;
    std::cout << '\n';
    std::cout << "Choose evaporation schematic: " << '\n';
    std::cout << "0 - Density Ant System (DAS)" << '\n';
    std::cout << "1 - Density Ant System (QAS)" << '\n';
    std::cout << "2 - Density Ant System (CAS)" << '\n';
    int input1 = getIntegerInput("Your choice: ");
    switch(input1){
        case 0: {
            pS = DAS;
            break;
        }
        case 1: {
            pS = QAS;
            break;
        }
        case 2: {
            pS = CAS;
            break;
        }
        default: {
            std::cout << "Unknown input! Choose between 0 and 2!" << '\n';
        }
    }
    std::cout << '\n';
    std::cout << "Choose next node choice heuristics: " << '\n';
    std::cout << "0 - VISIBILITY ( 1 / distance)" << '\n';
    std::cout << "1 - LOGARITHMIC ( ln(distance) )" << '\n';
    int input2 = getIntegerInput("Your choice: ");
    switch(input2){
        case 0: {
            hs = VISIBILITY;
            break;
        }
        case 1: {
            hs = LOGARITHMIC;
            break;
        }
        default: {
            std::cout << "Unknown input! Choose between 0 and 1!" << '\n';
        }
    }
    for (int i = 0; i < graphFiles.size(); i++) {
        FileReader reader(graphFiles[i]);
        auto* graph = new GraphRepresentation(0);
        reader.createAnAdjacencyMatrix(graph);

        outputFile << graphFiles[i];

        for (int j = 0; j < numbersOfCalls[i]; j++) {
            std::cout << std::endl;
            std::cout << "Measure nr " << j + 1 << std::endl;
            auto *aco = new AntColonyOptimization(graph, false, pS, alphaInput, betaInput, rhoInput, hs);

            aco -> startTheAlgorithm();
            outputFile << ";" << aco -> time;

            std::vector<int> temporaryCycle = aco -> hamiltonianCycle;
            float calculation;
            calculation = (abs(costs[i] - (aco -> currentBestDistance)) / costs[i]) * 100;
            std::cout << "Calculation complete. Relative error: " << calculation << "%" << std::endl;
            outputFile << ";" << calculation;
        }
        outputFile << std::endl;
        delete graph;
    }
    outputFile.close();
}
