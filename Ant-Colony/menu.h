//
// Created by Ponanoix on 20.01.2024.
//

#ifndef PEA_4_MENU_H
#define PEA_4_MENU_H

#include"file-reader.h"

class Menu{
private:
    // Variable to store the loaded file's name
    std::string loadedFileName;

    // Pointer to the graph
    GraphRepresentation* graphRepresentation = nullptr;

    // Prints main menu
    void printMenu();

    // Prompts the user with a message to input an integer value and returns it
    static int getIntegerInput(const std::string &message);

    // Prints an error message if it catches one
    static void printException(std::exception &e);

    // Analyses the contents of an .ini file and executes them accordingly
    static void readAnIniFile(std::string &fileName);
public:
    // Constructor
    Menu();

    // Loads a graph from a file and saves it in memory
    void loadAGraphFromAFile();

    // Prints a graph (NOTE: needs to be loaded first!)
    void printAGraph();

    // Executes the Ant Colony Optimization algorithm (single instance)
    void antColonyOptimization();

    // Starts the benchmark, based on a loaded .ini file's contents
    static void benchmark();
};

#endif //PEA_4_MENU_H
