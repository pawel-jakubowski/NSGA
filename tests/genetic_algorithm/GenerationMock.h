#ifndef GENERATIONMOCK_H
#define GENERATIONMOCK_H

#include <Generation.h>

class GenerationMock : public Generation
{
public:
    GenerationMock(unsigned subjectsCount, ExpressionPtr newf1, ExpressionPtr newf2)
        : Generation(subjectsCount, newf1, newf2)
    {
    }

    // Change function visibility for testing purposes
    using Generation::nonDominatedSort;
};

#endif // GENERATIONMOCK_H
