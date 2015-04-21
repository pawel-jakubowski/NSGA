#ifndef SUBJECT_H
#define SUBJECT_H

#include <Genotype.h>

class Subject
{
public:
    Subject(ExpressionPtr newf1, ExpressionPtr newf2);
    Subject(const Subject& parentA, const Subject& parentB);
    virtual ~Subject() {}

    double rateByF1() const;
    double rateByF2() const;
    const unsigned& getRank() const;
    const unsigned& getDistance() const;
    void setRank(const unsigned& newRank);
    void setDistance(const unsigned& newDistance);
    
    // Crowded distance operator
    bool operator<(const Subject& r);
protected:
    Genotype gen;
    unsigned nondominationRank;
    unsigned crowdingDistance;
};

#endif // SUBJECT_H
