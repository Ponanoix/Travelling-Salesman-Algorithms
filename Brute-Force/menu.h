//
// Created by Ponanoix on 17.10.2023.
//

#ifndef PEA_MENU_H
#define PEA_MENU_H

#include "file-reader.h"

class Menu{
private:
    GraphRepresentation* graphRepresentation = nullptr;                                     // Holds the representation of the graph

    void printMainMenu();                                                                   // Prints main menu

    static int getIntegerInput(const std::string& message, bool mustPositive = false);      // Prompts user with message to input integer value and returns it

    static void printException(std::exception &e);                                          // Nicely prints thrown exception on stdout
    void readFromIni(std::string &fileName);
public:
    Menu();                                                                                 // Constructor

    void loadFromFile();                                                                    // Menu utility

    void printGraph();                                                                      // Prints loaded graph

    void bruteForce();                                                                      // Starts the bruteForce algorithm

    void benchmark();                                                                       // Starts the benchmark, based on .ini file's contents
};

#endif //PEA_MENU_H
