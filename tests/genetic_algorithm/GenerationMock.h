#ifndef GENERATIONMOCK_H
#define GENERATIONMOCK_H

#include <Generation.h>

class GenerationMock : public Generation
{
public:
    GenerationMock(unsigned& subjectsCount, GoalFunctions& f)
        : Generation(subjectsCount, f)
    {
    }

    GenerationMock(std::vector<Subject> subjects, GoalFunctions& f)
        : Generation(subjects, f)
    {
    }

    const std::vector<Subject>& getSubjects()
    {
        return subjects;
    }

    const Fronts& getFronts()
    {
        return fronts;
    }

    // Change function visibility for testing purposes
    using Generation::nonDominatedSort;
    using Generation::calculateCrowdingDistances;
};

#endif // GENERATIONMOCK_H
