#include "Generation.h"
#include "CustomAssertion.h"

Generation::Generation(unsigned subjectsCount, GoalFunctions& newf)
    : f(&newf)
    , fMax(newf.size(), std::numeric_limits<double>::min())
    , fMin(newf.size(), std::numeric_limits<double>::infinity())
    , subjects(subjectsCount, Subject(*f))
    , dominatedSubjects(subjectsCount)
    , howManyDominatesSubject(subjectsCount, 0)
{
}

Generation::Generation(std::vector<Subject> newSubjects, GoalFunctions& newf)
    : f(&newf)
    , fMax(newf.size(), std::numeric_limits<double>::min())
    , fMin(newf.size(), std::numeric_limits<double>::infinity())
    , subjects(newSubjects)
    , dominatedSubjects(newSubjects.size())
    , howManyDominatesSubject(newSubjects.size(), 0)
{
}

bool compareSubjectPtrs(const Subject* a, const Subject* b)
{
    return a < b;
}

Generation Generation::produceNextGeneration()
{
    const unsigned subjectsCount = subjects.size();
//    std::vector<Subjects> offsprings = createOffsprings();
//    subjects.insert(subjects.end(), offsprings.begin(), offsprings.end());
    nonDominatedSort();
    assert(fronts.size() > 0);

    Generation nextGeneration(0, *f);
    unsigned i = 0;
    for(i = 0; i < fronts.size(); ++i)
    {
        if((nextGeneration.size() + fronts[i].size()) > subjectsCount)
            break;

        calculateDistancesForFront(fronts[i]);
        for(auto& subject : fronts[i])
            nextGeneration.addSubject(*subject);
    }
    std::sort(fronts[i].begin(), fronts[i].end(), compareSubjectPtrs);
    for(unsigned j = 0; nextGeneration.size() < subjectsCount; ++j)
        nextGeneration.addSubject(*(fronts[i][j]));
    return nextGeneration;
}

void Generation::addSubject(const Subject& subject)
{
    subjects.emplace_back(subject);
    howManyDominatesSubject.emplace_back(0);
    dominatedSubjects.emplace_back(std::list<unsigned>());
}

unsigned Generation::size() const
{
    return subjects.size();
}

void Generation::selection(unsigned)
{
}

//void Generation::pickParent(unsigned)
//{
//    return parent;
//}

void Generation::reproduction(unsigned subjectsCount)
{
    do
    {
        Subject parent1=subjects[rand()%subjectsCount];
    }while(std::find(usedParents.begin(), usedParents.end(), parent1) != usedParents.end());
    do
    {
        Subject parent2=subjects[rand()%subjectsCount];
    }while(parent1 == parent2 && (std::find(usedParents.begin(), usedParents.end(), parent2) != usedParents.end()));

    offspring.push(Subject(parent1,parent2));
    usedParents.push(parent1);
    usedParents.push(parent2);
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
        dominatedSubjects[p].emplace_back(q);
    else if (subjects[p].isDominatedBy(subjects[q]))
        howManyDominatesSubject[p] += 1;
}

void Generation::addSubjectToFront(const unsigned& frontNumber, const unsigned& subjectIndex)
{
    subjects[subjectIndex].setRank(frontNumber + 1);
    fronts[frontNumber].emplace_back(&subjects[subjectIndex]);
}

void Generation::updateMinMax(const Subject& subject, const unsigned& goalFunctionIndex)
{
    double tmpFValue = 0;
    tmpFValue = subject.rateByF(goalFunctionIndex);
    if (fMax[goalFunctionIndex] < tmpFValue)
        fMax[goalFunctionIndex] = tmpFValue;
    if (fMin[goalFunctionIndex] > tmpFValue)
        fMin[goalFunctionIndex] = tmpFValue;
}

void Generation::createFirstFront()
{
    for(unsigned i = 0; i < subjects.size(); ++i)
    {
        for(unsigned j = 0; j < subjects.size(); ++j)
            checkDominations(i, j);

        if(howManyDominatesSubject[i] == 0)
            addSubjectToFront(0, i);

        for(unsigned m = 0; m < f->size(); ++m)
            updateMinMax(subjects[i], m);
    }
}

void Generation::fillOtherFronts()
{
    for(unsigned n = 0; !fronts[n].empty(); ++n)
    {
        fronts.push_back(std::vector<Subject*>());
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

    for(auto& front : fronts)
        calculateDistancesForFront(front);
}

void Generation::calculateDistancesForFront(Front& front)
{
    const double infinity = std::numeric_limits<double>::infinity();

    for(unsigned m = 0; m < f->size(); ++m)
    {
        std::sort(front.begin(), front.end(), compareByF(m));
        front[0]->setDistance(infinity);
        front[front.size()-1]->setDistance(infinity);

        for(unsigned k = 1; k < front.size()-1; ++k)
            front[k]->setDistance(calculateDistance(k, front, m));
    }
}

double Generation::calculateDistance(unsigned subjectIndex, Front& front, const unsigned& goalFunctionIndex)
{
    return front[subjectIndex]->getDistance()+
            (
                front[subjectIndex+1]->rateByF(goalFunctionIndex)-
                front[subjectIndex-1]->rateByF(goalFunctionIndex)
            )/
            (fMax[goalFunctionIndex]-fMin[goalFunctionIndex]);
}
