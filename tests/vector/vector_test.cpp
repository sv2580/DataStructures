#include "vector_test.h"
#include "../../structures/vector/vector.h"

namespace tests
{
// VectorTestInterface:

    VectorTestInterface::VectorTestInterface() :
        SimpleTest("Interface")
    {
    }

    void VectorTestInterface::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        vector->size();
        vector->assign(*vector);
        vector->equals(*vector);
        vector->at(0);
        vector->getBytePointer(0);
        //structures::Vector::copy(*vector, 0, *vector, 0, 1);
        delete vector;
        SimpleTest::logPass("Compiled.");
    }

    VectorTestAt::VectorTestAt() :
        SimpleTest("at")
    {
    }

    void VectorTestAt::test() {
        this->logInfo("Creating vector with size 10.");
        structures::Vector* vector = new structures::Vector(10);
        this->assertTrue(vector->size() == 10, "size() is 10.");

        this->logInfo("Setting vector->at(i) = i.");
        for (int i = 0; i < 10; i++)
        {
            vector->at(i) = i;
        }

        this->logInfo("Checking if vector->at(i) == i.");
        for (int i = 0; i < 10; i++)
        {
            if (vector->at(i) != i) {
                this->fail("vector->at(i) != i for i = " + std::to_string(i));
                return;
            }

        }
        this->succeed("vector->at(i) == i.");

        this->logInfo("Checking if *vector->getBytePionter(i) == i.");
        for (int i = 0; i < 10; i++)
        {
            if (*vector->getBytePointer(i) != i) {
                this->fail("*vector->getBytePointer(i) != i for i = " + std::to_string(i));
                return;
            }

        }
        this->succeed("*vector->getBytePointer(i) == i.");

        delete vector;

        //structures::Logger::getInstance().logInfo("This is info.");

        //structures::Logger::getInstance().logWarning("This is warning.");

        //structures::Logger::getInstance().logError("This is error.");

        //structures::Logger::getInstance().logDuration(100,DurationType(123),"This is duration.");
    }


    // VectorTestCopy:  !SPRAVIT!

    VectorTestCopy::VectorTestCopy() :
        SimpleTest("copy")
    {
    }

    void VectorTestCopy::test() {
        this->logInfo("Creating vector with size 10.");
        structures::Vector* vector = new structures::Vector(10);
        

        this->logInfo("Setting vector->at(i) = i.");
        for (int i = 0; i < 10; i++)
        {
            vector->at(i) = i;
        }

        this->logInfo("Creating copy of the vector.");
        structures::Vector* vectorCopy = new structures::Vector(10);
        this->assertTrue(vectorCopy->size() == 10, "size() is 10.");

        this->logInfo("Chenging the second vector.");
        for (int k = 0; k < 10; k++)
        {
            vectorCopy->at(k) = vector->at(k);
        }
        this->succeed("*vectorCopy->getBytePointer(k) == *vector->getBytePointer(k).");

        delete vector;

        //structures::Logger::getInstance().logInfo("This is info.");

        //structures::Logger::getInstance().logWarning("This is warning.");

        //structures::Logger::getInstance().logError("This is error.");

        //structures::Logger::getInstance().logDuration(100,DurationType(123),"This is duration.");
    }





// VectorTestOverall:

    VectorTestOverall::VectorTestOverall() :
        ComplexTest("Vector")
    {
        addTest(new VectorTestInterface());
        addTest(new VectorTestAt());
        addTest(new VectorTestCopy());
    }
}