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

    GenerationMock(SubjectsContainer subjects, GoalFunctions& f)
        : Generation(subjects, f)
    {
    }

    GenerationMock(const Generation& other)
        : Generation(other)
    {
    }

    const SubjectsContainer& getSubjects()
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
    using Generation::reproduction;
};

#endif // GENERATIONMOCK_H
