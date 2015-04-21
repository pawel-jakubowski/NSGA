#include "Subject.h"

Subject::Subject(ExpressionPtr newf1, ExpressionPtr newf2)
    : gen(newf1, newf2)
{
}

Subject::Subject(const Subject &parentA, const Subject &parentB) : gen(parentA.gen, parentB.gen)
{
}

double Subject::rateByF1() const
{
    return gen.rateByF1();
}

double Subject::rateByF2() const
{
    return gen.rateByF2();
}

const unsigned &Subject::getRank() const
{
    return nondominationRank;
}

const unsigned &Subject::getDistance() const
{
    return crowdingDistance;
}

void Subject::setRank(const unsigned &newRank)
{
    nondominationRank = newRank;
}

void Subject::setDistance(const unsigned &newDistance)
{
    crowdingDistance = newDistance;
}

bool Subject::operator<(const Subject &r)
{
    if(nondominationRank == r.nondominationRank)
        return crowdingDistance > r.crowdingDistance;
    else
        return nondominationRank < r.nondominationRank;
}
