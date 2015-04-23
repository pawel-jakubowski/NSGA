#ifndef GENOTYPE_H
#define GENOTYPE_H

#include <Expression.h>
#include <memory>
#include <vector>

class Genotype
{
public:
    Genotype(Expression& f1, Expression& f2);
    Genotype(const Genotype& genA, const Genotype& genB);
    virtual ~Genotype() {}

    void mutate();
    double rateByF1() const;
    double rateByF2() const;
    std::vector<double> getFenotype() const;
protected:
    double f1Value;
    double f2Value;
    std::vector<double> x;

<<<<<<< HEAD
    double generateRandom(double lowerBound, double upperBound);
    double generateRandomN(double center, double sigma);
    void fillWithRandomVariables(std::vector<double>& randomX, double lowerBound, double upperBound);
    void getFValues(ExpressionPtr f1, ExpressionPtr f2, std::vector<double>& variables);
=======
    void fillWithRandomVariables(std::vector<double>& randomX);
    void getFValues(Expression& f1, Expression& f2, std::vector<double>& x);
>>>>>>> Implement non dominated sort
};

#endif // GENOTYPE_H
