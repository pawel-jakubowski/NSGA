#ifndef FENOTYPE_H
#define FENOTYPE_H

#include <GoalFunctions.h>
#include <RandomGenerator.h>
#include <memory>
#include <vector>

class Fenotype
{
public:
    Fenotype(GoalFunctions& newf, double genLowerBound, double genUpperBound);
    Fenotype(const Fenotype& fenotypeA, const Fenotype& fenotypeB);
    virtual ~Fenotype() {}

    const double& rateByF(const unsigned& function) const;
    std::vector<double> getGenotype() const;
protected:
    RandomGenerator generator;
    GoalFunctions* f;
    std::vector<double> fValue;
    std::vector<double> gen;

    void crossover(const std::vector<double> &genotypeA, const std::vector<double> &genotypeB);
    void mutate();
    void fillWithRandomVariables(std::vector<double>& randomX, double lowerBound, double upperBound);
    void getFValues(GoalFunctions& f, std::vector<double>& variables);

};

#endif // FENOTYPE_H
