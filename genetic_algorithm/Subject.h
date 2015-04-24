#ifndef SUBJECT_H
#define SUBJECT_H

#include <Genotype.h>

class Subject
{
public:
    Subject(const Genotype& newGen);
    Subject(Expression &f1, Expression &f2);
    Subject(const Subject& parentA, const Subject& parentB);
    virtual ~Subject() {}

    double rateByF1() const;
    double rateByF2() const;
    const unsigned& getRank() const;
    unsigned getDistance() const;
    void setRank(const unsigned& newRank);
    void setDistance(const unsigned& newDistance);
    
    bool isDominatedBy(const Subject& s);
    // Crowded distance operator
    bool operator<(const Subject& r);
protected:
    Genotype gen;
    unsigned nondominationRank;
    unsigned crowdingDistance;
};

#endif // SUBJECT_H
