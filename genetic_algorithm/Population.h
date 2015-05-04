#ifndef POPULATION_H
#define POPULATION_H

#include <Generation.h>

class Population
{
public:
    Population(unsigned firstGenerationSize, GoalFunctions &newf);

    std::vector<std::vector<double>> generateGenerations(unsigned generationsCount);
    unsigned generationsCount();
    unsigned sizeOfGeneration(unsigned generationNumber);
private:
    GoalFunctions* f;
    std::vector<Generation> generations;
};

#endif // POPULATION_H
