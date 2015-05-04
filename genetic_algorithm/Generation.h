#ifndef GENERATION_H
#define GENERATION_H

#include <Subject.h>
#include <vector>

typedef std::vector<Subject*> Front;
typedef std::vector<Front> Fronts;

class Generation
{
    static const int matingSize = 30;
    static const int tournamentSize = 5;
public:
    Generation(unsigned subjectsCount, GoalFunctions& newf);
    Generation(std::vector<Subject> newSubjects, GoalFunctions &newf);
    Generation produceNextGeneration();
    unsigned size() const;
    void addSubject(const Subject &subject);
    std::vector<Subject> reproduction (unsigned subjectsCount);
protected:
    GoalFunctions* f;
    std::vector<double> fMax;
    std::vector<double> fMin;
    std::vector<Subject> subjects;

    Fronts fronts;

    Generation fitFrontsToNextGeneration(const unsigned subjectsCount);

    const Fronts& nonDominatedSort();
    void updateMinMax(const Subject &subject, const unsigned &goalFunctionIndex);
    void addSubjectToFront(const unsigned& frontNumber, Subject &subject);
    void createFirstFront();
    void fillOtherFronts();

    void calculateCrowdingDistances();
    void calculateDistancesForFront(Front& front);
    double calculateDistance(unsigned k, Front& front, const unsigned& goalFunctionIndex);


    std::vector<Subject> createOffspringsFromPool(unsigned subjectsCount, std::vector<Subject*> matingPool);
    std::vector<Subject *> createMatingPool();
    Subject * findBestContestant(std::vector<Subject*> tournamentPool);
    std::vector<Subject *> createTournamentPool();
};

#endif // GENERATION_H
