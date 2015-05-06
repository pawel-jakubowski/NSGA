#ifndef GENERATION_H
#define GENERATION_H

#include <Front.h>
#include <vector>

typedef std::vector<Front> Fronts;

class Generation
{
    static const int matingSize = 30;
    static const int tournamentSize = 5;
public:
    Generation(unsigned subjectsCount, GoalFunctions& newf);
    Generation(SubjectsContainer newSubjects, GoalFunctions &newf);
    Generation produceNextGeneration();
    unsigned size() const;
    void addSubject(std::shared_ptr<Subject> subject);
    std::vector<std::vector<double>> getFirstFront();
    void addSubjectToFront(const unsigned &frontNumber, SubjectPtr subject);
protected:
    GoalFunctions* f;
    std::vector<double> fMax;
    std::vector<double> fMin;
    SubjectsContainer subjects;

    Fronts fronts;

    Generation fitFrontsToNextGeneration(const unsigned subjectsCount);

    const Fronts& nonDominatedSort();
    void updateMinMax(const Subject &subject, const unsigned &goalFunctionIndex);
    void createFirstFront();
    void fillOtherFronts();

    void calculateCrowdingDistances();

    SubjectsContainer reproduction (unsigned subjectsCount);
    SubjectsContainer createOffspringsFromPool(unsigned subjectsCount, SubjectsContainer matingPool);
    SubjectsContainer createMatingPool();
    std::shared_ptr<Subject> findBestContestant(SubjectsContainer tournamentPool);
    SubjectsContainer createTournamentPool();
};

#endif // GENERATION_H
