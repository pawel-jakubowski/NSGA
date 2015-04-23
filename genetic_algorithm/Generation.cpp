#include "Generation.h"
#include <iostream>

Generation::Generation(unsigned subjectsCount, Expression& newf1, Expression& newf2)
    : f1(&newf1)
    , f2(&newf2)
    , subjects(subjectsCount, Subject(*f1,*f2))
    , dominatedSubjects(subjectsCount)
    , howManyDominatesSubject(subjectsCount, 0)
{
}

Generation Generation::produceNextGeneration()
{
    return Generation(subjects.size(), *f1, *f2);
}

unsigned Generation::size() const
{
    return subjects.size();
}

void Generation::selection(unsigned)
{
}

Fronts Generation::nonDominatedSort()
{
    Fronts F;
    if(subjects.size() > 0)
    {
        F.resize(1);
        std::fill(dominatedSubjects.begin(), dominatedSubjects.end(), std::list<unsigned>());
        std::fill(howManyDominatesSubject.begin(), howManyDominatesSubject.end(), 0);

        fillFirstFront(F);
        fillOtherFronts(F);

        if(F[F.size()-1].empty())
            F.pop_back();
    }
    return F;
}

void Generation::checkDominations(const unsigned& p, const unsigned& q)
{
    if(subjects[q].isDominatedBy(subjects[p]))
        dominatedSubjects[p].push_back(q);
    else if (subjects[p].isDominatedBy(subjects[q]))
        howManyDominatesSubject[p] += 1;
}

void Generation::addSubjectToFront(Fronts& F, const unsigned& frontNumber, const unsigned& subjectIndex)
{
    unsigned rank = (frontNumber != 0) ? frontNumber : 1;
    F[frontNumber].push_back(subjects[subjectIndex]);
    subjects[subjectIndex].setRank(rank);
}

void Generation::fillFirstFront(Fronts& F)
{
    for(unsigned i = 0; i < subjects.size(); ++i)
    {
        for(unsigned j = 0; j < subjects.size(); ++j)
            checkDominations(i, j);

        if(howManyDominatesSubject[i] == 0)
            addSubjectToFront(F, 0, i);
    }
}

void Generation::fillOtherFronts(Fronts& F)
{
    for(unsigned n = 0; !F[n].empty(); ++n)
    {
        F.push_back(std::vector<Subject>());
        for(unsigned i = 0; i < F[n].size(); ++i)
        {
            for(auto& subjectIndex : dominatedSubjects[i])
            {
                howManyDominatesSubject[subjectIndex] -= 1;
                if (howManyDominatesSubject[subjectIndex] == 0)
                    addSubjectToFront(F, n+1, subjectIndex);
            }
        }
    }
}
