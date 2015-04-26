#include <GoalFunctions.h>
#include <CustomAssertion.h>

GoalFunctions::GoalFunctions(const unsigned &numberOfGoalFunctions, const unsigned &numberOfVariables)
    : goalFunctions(numberOfGoalFunctions, Expression(numberOfVariables))
{
}

GoalFunctions::GoalFunctions(std::initializer_list<Expression> f)
    : goalFunctions(f)
{
}

Expression &GoalFunctions::operator[](const unsigned &id)
{
    return at(id);
}

Expression &GoalFunctions::at(const unsigned &id)
{
    assert(id < goalFunctions.size());
    return goalFunctions[id];
}

unsigned GoalFunctions::size() const
{
    return goalFunctions.size();
}
