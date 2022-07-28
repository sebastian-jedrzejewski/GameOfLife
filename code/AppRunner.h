#ifndef _APP_RUNNER_H_
#define _APP_RUNNER_H_

#include <string>
#include "Generation.h"

class AppRunner {
private:
    std::string initFile;
    bool stepByStep;
    Generation initGeneration;
    Generation currentGeneration;
    int numberOfGenerations;

    void randomGeneration();

public:
    AppRunner();
    AppRunner(std::string initFile, bool stepByStep=true);
    void setInitFile(std::string name);
    void setStepByStep(bool mode);
    void run();
};

#endif