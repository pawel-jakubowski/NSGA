#include "Generation.h"
#include "CustomAssertion.h"
#include <iostream>

Generation::Generation(unsigned subjectsCount, GoalFunctions& newf)
    : f(&newf)
    , fMax(newf.size(), std::numeric_limits<double>::min())
    , fMin(newf.size(), std::numeric_limits<double>::infinity())
{
    for(unsigned i = 0; i < subjectsCount; ++i)
        subjects.push_back(Subject(*f));
}

Generation::Generation(std::vector<Subject> newSubjects, GoalFunctions& newf)
    : f(&newf)
    , fMax(newf.size(), std::numeric_limits<double>::min())
    , fMin(newf.size(), std::numeric_limits<double>::infinity())
    , subjects(newSubjects)
{
}

Generation Generation::produceNextGeneration()
{
    const unsigned subjectsCount = subjects.size();
    std::vector<Subject> offsprings = reproduction(subjects.size());
    subjects.insert(subjects.end(), offsprings.begin(), offsprings.end());
    assert(subjects.size() == 2*subjectsCount);
    nonDominatedSort();
    assert(fronts.size() > 0);

    const Generation& nextGeneration = fitFrontsToNextGeneration(subjectsCount);
    subjects.resize(subjectsCount, Subject(*f));

    for(auto& subject : nextGeneration.subjects)
        if(subject.getRank() == 1)
            std::cout << subject.rateByF(0) << " " << subject.rateByF(1) << std::endl;

    return nextGeneration;
}

Generation Generation::fitFrontsToNextGeneration(const unsigned subjectsCount)
{
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

    std::sort(fronts[i].begin(), fronts[i].end(),
        [](const Subject* a, const Subject* b){ return a < b; });
    for(unsigned j = 0; nextGeneration.size() < subjectsCount; ++j)
        nextGeneration.addSubject(*(fronts[i][j]));
    assert(nextGeneration.size() == subjectsCount);

    return nextGeneration;
}

void Generation::addSubject(const Subject& subject)
{
    subjects.emplace_back(subject);
}

unsigned Generation::size() const
{
    return subjects.size();
}

std::vector<Subject> Generation::reproduction(unsigned subjectsCount)
{
    std::vector<Subject*> matingPool = createMatingPool();
    return createOffspringsFromPool(subjectsCount, matingPool);
}

std::vector<Subject*> Generation::createMatingPool()
{
    std::vector<Subject*> matingPool;

    while(matingPool.size() < matingSize)
    {
        std::vector<Subject*> tournamentPool = createTournamentPool();
        Subject* bestContestant = findBestContestant(tournamentPool);
        matingPool.push_back(bestContestant);
    }
    return matingPool;
}

std::vector<Subject *> Generation::createTournamentPool()
{
    RandomGenerator generator;
    std::vector<Subject*> tournamentPool;
    std::vector<bool> usedSubjects(subjects.size(),false);
    int contestant;

    while(tournamentPool.size() < tournamentSize)
    {
        contestant = generator.rand(0,subjects.size());
        if(!usedSubjects[contestant])
        {
            tournamentPool.push_back(&subjects[contestant]);
            usedSubjects[contestant] = true;
        }
    }

    return tournamentPool;
}

Subject * Generation::findBestContestant(std::vector<Subject*> tournamentPool)
{
    Subject* bestContestant = tournamentPool[0];

    for(auto& subject:tournamentPool)
    {
        if(*subject < *bestContestant)
        {
            bestContestant = subject;
        }
    }

    return bestContestant;
}

std::vector<Subject> Generation::createOffspringsFromPool(unsigned subjectsCount, std::vector<Subject*> matingPool)
{
    RandomGenerator generator;

    unsigned parentA;
    unsigned parentB;
    std::vector<Subject> offsprings;
    while(offsprings.size() < subjectsCount)
    {
        parentA = parentB = generator.rand(0,matingPool.size());
        while(parentA == parentB)
            parentB = generator.rand(0,matingPool.size());
        offsprings.push_back(Subject(*matingPool[parentA],*matingPool[parentB]));
    }

    return offsprings;
}

const Fronts& Generation::nonDominatedSort()
{
    fronts.clear();
    if(subjects.size() > 0)
    {
        fronts.resize(1);
        for(auto& subject : subjects)
        {
            subject.dominatedSubjects.clear();
            subject.dominantsCount = 0;
        }

        createFirstFront();
        fillOtherFronts();

        if(fronts[fronts.size()-1].empty())
            fronts.pop_back();
    }
    return fronts;
}

void Generation::addSubjectToFront(const unsigned& frontNumber, Subject& subject)
{
    subject.setRank(frontNumber + 1);
    fronts[frontNumber].emplace_back(&subject);
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
    for(auto& p : subjects)
    {
        for(auto& q : subjects)
            p.checkDomination(q);

        if(p.dominantsCount == 0)
            addSubjectToFront(0, p);

        for(unsigned m = 0; m < f->size(); ++m)
            updateMinMax(p, m);
    }
}

void Generation::fillOtherFronts()
{
    for(unsigned n = 0; !fronts[n].empty(); ++n)
    {
        fronts.push_back(std::vector<Subject*>());
        for(auto& p : fronts[n])
        {
            for(auto& q : p->dominatedSubjects)
            {
                q->dominantsCount -= 1;
                assert(q->dominantsCount >= 0);
                if (q->dominantsCount == 0)
                    addSubjectToFront(n+1, *q);
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
        std::sort(front.begin(), front.end(),
            [m](const Subject* a, const Subject* b){ return a->rateByF(m) < b->rateByF(m); });
        front[0]->setDistance(infinity);
        front[front.size()-1]->setDistance(infinity);

        for(unsigned k = 1; k < front.size()-1; ++k)
            front[k]->setDistance(calculateDistance(k, front, m));
    }
}

double Generation::calculateDistance(unsigned subjectIndex, Front& front,
        const unsigned& goalFunctionIndex)
{
    return front[subjectIndex]->getDistance()+
            (
                front[subjectIndex+1]->rateByF(goalFunctionIndex)-
                front[subjectIndex-1]->rateByF(goalFunctionIndex)
            )/
            (fMax[goalFunctionIndex]-fMin[goalFunctionIndex]);
}
