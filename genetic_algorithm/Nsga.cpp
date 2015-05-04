#include "Nsga.h"

void Nsga::execute(const CoreSettings &settings)
{
    if(results.size() != settings.f.size())
        results.resize(settings.f.size());

    GoalFunctions f(settings.f.size(), settings.variablesCount);
    for(unsigned i = 0; i < settings.f.size(); ++i)
        f[i].parse(settings.f[i]);

    population.reset(new Population(settings.individualsCount, f));
    results = population->generateGenerations(settings.generationsCount);
}

const ResultType& Nsga::result()
{
    return results;
}
