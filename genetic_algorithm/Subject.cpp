#include "Subject.h"

Subject::Subject(const Genotype &newGen)
    : gen(newGen)
    , nondominationRank(0)
    , crowdingDistance(0)
{
}

Subject::Subject(GoalFunctions& f)
    : gen(f)
    , nondominationRank(0)
    , crowdingDistance(0)
{
}

Subject::Subject(const Subject &parentA, const Subject &parentB)
    : gen(parentA.gen, parentB.gen)
    , nondominationRank(0)
    , crowdingDistance(0)
{
}

const double& Subject::rateByF(const unsigned& function) const
{
    return gen.rateByF(function);
}

const unsigned &Subject::getRank() const
{
    return nondominationRank;
}

const double &Subject::getDistance() const
{
    return crowdingDistance;
}


void Subject::setRank(const unsigned &newRank)
{
    nondominationRank = newRank;
}

void Subject::setDistance(const double &newDistance)
{
    crowdingDistance = newDistance;
}

bool Subject::isDominatedBy(const Subject &s)
{
    bool isDominatedWithRespectToF1 = (s.rateByF(0) < rateByF(0)) && (s.rateByF(1) <= rateByF(1));
    bool isDominatedWithRespectToF2 = (s.rateByF(1) < rateByF(1)) && (s.rateByF(0) <= rateByF(0));
    return isDominatedWithRespectToF1 || isDominatedWithRespectToF2;
}

bool Subject::operator<(const Subject &r)
{
    if(nondominationRank == r.nondominationRank)
        return crowdingDistance > r.crowdingDistance;
    else
        return nondominationRank < r.nondominationRank;
}

bool Subject::operator==(const Subject &r, const Subject &l)
{

}
