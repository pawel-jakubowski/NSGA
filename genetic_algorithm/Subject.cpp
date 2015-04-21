#include "Subject.h"

Subject::Subject(const Genotype &newGen)
    : gen(newGen)
{
}

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

bool Subject::isDominatedBy(const Subject &s)
{
    bool isDominatedWithRespectToF1 = (s.rateByF1() < rateByF1()) && (s.rateByF2() <= rateByF2());
    bool isDominatedWithRespectToF2 = (s.rateByF2() < rateByF2()) && (s.rateByF1() <= rateByF1());
    return isDominatedWithRespectToF1 || isDominatedWithRespectToF2;
}

bool Subject::operator<(const Subject &r)
{
    if(nondominationRank == r.nondominationRank)
        return crowdingDistance > r.crowdingDistance;
    else
        return nondominationRank < r.nondominationRank;
}
