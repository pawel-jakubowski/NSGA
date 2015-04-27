#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <GoalFunctions.h>
#include <memory>
#include <vector>

class Genotype
{
public:
    Genotype(GoalFunctions& newf);
    Genotype(const Genotype& genA, const Genotype& genB);
    virtual ~Genotype() {}

    const double& rateByF(const unsigned& function) const;
    std::vector<double> getFenotype() const;
protected:
    GoalFunctions* f;
    std::vector<double> fValue;
    std::vector<double> x;

    void mutate();
    double generateRandom(double lowerBound, double upperBound);
    double generateRandomN(double center, double sigma);
    void fillWithRandomVariables(std::vector<double>& randomX, double lowerBound, double upperBound);
    void getFValues(Expression& f1, Expression& f2, std::vector<double>& variables);

};

#endif // GENOTYPE_H
