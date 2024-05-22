//
// Created by Ponanoix on 02.11.2023.
//

#include <windows.h>
#include <iostream>
#include <sstream>
#include "menu.h"
#include <vector>
#include "held-karp.h"

Menu::Menu() {
    printMainMenu();
}

void Menu::printMainMenu() {
    while (true) {
        std::cout << "Choose: " << std::endl;
        std::cout << "\t1. Load graph from a file" << std::endl;
        std::cout << "\t2. Print the graph" << std::endl;
        std::cout << "\t3. Single instance" << std::endl;
        std::cout << "\t4. .ini file benchmark" << std::endl;
        std::cout << "\t0. Shutdown the program" << std::endl;
        std::cout << std::endl;
        int input = getIntegerInput("Your choice: ");
        std::cout << std::endl;
        std::cout << ">------------------------------------------------------------------------------|" << std::endl;
        switch (input) {
            case 1: {
                loadFromFile();
                break;
            }
            case 2: {
                printGraph();
                break;
            }
            case 3: {
                heldKarp();
                break;
            }
            case 4: {
                benchmark();
                break;
            }
            case 0: {
                std::cout << "Shutting down..." << std::endl;
                exit(0);
            }
            default: {
                std::cout << "Unknown input" << std::endl;
                break;
            }
        }
    }
}

int Menu::getIntegerInput(const std::string &message, bool mustPositive) {
    bool isNum = false;
    bool isPositive = false;
    int val;
    while (!isNum) {
        std::cout << message;
        std::string input;
        std::cin.clear();
        std::cin.sync();
        getline(std::cin, input);
        try {
            val = std::stoi(input);
            if (val > 0) isPositive = true;
            if (!mustPositive) isNum = true;
            else if (isPositive) isNum = true;
            else isNum = false;
        } catch (std::invalid_argument &e) {
            std::cout << "Input data is not numerical" << std::endl;
            continue;
        }
        catch (std::out_of_range &e) {
            std::cout << "Input number is too large" << std::endl;
            continue;
        }
    }
    return val;
}

void Menu::printException(std::exception &e) {
    std::cout << "X-----------------------------X\n";
    std::cout << "WARNING: An error has occurred:\n";
    std::cerr << e.what() << "\n";
    std::cout << "X-----------------------------X\n";
}

void Menu::loadFromFile() {
    std::string fileName;
    std::cout << "Please enter the file's name: ";
    std::cin >> fileName;
    std::cout << std::endl;
    std::cout << "Loading data from the file..." << std::endl;
    try {
        FileReader reader(fileName);
        graphRepresentation = new GraphRepresentation(0, 0);
        reader.readToAdjMatrix(graphRepresentation);
    } catch (std::runtime_error &e) {
        printException(e);
        Sleep(200);
        return;
    }
    std::cout << "Data loaded successfully!" << std::endl << std::endl;
    std::cout << ">------------------------------------------------------------------------------|" << std::endl;
}

void Menu::printGraph() {
    try {
        if (graphRepresentation == nullptr) throw std::invalid_argument("There is nothing to read from!");
        std::cout << "Graph's adjacency matrix representation: " << std::endl;
        graphRepresentation->print();
    } catch (std::invalid_argument &e) {
        printException(e);
        Sleep(200);
        return;
    }
}

void Menu::heldKarp() {
    try {
        if (graphRepresentation == nullptr) throw std::invalid_argument("There is nothing to read from!");
        HeldKarp hKarp(graphRepresentation, 0);
        hKarp.Start();
    } catch (std::invalid_argument &e){
        printException(e);
        Sleep(200);
        return;
    }
}

void Menu::benchmark() {
    try {
        std::string iniFile;
        std::cout << "Please enter the name of the .ini file: " << std::endl;
        std::cin >> iniFile;
        readFromIni(iniFile);
    } catch (std::invalid_argument &e) {
        printException(e);
        Sleep(200);
        return;
    }
}

void Menu::readFromIni(std::string &fileName) {
    std::cout << fileName << std::endl;
    std::vector<int> numbersOfCalls;
    std::vector<int> costs;
    std::vector<std::string> graphFiles;
    std::vector<std::vector<int>> correctCycles;
    std::string csvFile;

    std::ifstream inputFile(fileName, std::ios::in);

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
            int numberOfCalls;
            int cost;
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
    for (int i = 0; i < graphFiles.size(); i++) {
        FileReader reader(graphFiles[i]);
        auto* graph = new GraphRepresentation(0, 0);
        reader.readToAdjMatrix(graph);

        outputFile << graphFiles[i];

        for (int j = 0; j < numbersOfCalls[i]; j++) {
            std::cout << std::endl;
            std::cout << "Measure nr " << j + 1 << std::endl;
            auto* hk = new HeldKarp(graph, 0);

            hk->Start();
            outputFile << ";" << hk->time;

            bool errorFlag = false;
            std::vector<int> temporaryCycle = hk -> hamiltonianCycle;

            for (int k = 0; k < temporaryCycle.size(); k++) {
                if (temporaryCycle[k] != correctCycles[i][k]) errorFlag = true;
            }

            if (costs[i] != hk -> distancePublic || errorFlag) {
                std::cout << "Calculated cost or cycle is incorrect" << std::endl;
            }
        }
        outputFile << std::endl;
        delete graph;
    }
    outputFile.close();
}
