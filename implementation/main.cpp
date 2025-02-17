/**
 * @mainpage Lecture EDA Program Documentation
 * This documentation shows the API and custom algorithms of the EDA lecture's additional programming exercise.
 */
 
#include <iostream>
#include <fstream>
#include <string>

#include "Circuit/Circuit.h"
#include "Parser/Parser.h"
#include "Analysis-EDA/AnalysisEDA.h"

/**
 * @brief The main function calls the circuit parser, reads the stimuli file and calls the AnalysisEDA.run function.
 */
int main(int argc, const char** argv) {
    const char* defaultCircuit = "../examples/circuit01.yal";
    const char* defaultTopcell = "CIRCUIT01";
    const char* defaultLib = "../examples/library.yal";
    if (argc < 4) {
        argc = 4;
        argv[1] = const_cast<char*>(defaultCircuit);
        argv[2] = const_cast<char*>(defaultTopcell);
        argv[3] = const_cast<char*>(defaultLib);
    }

    Circuit circuit;
    Parser::parse(argc, argv, &circuit);

    std::vector<std::string> args(argv, argv+argc);
    size_t pos = args[1].find_last_of("/\\");
    std::string path = args[1].substr(0, pos);
    std::string inFileName(path + "/" + args[2] + "_in.csv");
    std::ifstream inputFile;
    std::vector<std::vector<Logic>> inputData;

    inputFile.open(inFileName);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open " << inFileName << std::endl;
    } else {
        std::vector<Logic> inputValues;
        while (inputFile.good()) {
            char value = static_cast<char>(inputFile.get());
            inputValues.push_back(static_cast<Logic>(value - '0'));
            if (inputFile.get() == '\n') {
                inputData.push_back(inputValues);
                inputValues.clear();
            }
        }
    }
    inputFile.close();

    AnalysisEDA analysisEDA(&circuit, inputData);

    analysisEDA.run();

    return 0;
}
