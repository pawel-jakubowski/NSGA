#include "Population.h"
#include <CustomAssertion.h>
#include <iostream>

Population::Population(unsigned firstGenerationSize, GoalFunctions& newf)
    : f(&newf)
    , generations(1, Generation(firstGenerationSize, *f))
{
}

std::vector<std::vector<double>> Population::generateGenerations(unsigned generationsCount)
{
    assert(generations.size() >= 1);
    generations.resize(1, Generation(sizeOfGeneration(1), *f));
    for (unsigned i = 0; i < generationsCount - 1; ++i)
    {
        std::cout << "generation " << i << std::flush << std::endl;
        generations.push_back(generations[i].produceNextGeneration());
    }
    generations.shrink_to_fit();

    return generations[0].getFirstFront();
}

unsigned Population::generationsCount()
{
    return generations.size();
}

unsigned Population::sizeOfGeneration(unsigned generationNumber)
{
    assert(generationNumber <= generations.size());
    return generations[generationNumber - 1].size();
}
