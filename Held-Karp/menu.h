//
// Created by Ponanoix on 02.11.2023.
//

#ifndef PEA_2_MENU_H
#define PEA_2_MENU_H

#include "file-reader.h"

class Menu{
private:
    GraphRepresentation* graphRepresentation = nullptr;                                     // Holds the representation of the graph

    void printMainMenu();                                                                   // Prints main menu

    static int getIntegerInput(const std::string& message, bool mustPositive = false);      // Prompts user with message to input integer value and returns it

    static void printException(std::exception &e);                                          // Nicely prints thrown exception on stdout

    static void readFromIni(std::string &fileName);                                         // This function analyses .ini file contents and executes appropriate actions
public:
    Menu();                                                                                 // Constructor

    void loadFromFile();                                                                    // Menu utility

    void printGraph();                                                                      // Prints loaded graph

    void heldKarp();                                                                        // Starts the heldKarp algorithm (implement it first)

    static void benchmark();                                                                // Starts the benchmark, based on .ini file's contents
};

#endif //PEA_2_MENU_H
