#include <unittest++/UnitTest++.h>
#include <GenerationMock.h>
#include <FenotypeMock.h>
#include <CustomAssertion.h>

class GenerationTest
{
public:
    GoalFunctions f;
    unsigned generationSize;
    Generation generation;

    GenerationTest()
        : f(2,5)
        , generationSize(50)
        , generation(generationSize, f)
    {
    }
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

class GenerationWithSubjects : public GenerationTest
{
public:
    std::vector<Subject> subjects;
    std::vector<double> x1;
    std::vector<double> x2;

    GenerationWithSubjects() : GenerationTest()
    {
        f[0].parse("x1-x2");
        f[1].parse("x1+x2");

        std::vector<double> x{0,0};
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
        std::unique_ptr<FenotypeMock> gen;
        for(unsigned i = 0; i < x1.size(); ++i)
        {
            x[0] = x1[i];
            x[1] = x2[i];
            gen.reset(new FenotypeMock(x,f));
            subjects.emplace_back(*gen);
        }
    }
};

TEST_FIXTURE(GenerationWithSubjects, nonDominatedSortForEmptyGeneration)
{
    generationSize = 0;
    GenerationMock generation = GenerationMock(generationSize, f);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
    CHECK_EQUAL(0, fronts.size());
}

TEST_FIXTURE(GenerationWithSubjects, nonDominatedSortForGenerationWithOneSubject)
{
    generationSize = 1;
    GenerationMock generation = GenerationMock(generationSize, f);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(generationSize, generation.size());
    CHECK_EQUAL(1, fronts.size());
}

TEST_FIXTURE(GenerationWithSubjects, nonDominatedSortSimpleCase)
{
    GenerationMock generation = GenerationMock(subjects, f);
    Fronts fronts = generation.nonDominatedSort();
    CHECK_EQUAL(subjects.size(), generation.size());
    CHECK_EQUAL(4, fronts.size());
    CHECK_EQUAL(5, fronts[0].size());
    CHECK_EQUAL(3, fronts[1].size());
    CHECK_EQUAL(1, fronts[2].size());
    CHECK_EQUAL(1, fronts[3].size());
}

TEST_FIXTURE(GenerationWithSubjects, distanceCalculationWithNoFronts)
{
    GenerationMock generation = GenerationMock(generationSize, f);

    CHECK_ASSERT(generation.calculateCrowdingDistances());
}

TEST_FIXTURE(GenerationWithSubjects, reproduction)
{
    std::vector<Subject> offsprings = generation.reproduction(generation.size());
    CHECK_EQUAL(generation.size(), offsprings.size());
        for(auto& offspring : offsprings)
            for(auto& subject : subjects)
                for(unsigned m = 0; m < f.size(); ++m)
                    CHECK(offspring.rateByF(m) != subject.rateByF(m));
}

class GenerationWithFronts : public GenerationWithSubjects
{
public:
    GenerationMock generation;
    Fronts fronts;

    GenerationWithFronts()
        : GenerationWithSubjects(), generation(subjects, f)
    {
        fronts = generation.nonDominatedSort();
    }
};

TEST_FIXTURE(GenerationWithFronts, initialValues)
{
    CHECK_EQUAL(4, fronts.size());
    CHECK_EQUAL(5, fronts[0].size());
    CHECK_EQUAL(3, fronts[1].size());
    CHECK_EQUAL(1, fronts[2].size());
    CHECK_EQUAL(1, fronts[3].size());
    for(auto& subject : generation.getSubjects())
        CHECK_EQUAL(0, subject.getDistance());
}

TEST_FIXTURE(GenerationWithFronts, crowdingDistanceAssignment)
{
    generation.calculateCrowdingDistances();
    fronts = generation.getFronts();

    const double inf = std::numeric_limits<double>::infinity();

    CHECK_CLOSE(inf, fronts[0][0]->getDistance(), 0.01);
    CHECK_CLOSE(0.28, fronts[0][1]->getDistance(), 0.01);
    CHECK_CLOSE(0.19, fronts[0][2]->getDistance(), 0.01);
    CHECK_CLOSE(0.25, fronts[0][3]->getDistance(), 0.01);
    CHECK_CLOSE(inf, fronts[0][4]->getDistance(), 0.01);

    CHECK_CLOSE(inf, fronts[1][0]->getDistance(), 0.01);
    CHECK_CLOSE(0.12, fronts[1][1]->getDistance(), 0.01);
    CHECK_CLOSE(inf, fronts[1][2]->getDistance(), 0.01);

    CHECK_CLOSE(inf, fronts[2][0]->getDistance(), 0.01);

    CHECK_CLOSE(inf, fronts[3][0]->getDistance(), 0.01);
}

TEST_FIXTURE(GenerationWithFronts, returnFirstFront)
{
    std::vector<std::vector<double>> firstFront = generation.getFirstFront();
    CHECK_EQUAL(f.size(), firstFront.size());
    CHECK_EQUAL(5, firstFront[0].size());
    CHECK_EQUAL(5, firstFront[1].size());
    // assume that first front is on begining of our subjects vector
    for(unsigned i = 0; i < firstFront[0].size(); ++i)
        for(unsigned j = 0; j < f.size(); ++j)
            CHECK_EQUAL(subjects[i].rateByF(j), firstFront[j][i]);
}
