#include <unittest++/UnitTest++.h>
#include <Subject.h>
#include <FenotypeMock.h>
#include <memory>
#include <limits>

#include <iostream>

class SubjectTest
{
public:
    GoalFunctions f;
    Subject individual;

    SubjectTest()
        : f(2,5)
        , individual(f)
    {
    }
};

TEST_FIXTURE(SubjectTest, subjectCanCopy)
{
    Subject copy(individual);
}

TEST_FIXTURE(SubjectTest, childSubjectCreation)
{
    Subject parentA(f), parentB(f);
    Subject child(parentA, parentB);
}

TEST_FIXTURE(SubjectTest, setAndGetDistance)
{
    CHECK_CLOSE(0, individual.getDistance(), 0.01);
    individual.setDistance(1);
    CHECK_CLOSE(1, individual.getDistance(), 0.01);

    const double infinity = std::numeric_limits<double>::infinity();
    individual.setDistance(infinity);
    CHECK_CLOSE(infinity, individual.getDistance(), 0.01);
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

class SubjectDominationTest : public SubjectTest
{
public:
    std::vector<double> x;
    std::shared_ptr<Subject> A;
    std::shared_ptr<Subject> B;
    std::shared_ptr<Subject> C;
    std::shared_ptr<Subject> D;
    std::shared_ptr<Subject> E;
    std::unique_ptr<FenotypeMock> gen;

    SubjectDominationTest() : x{1,1,0,0,0}
    {
        f[0].parse("x1-x2");
        f[1].parse("x1+x2");
        std::vector<double> x1{1,0.5,0,1,-1};
        std::vector<double> x2{1,1.5,0,5,-5};
        std::vector<std::shared_ptr<Subject>> subjects(5);

        for (unsigned i = 0; i < x1.size(); ++i)
        {
            x[0] = x1[i];
            x[1] = x2[i];
            gen.reset(new FenotypeMock(x,f));
            subjects[i].reset(new Subject(*gen));
        }
        A = subjects[0];
        B = subjects[1];
        C = subjects[2];
        D = subjects[3];
        E = subjects[4];
    }
};

TEST_FIXTURE(SubjectDominationTest, properSubjectsCreation)
{
    CHECK(A.get() != NULL);
    CHECK(B.get() != NULL);
    CHECK(C.get() != NULL);
    CHECK(D.get() != NULL);
    CHECK(E.get() != NULL);

    CHECK_EQUAL(0, A->rateByF(0));
    CHECK_EQUAL(2, A->rateByF(1));

    CHECK_EQUAL(-1, B->rateByF(0));
    CHECK_EQUAL(2, B->rateByF(1));

    CHECK_EQUAL(0, C->rateByF(0));
    CHECK_EQUAL(0, C->rateByF(1));

    CHECK_EQUAL(-4, D->rateByF(0));
    CHECK_EQUAL(6, D->rateByF(1));

    CHECK_EQUAL(4, E->rateByF(0));
    CHECK_EQUAL(-6, E->rateByF(1));
}

TEST_FIXTURE(SubjectDominationTest, domination)
{
    CHECK(!A->isDominatedBy(*A));
    CHECK(A->isDominatedBy(*B));
    CHECK(A->isDominatedBy(*C));
    CHECK(!A->isDominatedBy(*D));
    CHECK(!A->isDominatedBy(*E));
}
