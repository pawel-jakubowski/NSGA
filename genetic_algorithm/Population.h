#ifndef POPULATION_H
#define POPULATION_H

#include <Generation.h>

class Population
{
public:
    Population(unsigned firstGenerationSize, Functions &newGoalFunctions, Functions &newConstraints);

    std::vector<std::vector<double>> generateGenerations(unsigned generationsCount);
    unsigned generationsCount();
    unsigned sizeOfGeneration(unsigned generationNumber);
private:
    Functions* goalFunctions;
    Functions* constraints;
    std::vector<Generation> generations;
};

#endif // POPULATION_H
