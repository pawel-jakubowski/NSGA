#ifndef GENERATION_H
#define GENERATION_H

#include <Subject.h>
#include <vector>

typedef std::vector<Subject*> Front;
typedef std::vector<Front> Fronts;

class Generation
{
public:
    Generation(unsigned subjectsCount, GoalFunctions& newf);
    Generation(std::vector<Subject> newSubjects, GoalFunctions &newf);
    Generation produceNextGeneration();
    unsigned size() const;
    void addSubject(const Subject &subject);
protected:
    GoalFunctions* f;
    std::vector<double> fMax;
    std::vector<double> fMin;
    std::vector<Subject> subjects;

    std::vector<std::list<unsigned>> dominatedSubjects;
    std::vector<int> howManyDominatesSubject;
    Fronts fronts;

    void selection(unsigned endSubjectsCount);

    const Fronts& nonDominatedSort();
    void checkDominations(const unsigned& p, const unsigned& q);
    void updateMinMax(const Subject &subject, const unsigned &goalFunctionIndex);
    void addSubjectToFront(const unsigned& frontNumber, const unsigned& subjectIndex);
    void createFirstFront();
    void fillOtherFronts();

    void calculateCrowdingDistances();
    void calculateDistancesForFront(Front& front);
    double calculateDistance(unsigned k, Front& front, const unsigned& goalFunctionIndex);
};

#endif // GENERATION_H
