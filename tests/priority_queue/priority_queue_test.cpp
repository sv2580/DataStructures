#include "priority_queue_test.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"

namespace tests
{
    PriorityQueueTestInterface::PriorityQueueTestInterface() :
        SimpleTest("Interface")
    {
    }

    void PriorityQueueTestInterface::test()
    {
        int x = 0;
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLimitedSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestInterface::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueUnsortedArrayListTestOverall::PriorityQueueUnsortedArrayListTestOverall() :
        ComplexTest("PriorityQueueUnsortedArray")
    {
        addTest(new PriorityQueueUnsortedArrayListTestInterface());
    }

    PriorityQueueSortedArrayListTestOverall::PriorityQueueSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueSortedArrayList")
    {
        addTest(new PriorityQueueSortedArrayListTestInterface());
    }

    PriorityQueueLimitedSortedArrayListTestOverall::PriorityQueueLimitedSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueLimitedSortedArrayList")
    {
        addTest(new PriorityQueueLimitedSortedArrayListTestInterface());
    }

    PriorityQueueLinkedListTestOverall::PriorityQueueLinkedListTestOverall() :
        ComplexTest("PriorityQueueLinkedList")
    {
        addTest(new PriorityQueueLinkedListTestInterface());
    }

    PriorityQueueTwoListsTestOverall::PriorityQueueTwoListsTestOverall() :
        ComplexTest("PriorityQueueTwoLists")
    {
        addTest(new PriorityQueueTwoListsTestInterface());
        addTest(new TwoListsPop());
        addTest(new TwoListsPush());
        addTest(new TwoListsPeek());
        addTest(new TwoListsAssign());
        addTest(new TwoListsCopy());
        addTest(new TwoListsPerformanceTest());
        addTest(new TwoListsTimeAnalysis());

    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapPop());
        addTest(new HeapPush());
        addTest(new HeapPeek());
        addTest(new HeapAssign());
        addTest(new HeapCopy());

        addTest(new HeapPerformanceTest());
        addTest(new HeapTimeAnalysis());

    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
      //  addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
    }




    PriorityQueuePerformanceTest::PriorityQueuePerformanceTest() : SimpleTest("PerformanceTest")
    {
    }

    void PriorityQueuePerformanceTest::testPriorityQueue(structures::PriorityQueue<int>* priorityQueue, char script, std::string file, int count)
    {
        int push, pop, peek;
        switch (script)
        {
        case 'A':
            push = 35;
            pop = 35;
            peek = 30;
            break;
        case 'B':
            push = 50;
            pop = 30;
            peek = 20;
            break;
        case 'C':
            push = 70;
            pop = 25;
            peek = 5;
            break;
        }
        structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
        std::string message = "Testing script ";
        message.append(&script);
        consumer->logMessage(structures::LogType::Info, message);
        srand(time(0));
        for (int i = 0; i < count; i++)
        {
            int random = rand() % 100 + 1;
            if (random <= push) {
                int priority = rand() % 100000;
                startStopwatch();
                priorityQueue->push(priority, i);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "push ; " + std::to_string(priorityQueue->size()));
            }
            else if (push < random && random <= push + pop) {
                if (!priorityQueue->isEmpty()) {
                    startStopwatch();
                    priorityQueue->pop();
                    stopStopwatch();
                    consumer->logDuration(0, getElapsedTime(), "pop ; " + std::to_string(priorityQueue->size()));
                }
            }
            else {
                if (!priorityQueue->isEmpty()) {
                    startStopwatch();
                    priorityQueue->peek();
                    stopStopwatch();
                    consumer->logDuration(0, getElapsedTime(), "peek ; " + std::to_string(priorityQueue->size()));
                }
            }

        }

        delete consumer;
    }



    void HeapPerformanceTest::test()
    {
        char script = 'A';
        for (int i = 0; i < 3; i++)
        {
            structures::PriorityQueue<int>* heap = new structures::Heap<int>();
            std::string file = "Heap";
            file.append(&script);
            this->testPriorityQueue(heap, script, file + ".csv", 100000);
            script++;
            delete heap;
        }

    }


    void TwoListsPerformanceTest::test()
    {
        char script = 'A';
        for (int i = 0; i < 3; i++)
        {
            structures::PriorityQueue<int>* twoLists = new structures::PriorityQueueTwoLists<int>();
            std::string file = "PriorityQueueTwoLists";
            file.append(&script);
            this->testPriorityQueue(twoLists, script, file + ".csv", 100000);
            script++;
            delete twoLists;
        }
    }


    PriorityQueueTimeAnalysis::PriorityQueueTimeAnalysis() : SimpleTest("TimeAnalysis")
    {
    }

    void PriorityQueueTimeAnalysis::testPush(structures::PriorityQueue<int>* priorityQueue, std::string file)
    {
        structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov bude v queue
            int size = priorityQueue->size();
            for (int j = 0; j < (1000 * i) - size; j++) //naplnenie queue tisic*i prvkov
            {
                int priority = rand() % 1000 * i; 
                priorityQueue->push(priority, j);
            }
            for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
            {
                int priority = rand() % 1000 * i;
                startStopwatch();
                priorityQueue->push(priority, j);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "push ; " + std::to_string(priorityQueue->size()));
            }
        }
        delete consumer;
        delete priorityQueue;

    }

    void PriorityQueueTimeAnalysis::testPop(structures::PriorityQueue<int>* priorityQueue, std::string file)
    {
        structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov bude v queue
            int size = priorityQueue->size();
            for (int j = 0; j < (1000 * i) - size; j++) //naplnenie queue tisic*i prvkov
            {
                int priority = rand() % 1000 * i;
                priorityQueue->push(priority, j);
            }
            for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
            {
                startStopwatch();
                priorityQueue->pop();
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "pop ; " + std::to_string(priorityQueue->size()));
            }
        }
        delete consumer;
        delete priorityQueue;

    }

    void PriorityQueueTimeAnalysis::testPeek(structures::PriorityQueue<int>* priorityQueue, std::string file)
    {
        structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov bude v queue
            int size = priorityQueue->size();
            for (int j = 0; j < (1000 * i) - size; j++) //naplnenie queue tisic*i prvkov
            {
                int priority = rand() % 1000 * i;
                priorityQueue->push(priority, j);
            }
            for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
            {
                startStopwatch();
                priorityQueue->peek();
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "peek ; " + std::to_string(priorityQueue->size()));
            }
        }
        delete consumer;
        delete priorityQueue;
    }


    void HeapTimeAnalysis::test()
    {
        this->testPush(new structures::Heap<int>(), "Heap_Push.csv");
        this->testPop(new structures::Heap<int>(), "Heap_Pop.csv");
        this->testPeek(new structures::Heap<int>(), "Heap_Peek.csv");


    }


    void TwoListsTimeAnalysis::test()
    {
        this->testPush(new structures::PriorityQueueTwoLists<int>(), "TwoLists_Push.csv");
        this->testPop(new structures::PriorityQueueTwoLists<int>(), "TwoLists_Pop.csv");
        this->testPeek(new structures::PriorityQueueTwoLists<int>(), "TwoLists_Peek.csv");
    }



    PriorityQueueTestPop::PriorityQueueTestPop() : SimpleTest("Pop")
    {
    }
    void PriorityQueueTestPop::testPop(structures::PriorityQueue<int>* list)
    {
        logInfo("Testing pop, first pushing in the queue with priorities 0,1,...");
        std::string s = "";

        for (int i = 0; i < 10; i++)
        {
            list->push(i, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        s = "";

        for (int i = 0; i < 10; i++)
        {
            int popped = list->pop();
            s += std::to_string(popped);
        }
        logInfo("Popped values:" + s);

        // logInfo("Trying to pop another value that isnt there");
        // list->pop();
        logPass("Sucess");
    }

    PriorityQueueTestPush::PriorityQueueTestPush() : SimpleTest("Push")
    {
    }

    void PriorityQueueTestPush::testPush(structures::PriorityQueue<int>* list)
    {
        logInfo("Testing pushing, pushing random values with priorities 10,9,...");
        std::string s = "";
        for (int i = 10; i > 0; i--)
        {
            int random = rand() % 10;
            list->push(random, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        s = "";
        for (int i = 0; i < 10; i++)
        {
            int popped = list->pop();
            s += std::to_string(popped);
        }
        logInfo("Popped values:" + s);
    }


    PriorityQueueTestPeek::PriorityQueueTestPeek() : SimpleTest("Peek")
    {
    }

    void PriorityQueueTestPeek::testPeek(structures::PriorityQueue<int>* list)
    {
        logInfo("Testing peek, pushing values with priorities 9,8,...");
        std::string s = "";
        for (int i = 9; i >= 0; i--)
        {
            list->push(i, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        logInfo("Peek is the number " + std::to_string(list->peek()));
        logInfo("Peek has priority " + std::to_string(list->peekPriority()));
    }


    PriorityQueueTestAssign::PriorityQueueTestAssign() : SimpleTest("Assign")
    {
    }

    void PriorityQueueTestAssign::testAssign(structures::PriorityQueue<int>* list1, structures::PriorityQueue<int>* list2)
    {
        logInfo("Testing assign, first pushing in the queue with priorities 0,1,.. to first Queue");
        std::string s = "";
        for (int i = 0; i < 10; i++)
        {
            list1->push(i, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        s = "";
        logInfo("Assigning to second queue");
        list2->assign(*list1);
        logInfo("Popping second queue to see the values");
        for (int i = 0; i < 10; i++)
        {
            s += std::to_string(list2->pop());
        }
        logInfo("Popped values:" + s);

    }


    HeapCopy::HeapCopy() : SimpleTest("Copy")
    {
    }

    void HeapCopy::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        logInfo("Testing assign, first pushing in the heap with priorities 0,1,.. to first Queue");
        std::string s = "";
        for (int i = 0; i < 10; i++)
        {
            heap->push(i, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        logInfo("Copying to second");
        structures::Heap<int>* heap2 = new structures::Heap<int>(*heap);
        logInfo("Popping second queue to see the values");
        for (int i = 0; i < heap2->size(); i++)
        {
            s += std::to_string(heap2->pop());
        }
        logInfo("Popped values:" + s);

        delete heap;
        delete heap2;
    }


    TwoListsCopy::TwoListsCopy() : SimpleTest("Copy")
    {
    }

    void TwoListsCopy::test()
    {
        structures::PriorityQueueTwoLists<int>* list1 = new structures::PriorityQueueTwoLists<int>();
        logInfo("Testing copy, first pushing in the list with priorities 0,1,.. to first Queue");
        std::string s = "";
        for (int i = 0; i < 10; i++)
        {
            list1->push(i, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        logInfo("Copying to second");
        s = "";
        structures::PriorityQueueTwoLists<int>* list2 = new structures::PriorityQueueTwoLists<int>(*list1);
        logInfo("Popping second queue to see the values");
        for (int i = 0; i < 10; i++)
        {
            s += std::to_string(list2->pop());
        }
        logInfo("Popped values:" + s);
        delete list1;
        delete list2;
    }




    void HeapPop::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        testPop(heap);
        delete heap;
    }


    void TwoListsPop::test()
    {
        structures::PriorityQueueTwoLists<int>* list = new structures::PriorityQueueTwoLists<int>();
        testPop(list);
        delete list;
    }




    void HeapPush::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        testPush(heap);
        delete heap;
    }



    void TwoListsPush::test()
    {
        structures::PriorityQueueTwoLists<int>* list = new structures::PriorityQueueTwoLists<int>();
        testPush(list);
        delete list;
    }


    void HeapPeek::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        testPeek(heap);
        delete heap;
    }



    void TwoListsPeek::test()
    {
        structures::PriorityQueueTwoLists<int>* list = new structures::PriorityQueueTwoLists<int>();
        testPeek(list);
        delete list;
    }


    void HeapAssign::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        structures::Heap<int>* heap2 = new structures::Heap<int>();

        testAssign(heap, heap2);
        delete heap;
        delete heap2;
    }


    void TwoListsAssign::test()
    {
        structures::PriorityQueueTwoLists<int>* list = new structures::PriorityQueueTwoLists<int>();
        structures::PriorityQueueTwoLists<int>* list2 = new structures::PriorityQueueTwoLists<int>();

        testAssign(list, list2);
        delete list;
        delete list2;
    }




}