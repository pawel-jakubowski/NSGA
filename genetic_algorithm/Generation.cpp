#include "Generation.h"
#include "CustomAssertion.h"

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

const Fronts& Generation::nonDominatedSort()
{
    fronts.clear();
    if(subjects.size() > 0)
    {
        fronts.resize(1);
        std::fill(dominatedSubjects.begin(), dominatedSubjects.end(), std::list<unsigned>());
        std::fill(howManyDominatesSubject.begin(), howManyDominatesSubject.end(), 0);

        createFirstFront();
        fillOtherFronts();

        if(fronts[fronts.size()-1].empty())
            fronts.pop_back();
    }
    return fronts;
}

void Generation::checkDominations(const unsigned& p, const unsigned& q)
{
    if(subjects[q].isDominatedBy(subjects[p]))
        dominatedSubjects[p].push_back(q);
    else if (subjects[p].isDominatedBy(subjects[q]))
        howManyDominatesSubject[p] += 1;
}

void Generation::addSubjectToFront(const unsigned& frontNumber, const unsigned& subjectIndex)
{
    subjects[subjectIndex].setRank(frontNumber + 1);
    fronts[frontNumber].push_back(subjects[subjectIndex]);
}

void Generation::createFirstFront()
{
    for(unsigned i = 0; i < subjects.size(); ++i)
    {
        for(unsigned j = 0; j < subjects.size(); ++j)
            checkDominations(i, j);

        if(howManyDominatesSubject[i] == 0)
            addSubjectToFront(0, i);
    }
}

void Generation::fillOtherFronts()
{
    for(unsigned n = 0; !fronts[n].empty(); ++n)
    {
        fronts.push_back(std::vector<Subject>());
        for(unsigned i = 0; i < fronts[n].size(); ++i)
        {
            for(auto& subjectIndex : dominatedSubjects[i])
            {
                howManyDominatesSubject[subjectIndex] -= 1;
                if (howManyDominatesSubject[subjectIndex] == 0)
                    addSubjectToFront(n+1, subjectIndex);
            }
        }
    }
}

void Generation::calculateCrowdingDistances()
{
    assert(fronts.size() != 0);

    const double infinity = std::numeric_limits<double>::infinity();
    double tmpDistance = 0;
    double f1Max = std::numeric_limits<double>::min();
    double f1Min = infinity;
    double f2Max = std::numeric_limits<double>::min();
    double f2Min = infinity;

    double tmpFValue = 0;
    for(auto& subject : subjects)
    {
        tmpFValue = subject.rateByF1();
        if (f1Max < tmpFValue)
            f1Max = tmpFValue;
        if (f1Min > tmpFValue)
            f1Min = tmpFValue;

        tmpFValue = subject.rateByF2();
        if (f2Max < tmpFValue)
            f2Max = tmpFValue;
        if (f2Min > tmpFValue)
            f2Min = tmpFValue;
    }

    for(auto& front : fronts)
    {
        std::sort(front.begin(), front.end(), compareByF1());
        front[0].setDistance(infinity);
        front[front.size()-1].setDistance(infinity);

        for(unsigned k = 1; k < front.size()-1; ++k)
        {
            tmpDistance = front[k].getDistance()+
                    (front[k+1].rateByF1()-front[k-1].rateByF1())/(f1Max-f1Min);
            front[k].setDistance(tmpDistance);
        }

        std::sort(front.begin(), front.end(), compareByF2());
        front[0].setDistance(infinity);
        front[front.size()-1].setDistance(infinity);

        for(unsigned k = 1; k < front.size()-1; ++k)
        {
            tmpDistance = front[k].getDistance()+
                    (front[k+1].rateByF2()-front[k-1].rateByF2())/(f2Max-f2Min);
            front[k].setDistance(tmpDistance);
        }
    }
}
