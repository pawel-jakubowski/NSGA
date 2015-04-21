#ifndef GENERATION_H
#define GENERATION_H

#include <Subject.h>
#include <vector>

typedef std::shared_ptr<Expression> ExpressionPtr;
typedef std::vector<std::vector<Subject>> Fronts;

class Generation
{
public:
    Generation(unsigned subjectsCount, ExpressionPtr newf1, ExpressionPtr newf2);
    Generation produceNextGeneration();
    unsigned size() const;
protected:
    ExpressionPtr f1;
    ExpressionPtr f2;
    std::vector<Subject> subjects;
    void selection(unsigned endSubjectsCount);
    Fronts nonDominatedSort();
};

#endif // GENERATION_H
