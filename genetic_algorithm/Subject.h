#ifndef SUBJECT_H
#define SUBJECT_H

#include <Fenotype.h>
#include <list>

class Subject
{
public:
    Subject(const Fenotype& newGen);
    Subject(GoalFunctions& f);
    Subject(const Subject& parentA, const Subject& parentB);
    virtual ~Subject() {}

    const double& rateByF(const unsigned& function) const;
    void checkDomination(Subject &q);
    bool isDominatedBy(const Subject& s) const;
    bool operator<(const Subject& r); // Crowded distance operator

    const unsigned& getRank() const;
    const double& getDistance() const;
    void setRank(const unsigned& newRank);
    void setDistance(const double& newDistance);

    int dominantsCount;
    std::list<Subject*> dominatedSubjects;
private:
    double distance;
    unsigned rank;
    Fenotype gen;
};

#endif // SUBJECT_H
