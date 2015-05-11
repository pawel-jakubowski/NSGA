#include "Nsga.h"

void Nsga::execute(const CoreSettings &settings)
{
    if(results.size() != settings.f.size())
        results.resize(settings.f.size());

    Functions f(settings.f.size(), settings.variablesCount);
    for(unsigned i = 0; i < settings.f.size(); ++i)
        f[i].parse(settings.f[i]);

    Functions g(settings.g.size(), settings.variablesCount);
    for(unsigned i = 0; i < settings.g.size(); ++i)
        g[i].parse(settings.g[i]);

    population.reset(new Population(settings.individualsCount, f, g));
    results = population->generateGenerations(settings.generationsCount);
}

const ResultType& Nsga::result()
{
    return results;
}
