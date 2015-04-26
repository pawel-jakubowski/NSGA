#include <unittest++/UnitTest++.h>
#include <GenotypeMock.h>
#include <iostream>

class GenotypeTest
{
public:
    std::vector<double> x;
    GoalFunctions f;
    std::unique_ptr<GenotypeMock> gen;

    GenotypeTest()
        : x{1,2,3,4,5}
        , f(2,5)
    {
        f[0].parse("x1+x2+x3+x4+x5");
        f[1].parse("x1-x2-x3-x4-x5");
        gen.reset(new GenotypeMock(x, f));
    }
};

TEST_FIXTURE(GenotypeTest, getFenotype)
{
    std::vector<double> fenotype = gen->getFenotype();

    CHECK_EQUAL(1, fenotype[0]);
    CHECK_EQUAL(2, fenotype[1]);
    CHECK_EQUAL(3, fenotype[2]);
    CHECK_EQUAL(4, fenotype[3]);
    CHECK_EQUAL(5, fenotype[4]);
}

TEST_FIXTURE(GenotypeTest, genotypeCanCopy)
{
    Genotype copy(*gen);
}

TEST_FIXTURE(GenotypeTest, childGenotypeCreation)
{
    Genotype parentA(f), parentB(f);
    Genotype child(parentA, parentB);

    CHECK(!isnan(child.rateByF(0)));
    CHECK(!isnan(child.rateByF(1)));

    CHECK(!isinf(child.rateByF(0)));
    CHECK(!isinf(child.rateByF(1)));

}

class GenotypeWithFValuesTest : public GenotypeTest
{
public:
    const double f1Value;
    const double f2Value;
    GenotypeWithFValuesTest()
     : f1Value(x[0]+x[1]+x[2]+x[3]+x[4])
     , f2Value(x[0]-x[1]-x[2]-x[3]-x[4])
    {}
};

TEST_FIXTURE(GenotypeWithFValuesTest, initialExpressionsCorectness)
{
    CHECK_EQUAL(f1Value, gen->rateByF(0));
    CHECK_EQUAL(f2Value, gen->rateByF(1));
}

TEST_FIXTURE(GenotypeWithFValuesTest, genotypeIsConstantAfterReparse)
{
    f[0].parse("x1^2+x2^2+x3^2+x4^2+x5^2");
    f[1].parse("sqrt(x1-x2-x3-x4-x5)");
    CHECK_EQUAL(f1Value, gen->rateByF(0));
    CHECK_EQUAL(f2Value, gen->rateByF(1));
}

TEST_FIXTURE(GenotypeWithFValuesTest, genotypeIsConstantAfterChangingX)
{
    f[0].at("x1") = f[1].at("x5") = 20;
    CHECK_EQUAL(f1Value, gen->rateByF(0));
    CHECK_EQUAL(f2Value, gen->rateByF(1));
}
