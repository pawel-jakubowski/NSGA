#ifndef GOALFUNCTIONS_H
#define GOALFUNCTIONS_H

#include <Expression.h>

class GoalFunctions : public Expression
{
public:
    GoalFunctions(const unsigned& numberOfGoalFunctions, const unsigned& numberOfVariables = 5);
    GoalFunctions(std::initializer_list<Expression> f);

    Expression& operator[](const unsigned& id);
    Expression &at(const unsigned& id);
    unsigned size() const;
private:
    std::vector<Expression> goalFunctions;
};

#endif // GOALFUNCTIONS_H
