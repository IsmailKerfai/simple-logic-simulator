/*
 * AnalysisEDA.cpp
 *
 * This file contains the implementation of the simulator.
 */

#include "AnalysisEDA.h"
#include "Circuit/Circuit.h"
#include <iostream>
#include <algorithm>


void AnalysisEDA::run() {
    // Get all nets and elements from the circuit.
    auto nets = circuit->getAllNets();
    auto elements = circuit->getAllElements();
    
    // Initialize net states
    size_t numberOfNets = nets.size();
    std::vector<Logic> currentState(numberOfNets, Logic::logicX);
    std::vector<Logic> nextState(numberOfNets, Logic::logicX);
    
    // Process each input vector
    for (const auto& inputVector : inputData) {
        for (const Element* element : elements) {
            if (element->getElementInfo()->getType() == ElementType::Dff) {
                auto inNets = element->getInNets();
                auto outNets = element->getOutNets();
                if (!outNets.empty() && inNets.size() >= 2) {
                    currentState[outNets[0]->getId()] = nextState[outNets[0]->getId()];
                }
            }
        }

        // Assign primary inputs
        size_t inputIndex = 0;
        for (size_t i = 0; i < numberOfNets; i++) {
            if (nets[i]->getInElement() == nullptr) {
                currentState[i] = inputVector[inputIndex++];
            }
        }

        // Process combinational logic multiple times 
        bool changed;
        int maxIterations = 100;  
        do {
            changed = false;
            for (const Element* element : elements) {
                if (element->getElementInfo()->getType() == ElementType::Dff) {
                    continue;  
                }

                auto inNets = element->getInNets();
                auto outNets = element->getOutNets();
                ElementType type = element->getElementInfo()->getType();

                // Get input values
                std::vector<Logic> inputs;
                for (const Net* net : inNets) {
                    inputs.push_back(currentState[net->getId()]);
                }

                // Evaluate gate
                Logic output;
                switch (type) {
                    case ElementType::Not:
                        if (inputs[0] == Logic::logicX) {
                            output = Logic::logicX;
                        } else {
                            output = (inputs[0] == Logic::logic0) ? Logic::logic1 : Logic::logic0;
                        }
                        break;
                        
                    case ElementType::And:
                        if (std::find(inputs.begin(), inputs.end(), Logic::logic0) != inputs.end()) {
                            output = Logic::logic0;
                        } else if (std::find(inputs.begin(), inputs.end(), Logic::logicX) != inputs.end()) {
                            output = Logic::logicX;
                        } else {
                            output = Logic::logic1;
                        }
                        break;
                        
                    case ElementType::Or:
                        if (std::find(inputs.begin(), inputs.end(), Logic::logic1) != inputs.end()) {
                            output = Logic::logic1;
                        } else if (std::find(inputs.begin(), inputs.end(), Logic::logicX) != inputs.end()) {
                            output = Logic::logicX;
                        } else {
                            output = Logic::logic0;
                        }
                        break;

                    default:
                        throw std::runtime_error("Unsupported gate type");
                }

                // Update output if changed
                for (const Net* net : outNets) {
                    if (currentState[net->getId()] != output) {
                        currentState[net->getId()] = output;
                        changed = true;
                    }
                }
            }
            maxIterations--;
        } while (changed && maxIterations > 0);

        // Update flip-flop next state
        for (const Element* element : elements) {
            if (element->getElementInfo()->getType() == ElementType::Dff) {
                auto inNets = element->getInNets();
                auto outNets = element->getOutNets();
                if (!outNets.empty() && inNets.size() >= 2) {
                    nextState[outNets[0]->getId()] = currentState[inNets[1]->getId()];
                }
            }
        }

        // Output primary outputs
        std::vector<Logic> outputs;
        for (const Net* net : nets) {
            if (net->getOutElements().empty() || net->getOutElements()[0] == nullptr) {
                outputs.push_back(currentState[net->getId()]);
            }
        }

        // Print outputs
        for (size_t i = 0; i < outputs.size(); i++) {
            std::cout << outputs[i];
            if (i < outputs.size() - 1) {
                std::cout << ";";
            }
        }
        std::cout << std::endl;
    }


#if false
    /*
     * The following code shows some exemplary usage of the API
     */

    // Iterate all elements:
    for (const Element* element : circuit->getAllElements()) {
        std::cout << element->getName() << std::endl;
    }

    // Iterate all nets:
    for(const Net* net: circuit->getAllNets()) {
        std::cout << net->getName();
        if (net->getInElement() == nullptr)
            std::cout << " (primary input)";
        if (net->getOutElements()[0] == nullptr)
            std::cout << " (primary output)";
        std::cout << std::endl;
    }

    // Iterate all time steps:
    for (const std::vector<Logic>& timeStep : inputData) {
        for (const Logic& value : timeStep) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
#endif
}
