#include <unittest++/UnitTest++.h>
#include <Subject.h>
#include <limits>

class SubjectTest
{
public:
    ExpressionPtr f1, f2;
    Subject individual;

    SubjectTest()
        : f1(new Expression(5))
        , f2(new Expression(5))
        , individual(f1, f2)
    {
    }
};

TEST_FIXTURE(SubjectTest, subjectCanCopy)
{
    Subject copy(individual);
}

TEST_FIXTURE(SubjectTest, childSubjectCreation)
{
    Subject parentA(f1, f2), parentB(f1, f2);
    Subject child(parentA, parentB);
}

TEST_FIXTURE(SubjectTest, setAndGetRank)
{
    CHECK_EQUAL(0, individual.getRank());
    individual.setRank(1);
    CHECK_EQUAL(1, individual.getRank());
    individual.setRank(126);
    CHECK_EQUAL(126, individual.getRank());
}

TEST_FIXTURE(SubjectTest, setAndGetDistance)
{
    CHECK_EQUAL(0, individual.getDistance());
    individual.setDistance(1);
    CHECK_EQUAL(1, individual.getDistance());

    const unsigned infinity = std::numeric_limits<unsigned>::max();
    individual.setDistance(infinity);
    CHECK_EQUAL(infinity, individual.getDistance());
}

class SubjectOperatorsTest : public SubjectTest
{
public:
    const unsigned infinity = std::numeric_limits<unsigned>::max();
    Subject A;
    Subject B;
    Subject C;

    SubjectOperatorsTest()
        : A(individual)
        , B(individual)
        , C(individual)
    {
        A.setRank(5);
        B.setRank(7);
        B.setDistance(10);
        C.setRank(7);
        C.setDistance(infinity);

    }
};

TEST_FIXTURE(SubjectOperatorsTest, crowdedComparisonOperator)
{
    CHECK(A < B);
    CHECK(C < B);
    CHECK(A < C);
}
