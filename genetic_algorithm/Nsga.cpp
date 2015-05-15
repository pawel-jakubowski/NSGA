#include "Nsga.h"
#include <iostream>

void Nsga::execute(const CoreSettings &settings)
{
    std::cout << "CoreSettings:" << std::endl
              << "f1 = " << settings.f[0] << std::endl
              << "f2 = " << settings.f[1] << std::endl
              << "----------------------" << std::endl
              << "g1 = " << settings.g[0] << std::endl
              << "g2 = " << settings.g[1] << std::endl
              << "g3 = " << settings.g[2] << std::endl
              << "g4 = " << settings.g[3] << std::endl
              << "g5 = " << settings.g[4] << std::endl
              << "boundaries = " << settings.g[5] << std::endl
              << "----------------------" << std::endl
              << "variables: " << settings.variablesCount << std::endl
              << "individuals: " << settings.individualsCount << std::endl
              << "generations: " << settings.generationsCount << std::endl
              << "lower bound: " << settings.lowerBound << std::endl
              << "upper bound: " << settings.upperBound << std::endl;

    if(results.size() != settings.f.size())
        results.resize(settings.f.size());

    Functions f(settings.f.size(), settings.variablesCount);
    for(unsigned i = 0; i < settings.f.size(); ++i)
        f[i].parse(settings.f[i]);

    Functions g(settings.g.size(), settings.variablesCount);
    for(unsigned i = 0; i < settings.g.size(); ++i)
        g[i].parse(settings.g[i]);

    population.reset(new Population(settings.individualsCount, f, g, settings.lowerBound,
                        settings.upperBound));
    results = population->generateGenerations(settings.generationsCount);
}

const ResultType& Nsga::result()
{
    return results;
}
