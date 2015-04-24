#ifndef GENERATION_H
#define GENERATION_H

#include <Subject.h>
#include <vector>

typedef std::vector<std::vector<Subject>> Fronts;

class Generation
{
public:
    Generation(unsigned subjectsCount, Expression& newf1, Expression& newf2);
    Generation produceNextGeneration();
    unsigned size() const;
protected:
    Expression* f1;
    Expression* f2;
    std::vector<Subject> subjects;

    std::vector<std::list<unsigned>> dominatedSubjects;
    std::vector<int> howManyDominatesSubject;
    Fronts fronts;

    void selection(unsigned endSubjectsCount);

    const Fronts& nonDominatedSort();
    void checkDominations(const unsigned& p, const unsigned& q);
    void addSubjectToFront(const unsigned& frontNumber, const unsigned& subjectIndex);
    void createFirstFront();
    void fillOtherFronts();
};

#endif // GENERATION_H
