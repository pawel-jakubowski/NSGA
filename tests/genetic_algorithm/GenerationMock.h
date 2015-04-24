#ifndef GENERATIONMOCK_H
#define GENERATIONMOCK_H

#include <Generation.h>

class GenerationMock : public Generation
{
public:
    GenerationMock(unsigned& subjectsCount, Expression& newf1, Expression& newf2)
        : Generation(subjectsCount, newf1, newf2)
    {
    }

    GenerationMock(std::vector<Subject> newSubjects, Expression& newf1, Expression& newf2)
        : Generation(newSubjects.size(), newf1, newf2)
    {
        subjects = newSubjects;
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
