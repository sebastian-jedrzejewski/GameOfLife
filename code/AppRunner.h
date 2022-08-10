#ifndef _APP_RUNNER_H_
#define _APP_RUNNER_H_

#include <string>
#include "Generation.h"
#include "Image.h"

class AppRunner {
private:
    // Constant defining standard width and height of generated image.
    // If both board dimensions are smaller than it, then image size is
    // defined by this constant. If either of board dimensions is greater,
    // then image size in pixels is equal to board size.
    const int BASE_IMAGE_SIZE = 500;

    std::string initFile;
    bool generateFiles;
    bool generateImages;
    bool stepByStep;
    Generation initGeneration; // on the base of it, currentGeneration is created
    Generation currentGeneration;
    int numberOfGenerations;

    void randomGeneration();
    void generateImage(Image &image);

public:
    AppRunner();
    AppRunner(std::string initFile, bool generateFiles, bool generateImages, bool stepByStep);
    void setInitFile(std::string name);
    void setStepByStep(bool mode);
    void setGenerateFiles(bool mode);
    void setGenerateImages(bool mode);
    bool getStepByStep() const;
    bool getGenerateFiles() const;
    bool getGenerateImages() const;
    std::string getInitFile() const;
    void run();
};

#endif