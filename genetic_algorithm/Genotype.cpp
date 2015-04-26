#include "Genotype.h"
#include <CustomAssertion.h>
#include <random>

Genotype::Genotype(GoalFunctions& newf)
    : f(&newf)
    , fValue(2,0)
{
    assert(f->at(0).variablesCount() == f->at(1).variablesCount());

    x.resize(f->at(0).variablesCount());
    double LB = -5;
    double UB = 5;
    fillWithRandomVariables(x, LB, UB);
    getFValues(f->at(0), f->at(1), x);
}

Genotype::Genotype(const Genotype &genA, const Genotype &genB)
    : f(genA.f)
    , fValue(2,0)
{
    std::vector<double> fenotypeA = genA.getFenotype();
    std::vector<double> fenotypeB = genB.getFenotype();

    assert(fenotypeA.size() == fenotypeB.size());
    x.resize(fenotypeA.size());

    for(unsigned i = 0; i < fenotypeA.size(); ++i)
    {
        if(fenotypeA[i] < fenotypeB[i])
            x[i] = Genotype::generateRandom(fenotypeA[i], fenotypeB[i]);
        else
            x[i] = Genotype::generateRandom(fenotypeB[i], fenotypeA[i]);
    }
    mutate();
    getFValues(f->at(0), f->at(1), x);
}

void Genotype::mutate()
{   for(auto& xElem : x)
    {
        xElem += generateRandomN(0,1);
    }
}

const double& Genotype::rateByF(const unsigned& function) const
{
    assert(function < fValue.size());
    return fValue[function];
}

std::vector<double> Genotype::getFenotype() const
{
    return x;
}

double Genotype::generateRandom(double lowerBound, double upperBound)
{
    std::uniform_real_distribution<double> dist(lowerBound, upperBound);
    static std::random_device seed;
    static std::mt19937 randomNumberGenerator(seed());
    return dist(randomNumberGenerator);
}

double Genotype::generateRandomN(double center, double sigma)
{
    std::normal_distribution<double> dist(center, sigma);
    static std::random_device seed;
    static std::mt19937 randomNumberGenerator(seed());
    return dist(randomNumberGenerator);
}

void Genotype::fillWithRandomVariables(std::vector<double>& randomX, double lowerBound, double upperBound)
{
    for(auto& x : randomX)
        x = generateRandom(lowerBound, upperBound);
}

void Genotype::getFValues(Expression& f1, Expression& f2, std::vector<double>& variables)
{
    x = variables;
    int i = -1;
    for(auto& key : f1.getAllVariableKeys())
        f1.at(key) = f2.at(key) = x[++i];
    fValue[0] = f1.value();
    fValue[1] = f2.value();
}
