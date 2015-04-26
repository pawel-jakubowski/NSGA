#ifndef GENOTYPEMOCK_H
#define GENOTYPEMOCK_H

#include <Genotype.h>

class GenotypeMock : public Genotype
{
public:
    GenotypeMock(std::vector<double> x, GoalFunctions& f)
        : Genotype(f)
    {
        getFValues(f[0], f[1], x);
    }
    virtual ~GenotypeMock() {}
};

#endif // GENOTYPEMOCK_H
