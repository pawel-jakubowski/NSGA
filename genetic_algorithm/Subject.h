#ifndef SUBJECT_H
#define SUBJECT_H

#include <Genotype.h>

class Subject
{
public:
    Subject(const Genotype& newGen);
    Subject(GoalFunctions& f);
    Subject(const Subject& parentA, const Subject& parentB);
    virtual ~Subject() {}

    const double& rateByF(const unsigned& function) const;
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

class compareByF
{
public:
    compareByF(const unsigned& function) : functionId(function) {}
    inline bool operator() (const Subject* subject1, const Subject* subject2)
    {
        return (subject1->rateByF(functionId) < subject2->rateByF(functionId));
    }
private:
    unsigned functionId;
};

#endif // SUBJECT_H
