#ifndef POPULATION_H
#define POPULATION_H

#include <Generation.h>

class Population
{
public:
    Population(unsigned firstGenerationSize, Expression& newf1, Expression& newf2);

    void generateGenerations(unsigned generationsCount);
    unsigned generationsCount();
    unsigned sizeOfGeneration(unsigned generationNumber);
private:
    Expression& f1;
    Expression& f2;
    std::vector<Generation> generations;
};

#endif // POPULATION_H
