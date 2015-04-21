#include <unittest++/UnitTest++.h>
#include <Subject.h>
#include <GenotypeMock.h>
#include <memory>
#include <limits>

#include <iostream>

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

class SubjectDominationTest : public SubjectTest
{
public:
    std::vector<double> x;
    std::shared_ptr<Subject> A;
    std::shared_ptr<Subject> B;
    std::shared_ptr<Subject> C;
    std::shared_ptr<Subject> D;
    std::shared_ptr<Subject> E;
    std::unique_ptr<GenotypeMock> gen;

    SubjectDominationTest() : x{1,1,0,0,0}
    {
        f1->parse("x1-x2");
        f2->parse("x1+x2");
        std::vector<double> x1{1,0.5,0,1,-1};
        std::vector<double> x2{1,1.5,0,5,-5};

        x[0] = x1[0];
        x[1] = x2[0];
        gen.reset(new GenotypeMock(x,f1,f2));
        A.reset(new Subject(*gen));

        x[0] = x1[1];
        x[1] = x2[1];
        gen.reset(new GenotypeMock(x,f1,f2));
        B.reset(new Subject(*gen));

        x[0] = x1[2];
        x[1] = x2[2];
        gen.reset(new GenotypeMock(x,f1,f2));
        C.reset(new Subject(*gen));

        x[0] = x1[3];
        x[1] = x2[3];
        gen.reset(new GenotypeMock(x,f1,f2));
        D.reset(new Subject(*gen));

        x[0] = x1[4];
        x[1] = x2[4];
        gen.reset(new GenotypeMock(x,f1,f2));
        E.reset(new Subject(*gen));
    }
};

TEST_FIXTURE(SubjectDominationTest, properSubjectsCreation)
{
    CHECK(A.get() != NULL);
    CHECK(B.get() != NULL);
    CHECK(C.get() != NULL);
    CHECK(D.get() != NULL);
    CHECK(E.get() != NULL);

    CHECK_EQUAL(0, A->rateByF1());
    CHECK_EQUAL(2, A->rateByF2());

    CHECK_EQUAL(-1, B->rateByF1());
    CHECK_EQUAL(2, B->rateByF2());

    CHECK_EQUAL(0, C->rateByF1());
    CHECK_EQUAL(0, C->rateByF2());

    CHECK_EQUAL(-4, D->rateByF1());
    CHECK_EQUAL(6, D->rateByF2());

    CHECK_EQUAL(4, E->rateByF1());
    CHECK_EQUAL(-6, E->rateByF2());
}

TEST_FIXTURE(SubjectDominationTest, domination)
{
    CHECK(!A->isDominatedBy(*A));
    CHECK(A->isDominatedBy(*B));
    CHECK(A->isDominatedBy(*C));
    CHECK(!A->isDominatedBy(*D));
    CHECK(!A->isDominatedBy(*E));
}
