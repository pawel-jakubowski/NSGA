#ifndef GENOTYPEMOCK_H
#define GENOTYPEMOCK_H

#include <Genotype.h>

class GenotypeMock : public Genotype
{
public:
    GenotypeMock(std::vector<double> x, Expression& f1, Expression& f2)
        : Genotype(f1, f2)
    {
        getFValues(f1, f2, x);
    }
    virtual ~GenotypeMock() {}
};

#endif // GENOTYPEMOCK_H
