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
    const double& getDistance() const;
    void setRank(const unsigned& newRank);
    void setDistance(const double& newDistance);
    
    bool isDominatedBy(const Subject& s);
    // Crowded distance operator
    bool operator<(const Subject& r);
protected:
    Genotype gen;
    unsigned nondominationRank;
    double crowdingDistance;
};

struct compareByF1
{
    inline bool operator() (const Subject& subject1, const Subject& subject2)
    {
        return (subject1.rateByF1() < subject2.rateByF1());
    }
};

struct compareByF2
{
    inline bool operator() (const Subject& subject1, const Subject& subject2)
    {
        return (subject1.rateByF2() < subject2.rateByF2());
    }
};

#endif // SUBJECT_H
