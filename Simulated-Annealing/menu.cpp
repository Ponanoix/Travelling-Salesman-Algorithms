//
// Created by Ponanoix on 18.12.2023.
//

#include "simulated-annealing.h"
#include "menu.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <cmath>

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
                simulatedAnnealing();
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

void Menu::simulatedAnnealing() {
    try {
        if (graphRepresentation == nullptr) throw std::invalid_argument("There is nothing to read from!");
        int input1;
        std::cout << "Please choose the cooling schedule: " << std::endl;
        std::cout << "1. Geometric" << std::endl;
        std::cout << "2. Linear" << std::endl;
        std::cin >> input1;
        int input2;
        std::cout << "Please choose the method of setting the initial temperature: " << std::endl;
        std::cout << "1. Set" << std::endl;
        std::cout << "2. Adaptive" << std::endl;
        std::cin >> input2;
        int input3;
        std::cout << "Please choose the method of exploration in a neighbourhood: " << std::endl;
        std::cout << "1. Random" << std::endl;
        std::cout << "2. Greedy" << std::endl;
        std::cin >> input3;
        int input4;
        std::cout << "Please choose the method of coming up with a solution in a neighbourhood: " << std::endl;
        std::cout << "1. 2-Swap" << std::endl;
        std::cout << "2. Reversal" << std::endl;
        std::cin >> input4;
        if(input1 == 1) {
            if(input2 == 1) {
                if(input3 == 1) {
                    if(input4 == 1) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, SET, RANDOM, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, SET, RANDOM, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                } else if (input3 == 2) {
                    if (input4 == 1) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, SET, GREEDY, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, SET, GREEDY, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                }
            } else if(input2 == 2) {
                if(input3 == 1) {
                    if(input4 == 1){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, ADAPTIVE, RANDOM, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, ADAPTIVE, RANDOM, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                } else if (input3 == 2) {
                    if(input4 == 1){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, ADAPTIVE, GREEDY, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, GEOMETRIC, ADAPTIVE, GREEDY, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
            } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
        } else if (input1 == 2) {
            if(input2 == 1) {
                if(input3 == 1) {
                    if(input4 == 1) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, SET, RANDOM, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, SET, RANDOM, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                } else if (input3 == 2) {
                    if (input4 == 1) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, SET, GREEDY, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2) {
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, SET, GREEDY, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                }
            } else if(input2 == 2) {
                if(input3 == 1) {
                    if(input4 == 1){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, ADAPTIVE, RANDOM, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, ADAPTIVE, RANDOM, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                } else if (input3 == 2) {
                    if(input4 == 1){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, ADAPTIVE, GREEDY, TWO_SWAP);
                        sAnnealing.Start();
                    } else if (input4 == 2){
                        SimulatedAnnealing sAnnealing(graphRepresentation, 0, LINEAR, ADAPTIVE, GREEDY, REVERSAL);
                        sAnnealing.Start();
                    } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
                } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
            } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
        } else throw std::invalid_argument("Incorrect input, type either ""1"" or ""2""");
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
    for (int i = 0; i < graphFiles.size(); i++) {
        FileReader reader(graphFiles[i]);
        auto* graph = new GraphRepresentation(0, 0);
        reader.readToAdjMatrix(graph);

        outputFile << graphFiles[i];

        for (int j = 0; j < numbersOfCalls[i]; j++) {
            std::cout << std::endl;
            std::cout << "Measure nr " << j + 1 << std::endl;
            auto* sa = new SimulatedAnnealing(graph, 0, GEOMETRIC, ADAPTIVE, RANDOM, TWO_SWAP);

            sa -> Start();
            outputFile << ";" << sa -> time;

            bool errorFlag = false;
            std::vector<int> temporaryCycle = sa -> hamiltonianCyclePublic;

            if (costs[i] != sa -> distancePublic) {
                float calculation;
                calculation = (abs(costs[i] - (sa -> distancePublic)) / costs[i]) * 100;
                std::cout << "Calculated cost is incorrect. Relative error: " << calculation << "%" << std::endl;
                //outputFile << ";" << calculation;
            }
        }
        outputFile << std::endl;
        delete graph;
    }
    outputFile.close();
}
