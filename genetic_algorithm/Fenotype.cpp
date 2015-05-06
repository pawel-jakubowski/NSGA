#include "Fenotype.h"
#include <CustomAssertion.h>
#include <random>
#include <iostream>

Fenotype::Fenotype(GoalFunctions& newf, double genLowerBound, double genUpperBound)
    : f(&newf)
    , fValue(f->size(),0)
{
    gen.resize(f->at(0).variablesCount());
    fillWithRandomVariables(gen, genLowerBound, genUpperBound);
    getFValues(*f, gen);
}

Fenotype::Fenotype(const Fenotype &fenotypeA, const Fenotype &fenotypeB)
    : f(fenotypeA.f)
    , fValue(f->size(),0)
{
    crossover(fenotypeA.getGenotype(), fenotypeB.getGenotype());
    mutate();
    getFValues(*f, gen);
}

void Fenotype::crossover(const std::vector<double>& genotypeA, const std::vector<double>& genotypeB)
{
    assert(genotypeA.size() == genotypeB.size());
    gen.resize(genotypeA.size());

    for(unsigned i = 0; i < genotypeA.size(); ++i)
    {
        if(genotypeA[i] < genotypeB[i])
            gen[i] = generator.rand(genotypeA[i], genotypeB[i]);
        else
            gen[i] = generator.rand(genotypeB[i], genotypeA[i]);
    }
}

void Fenotype::mutate()
{
    for(auto& xElem : gen)
    {
        xElem += generator.randn(0,1);
    }
}

const double& Fenotype::rateByF(const unsigned& function) const
{
    assert(function < fValue.size());
    return fValue[function];
}

std::vector<double> Fenotype::getGenotype() const
{
    return gen;
}

void Fenotype::fillWithRandomVariables(std::vector<double>& randomX, double lowerBound, double upperBound)
{
    for(auto& x : randomX)
        x = generator.rand(lowerBound, upperBound);
}

void Fenotype::getFValues(GoalFunctions &f, std::vector<double>& variables)
{
    gen = variables;
    int i = -1;
    for(unsigned m = 0; m < f.size(); ++m)
    {
        i = -1;
        for(auto& key : f[m].getAllVariableKeys())
            f[m](key) = gen[++i];
        fValue[m] = f[m].value();
    }
}
