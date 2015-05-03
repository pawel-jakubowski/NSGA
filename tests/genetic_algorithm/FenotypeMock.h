#ifndef FENOTYPEMOCK_H
#define FENOTYPEMOCK_H

#include <Fenotype.h>

class FenotypeMock : public Fenotype
{
public:
    FenotypeMock(std::vector<double> x, GoalFunctions& f)
        : Fenotype(f, -5.0, 5.0)
    {
        getFValues(f, x);
    }
    virtual ~FenotypeMock() {}
};

#endif // FENOTYPEMOCK_H
