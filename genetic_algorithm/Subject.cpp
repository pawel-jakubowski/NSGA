#include "Subject.h"

#include <iostream>

Subject::Subject(const Genotype &newGen)
    : gen(newGen)
    , nondominationRank(0)
    , crowdingDistance(0)
{
    std::cout << "crowding = " << crowdingDistance << std::endl;
}

Subject::Subject(Expression& f1, Expression& f2)
    : gen(f1, f2)
    , nondominationRank(0)
    , crowdingDistance(0)
{
    std::cout << "(f1 f2) crowding = " << crowdingDistance << std::endl;
}

Subject::Subject(const Subject &parentA, const Subject &parentB)
    : gen(parentA.gen, parentB.gen)
    , nondominationRank(0)
    , crowdingDistance(0)
{
    std::cout << "(child) crowding = " << crowdingDistance << std::endl;
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

unsigned Subject::getDistance() const
{
    std::cout << crowdingDistance << std::endl;
    return crowdingDistance;
}

void Subject::setRank(const unsigned &newRank)
{
    nondominationRank = newRank;
}

void Subject::setDistance(const unsigned &newDistance)
{
    std::cout << crowdingDistance << " is now " << newDistance << std::endl;
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
