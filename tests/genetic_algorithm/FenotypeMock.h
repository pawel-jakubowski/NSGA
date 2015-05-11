#ifndef FENOTYPEMOCK_H
#define FENOTYPEMOCK_H

#include <Fenotype.h>

class FenotypeMock : public Fenotype
{
public:
    FenotypeMock(std::vector<double> x, Functions& goalFunctions, Functions& constraints)
        : Fenotype(goalFunctions, constraints, -5.0, 5.0)
    {
        gen = x;
        calculateFunctionsValues();
        calculateViolatedConstraints();
    }
    virtual ~FenotypeMock() {}
};

#endif // FENOTYPEMOCK_H
