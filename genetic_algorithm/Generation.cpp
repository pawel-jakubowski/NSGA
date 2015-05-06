#include "Generation.h"
#include "CustomAssertion.h"

Generation::Generation(unsigned subjectsCount, GoalFunctions& newf)
    : f(&newf)
    , fMax(newf.size(), std::numeric_limits<double>::min())
    , fMin(newf.size(), std::numeric_limits<double>::infinity())
{
    for(unsigned i = 0; i < subjectsCount; ++i)
        subjects.push_back(std::make_shared<Subject>(*f));
}

Generation::Generation(SubjectsContainer newSubjects, GoalFunctions& newf)
    : f(&newf)
    , fMax(newf.size(), std::numeric_limits<double>::min())
    , fMin(newf.size(), std::numeric_limits<double>::infinity())
    , subjects(newSubjects)
{
}

Generation Generation::produceNextGeneration()
{
    const unsigned subjectsCount = subjects.size();
    SubjectsContainer offsprings = reproduction(subjects.size());
    subjects.insert(subjects.end(), offsprings.begin(), offsprings.end());
    assert(subjects.size() == 2*subjectsCount);
    nonDominatedSort();
    assert(fronts.size() > 0);

    const Generation& nextGeneration = fitFrontsToNextGeneration(subjectsCount);
    subjects.resize(subjectsCount);

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

        fronts[i].calculateDistances(fMin, fMax);
        for(auto& subject : fronts[i])
            nextGeneration.addSubject(subject);
    }
    std::sort(fronts[i].begin(), fronts[i].end(),
              [](const SubjectPtr a, const SubjectPtr b){ return a < b; });
    for(unsigned j = 0; nextGeneration.size() < subjectsCount; ++j)
        nextGeneration.addSubject(fronts[i][j]);
    assert(nextGeneration.size() == subjectsCount);
    nextGeneration.nonDominatedSort();

    return nextGeneration;
}

void Generation::addSubject(std::shared_ptr<Subject> subject)
{
    subjects.emplace_back(subject);
}

unsigned Generation::size() const
{
    return subjects.size();
}

SubjectsContainer Generation::reproduction(unsigned subjectsCount)
{
    SubjectsContainer matingPool = createMatingPool();
    return createOffspringsFromPool(subjectsCount, matingPool);
}

std::vector<std::vector<double>> Generation::getFirstFront()
{
    assert(fronts.size() > 0);
    std::vector<std::vector<double>> firstFront(f->size(), std::vector<double>(fronts[0].size()));
    for(unsigned i = 0; i < fronts[0].size(); ++i)
        for(unsigned j = 0; j < firstFront.size(); ++j)
            firstFront[j][i] = fronts[0][i]->rateByF(j);
    return firstFront;
}

SubjectsContainer Generation::createMatingPool()
{
    SubjectsContainer matingPool;

    while(matingPool.size() < matingSize)
    {
        SubjectsContainer tournamentPool = createTournamentPool();
        std::shared_ptr<Subject> bestContestant = findBestContestant(tournamentPool);
        matingPool.emplace_back(bestContestant);
    }
    return matingPool;
}

SubjectsContainer Generation::createTournamentPool()
{
    RandomGenerator generator;
    SubjectsContainer tournamentPool;
    std::vector<bool> usedSubjects(subjects.size(),false);
    int contestant;

    while(tournamentPool.size() < tournamentSize)
    {
        contestant = generator.rand(0,subjects.size());
        if(!usedSubjects[contestant])
        {
            tournamentPool.emplace_back(subjects[contestant]);
            usedSubjects[contestant] = true;
        }
    }

    return tournamentPool;
}

std::shared_ptr<Subject> Generation::findBestContestant(SubjectsContainer tournamentPool)
{
    std::shared_ptr<Subject> bestContestant = tournamentPool[0];

    for(auto& subject:tournamentPool)
    {
        if(*subject < *bestContestant)
        {
            bestContestant = subject;
        }
    }

    return bestContestant;
}

SubjectsContainer Generation::createOffspringsFromPool(unsigned subjectsCount, SubjectsContainer matingPool)
{
    RandomGenerator generator;

    unsigned parentA;
    unsigned parentB;
    SubjectsContainer offsprings;
    while(offsprings.size() < subjectsCount)
    {
        parentA = parentB = generator.rand(0,matingPool.size());
        while(parentA == parentB)
            parentB = generator.rand(0,matingPool.size());
        offsprings.push_back(std::make_shared<Subject>(*matingPool[parentA],*matingPool[parentB]));
    }

    return offsprings;
}

const Fronts& Generation::nonDominatedSort()
{
    fronts.clear();
    if(subjects.size() > 0)
    {
        fronts.resize(1, Front(*f));
        for(auto& subject : subjects)
        {
            subject->dominatedSubjects.clear();
            subject->dominantsCount = 0;
        }

        createFirstFront();
        fillOtherFronts();

        if(fronts[fronts.size()-1].empty())
            fronts.pop_back();
    }
    return fronts;
}

void Generation::addSubjectToFront(const unsigned& frontNumber, SubjectPtr subject)
{
    subject->setRank(frontNumber + 1);
    fronts[frontNumber].add(subject);
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
            p->checkDomination(q);

        if(p->dominantsCount == 0)
            addSubjectToFront(0, p);

        for(unsigned m = 0; m < f->size(); ++m)
            updateMinMax(*p, m);
    }
}

void Generation::fillOtherFronts()
{
    for(unsigned n = 0; !fronts[n].empty(); ++n)
    {
        fronts.push_back(Front(*f));
        for(auto& p : fronts[n])
        {
            for(auto& q : p->dominatedSubjects)
            {
                q->dominantsCount -= 1;
                assert(q->dominantsCount >= 0);
                if (q->dominantsCount == 0)
                    addSubjectToFront(n+1, q);
            }
        }
    }
}

void Generation::calculateCrowdingDistances()
{
    assert(fronts.size() != 0);

    for(auto& front : fronts)
        front.calculateDistances(fMin,fMax);
}
