#include <unittest++/UnitTest++.h>
#include <GenerationMock.h>
#include <GenotypeMock.h>

class GenerationTest
{
public:
    Expression f1, f2;
    unsigned generationSize;
    Generation generation;

    GenerationTest()
        : generationSize(50)
        , generation(generationSize, f1, f2) {}
};

TEST_FIXTURE(GenerationTest, generationCreation)
{
    CHECK_EQUAL(generationSize, generation.size());
}

TEST_FIXTURE(GenerationTest, produceNextGeneration)
{
    Generation newGeneration = generation.produceNextGeneration();
    CHECK_EQUAL(generationSize, newGeneration.size());
}

class GenerationSortingTest : public GenerationTest
{
public:
    std::vector<Subject> subjects;

    GenerationSortingTest() : GenerationTest()
    {
        f1.parse("x1-x2");
        f2.parse("x1+x2");

        std::vector<double> x{0,0,0,0,0};
        std::vector<double> x1 = {
            // Front 1
            0.5, 1, 0.5, 1, -1,
            //Front 2
            10, 9, 8.5,
            // Front 3
            15,
            // Front 4
            40
        };
        std::vector<double> x2 = {
            // Front 1
            7.5, 0.5, 1.5, 5, -5,
            //Front 2
            -1, 2, 1,
            // Front 3
            3,
            // Front 4
            0
        };

        subjects.reserve(x1.size());
        std::unique_ptr<GenotypeMock> gen;
        for(unsigned i = 0; i < x1.size(); ++i)
        {
            x[0] = x1[i];
            x[1] = x2[i];
            gen.reset(new GenotypeMock(x,f1,f2));
            subjects.push_back(Subject(*gen));
        }
    }
};

TEST_FIXTURE(GenerationSortingTest, nonDominatedSortForEmptyGeneration)
{
    generationSize = 0;
    GenerationMock generation = GenerationMock(generationSize, f1, f2);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
    CHECK_EQUAL(0, fronts.size());
}

TEST_FIXTURE(GenerationSortingTest, nonDominatedSortForGenerationWithOneSubject)
{
    generationSize = 1;
    GenerationMock generation = GenerationMock(generationSize, f1, f2);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
    CHECK_EQUAL(1, fronts.size());
}

TEST_FIXTURE(GenerationSortingTest, nonDominatedSortSimpleCase)
{
    GenerationMock generation = GenerationMock(subjects, f1, f2);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(subjects.size(), generation.size());
    CHECK_EQUAL(4, fronts.size());
    CHECK_EQUAL(5, fronts[0].size());
    CHECK_EQUAL(3, fronts[1].size());
    CHECK_EQUAL(1, fronts[2].size());
    CHECK_EQUAL(1, fronts[3].size());
}

class GenerationCrowdingDistance : public GenerationSortingTest
{
public:
    GenerationMock generation;
    Fronts fronts;

    GenerationCrowdingDistance()
        : GenerationSortingTest(), generation(subjects, f1, f2)
    {
        fronts = generation.nonDominatedSort();
    }
};

TEST_FIXTURE(GenerationCrowdingDistance, initialFronts)
{
    CHECK_EQUAL(4, fronts.size());
    CHECK_EQUAL(5, fronts[0].size());
    CHECK_EQUAL(3, fronts[1].size());
    CHECK_EQUAL(1, fronts[2].size());
    CHECK_EQUAL(1, fronts[3].size());
}
