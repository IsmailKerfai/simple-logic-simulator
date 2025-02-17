/*
 * AnalysisEDA.h
 */

#ifndef AnalysisEDA_H_
#define AnalysisEDA_H_

#include <vector>
#include "template.h"

// forward declarations
class Circuit;

class AnalysisEDA {
public:
    AnalysisEDA(const Circuit* circuit, const std::vector<std::vector<Logic>>& inputData) :
        circuit(circuit), inputData(inputData) {
    }
    virtual ~AnalysisEDA() {
    }

    void run();

private:
    // prevent from using the default constructor, copy constructor and assignment operator
    AnalysisEDA();
    AnalysisEDA(const AnalysisEDA&);
    AnalysisEDA& operator=(const AnalysisEDA&);

    const Circuit* circuit;
    const std::vector<std::vector<Logic>>& inputData;
};

#endif /* AnalysisEDA_H_ */
