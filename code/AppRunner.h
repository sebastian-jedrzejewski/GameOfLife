#ifndef _APP_RUNNER_H_
#define _APP_RUNNER_H_

#include <string>
#include "Generation.h"

class AppRunner {
private:
    std::string initFile;
    bool stepByStep;
    Generation initGeneration; // on the base of it, currentGeneration is created
    Generation currentGeneration;
    int numberOfGenerations;

    void randomGeneration();

public:
    AppRunner();
    AppRunner(std::string initFile, bool stepByStep=true);
    void setInitFile(std::string name);
    void setStepByStep(bool mode);
    bool getStepByStep();
    std::string getInitFile();
    void run();
};

#endif