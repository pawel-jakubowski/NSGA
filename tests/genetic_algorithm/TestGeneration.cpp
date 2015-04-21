#include <unittest++/UnitTest++.h>
#include <GenerationMock.h>

class GenerationTest
{
public:
    ExpressionPtr f1, f2;
    unsigned generationSize;
    Generation generation;

    GenerationTest()
        : f1(new Expression())
        , f2(new Expression())
        , generationSize(50)
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
    GenerationMock generation;

    GenerationSortingTest() : GenerationTest(), generation(generationSize, f1, f2)
    {
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
        subjects.push_back(Subject(f1,f2));
    }
};

TEST_FIXTURE(GenerationSortingTest, nonDominatedSortForEmptyGeneration)
{
    generationSize = 0;
    generation = GenerationMock(generationSize, f1, f2);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
    CHECK_EQUAL(0, fronts.size());
}

TEST_FIXTURE(GenerationSortingTest, nonDominatedSortForGenerationWithOneSubject)
{
    generationSize = 1;
    generation = GenerationMock(generationSize, f1, f2);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
    CHECK_EQUAL(1, fronts.size());
}

TEST_FIXTURE(GenerationSortingTest, nonDominatedSortSimpleCase)
{
    generationSize = 10;
    generation = GenerationMock(generationSize, f1, f2);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
}
