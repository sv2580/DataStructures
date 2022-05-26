#include "priority_queue_test.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"
#include "../../file_log_consumer.h"
#include <fstream>;



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
    
    //UNIT testy
    //PUSH testy
    PriorityQueuePushTest::PriorityQueuePushTest() : SimpleTest("Push")
    {
    }

    void PriorityQueuePushTest::pushTest(structures::PriorityQueue<int>* list)
    {
        logInfo("PUSH priorít 10-1 (priority = data)");
        std::string hodnoty = "";
        for (int i = 10; i > 0; i--)
        {
            list->push(i, i);
            hodnoty += std::to_string(i);
            hodnoty += " ";

        }
        logInfo("PUSH hodnoty" + hodnoty);
        hodnoty = "";
        for (int i = 0; i < 10; i++)
        {
            int popped = list->pop();
            hodnoty += std::to_string(popped);
            hodnoty += " ";
        }
        logInfo("POP hodnoty:" + hodnoty);
        logPass("POP opaèné poradie ako PUSH");
    }

    void HeapPush::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        pushTest(heap);
        delete heap;
    }



    void TwoListsPush::test()
    {
        structures::PriorityQueueTwoLists<int>* PQTlist = new structures::PriorityQueueTwoLists<int>();
        pushTest(PQTlist);
        delete PQTlist;
    }

    //POP testy

    PriorityQueuePopTest::PriorityQueuePopTest() : SimpleTest("Pop")
    {
    }
    void PriorityQueuePopTest::popTest(structures::PriorityQueue<int>* list)
    {
        logInfo("PUSH random priorít v rozmedzi 1-10 (priority = data)");
        std::string hodnoty = "";

        for (int i = 0; i < 10; i++)
        {
            int r = 1+ (rand() % 10);
            list->push(r, r);
            hodnoty += std::to_string(r);
            hodnoty += " ";
        }
        logInfo("PUSH hodnoty:" + hodnoty);
        hodnoty = "";

        for (int i = 0; i < 10; i++)
        {
            int popped = list->pop();
            hodnoty += std::to_string(popped);
            hodnoty += " ";
        }
        logInfo("POP hodnoty:" + hodnoty);
        
        logPass("Zoradené");
    }

    void HeapPop::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        popTest(heap);
        delete heap;
    }


    void TwoListsPop::test()
    {
        structures::PriorityQueueTwoLists<int>* PQTlist = new structures::PriorityQueueTwoLists<int>();
        popTest(PQTlist);
        delete PQTlist;
    }

    //PEEK testy

    PriorityQueuePeekTest::PriorityQueuePeekTest() : SimpleTest("Peek")
    {
    }

    void PriorityQueuePeekTest::peekTest(structures::PriorityQueue<int>* list)
    {
        logInfo("PUSH random priorít v rozmedzi 1-10 (priority = data)");
        std::string hodnoty = "";
        for (int i = 9; i >= 0; i--)
        {
            int r = 1 + (rand() % 10);
            list->push(r, r);
            hodnoty += std::to_string(r);
            hodnoty += " ";
        }
        logInfo("PUSH hodnoty:" + hodnoty);
        logInfo("PEEK data " + std::to_string(list->peek()));
        logInfo("PEEK priority " + std::to_string(list->peekPriority()));
    }

    void HeapPeek::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        peekTest(heap);
        delete heap;
    }



    void TwoListsPeek::test()
    {
        structures::PriorityQueueTwoLists<int>* PQTlist = new structures::PriorityQueueTwoLists<int>();
        peekTest(PQTlist);
        delete PQTlist;
    }

    //ASSIGN testy

    PriorityQueueAssignTest::PriorityQueueAssignTest() : SimpleTest("Assign")
    {
    }

    void PriorityQueueAssignTest::assignTest(structures::PriorityQueue<int>* list1, structures::PriorityQueue<int>* list2)
    {
        logInfo("PUSH priorít 1-10 do PQ1 (priority = data)");
        std::string hodnoty = "";
        for (int i = 1; i < 11; i++)
        {
            list1->push(i, i);
            hodnoty += std::to_string(i);
            hodnoty += " ";
        }
        logInfo("PUSH hodnoty:" + hodnoty);
        std::string hodnoty2 = "";
        logInfo("ASSIGN PQ1 -> PQ2");
        list2->assign(*list1);
        logInfo("POP PQ2");
        for (int i = 1; i < 11; i++)
        {
            hodnoty2 += std::to_string(list2->pop());
            hodnoty2 += " ";
        }
        logInfo("POP hodnoty:" + hodnoty);
        SimpleTest::assertTrue(hodnoty == hodnoty2, "PQ rovnaju sa");

    }

    void HeapAssign::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        structures::Heap<int>* heap2 = new structures::Heap<int>();

        assignTest(heap, heap2);
        delete heap;
        delete heap2;
    }


    void TwoListsAssign::test()
    {
        structures::PriorityQueueTwoLists<int>* PQTlist = new structures::PriorityQueueTwoLists<int>();
        structures::PriorityQueueTwoLists<int>* PQTlist2 = new structures::PriorityQueueTwoLists<int>();

        assignTest(PQTlist, PQTlist2);
        delete PQTlist;
        delete PQTlist2;
    }

    //CLEAR testy


    TwoListsClear::TwoListsClear() : SimpleTest("Clear")
    {
    }

    void TwoListsClear::test()
    {
        structures::PriorityQueueTwoLists<int>* PQTlist = new structures::PriorityQueueTwoLists<int>();
        logInfo("PUSH priorít 1-10 (priority = data)");
        std::string hodnoty = "";
        for (int i = 1; i < 11; i++)
        {
            PQTlist->push(i, i);
            hodnoty += std::to_string(i);
            hodnoty += " ";
        }
        logInfo("PUSH hodnoty:" + hodnoty);
        logInfo("CLEAR");
        hodnoty = "";
        PQTlist->clear();

        SimpleTest::assertTrue(PQTlist->size() == (0), "PQTwoLists::size() prazdny");
        delete PQTlist;
        
    }

    //UNIT testy KONIEC

    //VYKONOSTNE testy
    PQPerformanceTest::PQPerformanceTest() : SimpleTest("PerformanceTest")
    {
    }

    void PQPerformanceTest::PQtest(structures::PriorityQueue<int>* priorityQueue, char script, std::string file, int count)
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
            this->PQtest(heap, script, file + ".csv", 100000);
            script++;
            delete heap;
        }

    }


    void TwoListsPerformanceTest::test()
    {
        char script = 'A';
        for (int i = 0; i < 3; i++)
        {
            structures::PriorityQueue<int>* PQtwoLists = new structures::PriorityQueueTwoLists<int>();
            std::string file = "PriorityQueueTwoLists";
            file.append(&script);
            this->PQtest(PQtwoLists, script, file + ".csv", 100000);
            script++;
            delete PQtwoLists;
        }
    }
    //VYKONOSTNE testy koniec

    //MERANIE ÈASU testy
    
    //HeapTestTimeComplexityPush::HeapTestTimeComplexityPush() : SimpleTest("HeapTimeComplexityTestPush")
    //{
    //}
    //void HeapTestTimeComplexityPush::test()
    //{
    //    structures::PriorityQueue<int>* newPQ = new structures::Heap<int>();
    //    std::ofstream heapTimePush;
    //    heapTimePush.open("HeapTimePush.csv");
    //    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    //    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    //    int priority1;
    //    int priority2;
    //    int data;

    //    int whileSize = 0;
    //    srand(time(NULL));
    //    while (whileSize <= 99) {
    //        for (int i = 0; i < 10 * whileSize; i++) {
    //            priority1 = rand() % 100000 + 1;
    //            newPQ->push(priority1, i);
    //        }
    //        for (int i = 0; i < 100; i++) {
    //            data = rand() % 100 + 1;
    //            priority2 = rand() % 100000 + 1;

    //            start = std::chrono::high_resolution_clock::now();
    //            newPQ->push(priority2, data);
    //            end = std::chrono::high_resolution_clock::now();
    //            unsigned long long operationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    //            heapTimePush << operationTime << ";" << "1;" << newPQ->size() << "\n";
    //        }
    //        whileSize++;
    //    }

    //    delete newPQ;
    //    heapTimePush.close();

    //    logPass("HeapTestComplexityPush succesfully finished");

    //}

    HeapTestTimeComplexityPush::HeapTestTimeComplexityPush() : SimpleTest("HeapTimeComplexityTestPush")
    {
    }
    void HeapTestTimeComplexityPush::test()
    {
        structures::PriorityQueue<int>* newHeap = new structures::Heap<int>();
        structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("HeapTimeComplexityTestPush.csv");

        int priority1;
        int priority2;
        int data;

        int whileSize = 1;
        srand(time(NULL));
        
            while (whileSize <= 100) {
                for (int i = 0; i < 1000 * whileSize; i++) {
                    priority1 = rand() % 100000 + 1;
                    newHeap->push(priority1, i);
                }
                for (int i = 0; i < 1000; i++) {
                    data = rand() % 100 + 1;
                    priority2 = rand() % 100000 + 1;

                    startStopwatch();
                    newHeap->push(priority2, data);
                    stopStopwatch();
                    fileLog->logDuration(0, getElapsedTime(), std::to_string(newHeap->size()));
                }
                whileSize++;
            }
        

        delete newHeap;
        delete fileLog;

        logPass("HeapTestComplexityPush succesfully finished");

    }

    //HeapTestTimeComplexityPop::HeapTestTimeComplexityPop() : SimpleTest("HeapTimeComplexityTestPop")
    //{
    //}
    //void HeapTestTimeComplexityPop::test()
    //{
    //    structures::PriorityQueue<int>* newPQ = new structures::Heap<int>();
    //    std::ofstream heapTimePop;
    //    heapTimePop.open("HeapTimePop.csv");
    //    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    //    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    //    for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov bude v queue
    //        int size = newPQ->size();
    //        for (int j = 0; j < (1000 * i) - size; j++) //naplnenie queue tisic*i prvkov
    //        {
    //            int priority = rand() % 1000 * i;
    //            newPQ->push(priority, j);
    //        }
    //        for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
    //        {
    //            start = std::chrono::high_resolution_clock::now();
    //            newPQ->pop();
    //            end = std::chrono::high_resolution_clock::now();
    //            unsigned long long operationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    //            heapTimePop << operationTime << ";" << "1;" << newPQ->size() << "\n";
    //        }
    //    }

    //    delete newPQ;
    //    heapTimePop.close();

    //    logPass("HeapTestComplexityPop succesfully finished");

    //}


    /*HeapTestTimeComplexityPop::HeapTestTimeComplexityPop() : SimpleTest("HeapTimeComplexityTestPop")
    {
    }
    void HeapTestTimeComplexityPop::test()
    {
        structures::PriorityQueue<int>* newPQ = new structures::Heap<int>();
        std::ofstream heapTimePop;
        heapTimePop.open("HeapTimePop.csv");
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        std::chrono::time_point<std::chrono::high_resolution_clock> start;

        int priority1;
        int data;

        int whileSize = 1;
        srand(time(NULL));
        while (whileSize <= 100) {
            for (int i = 0; i < 10 * whileSize; i++) {
                priority1 = rand() % 100000 + 1;
                newPQ->push(priority1, i);
            }
            for (int i = 0; i < 100; i++) {
                start = std::chrono::high_resolution_clock::now();
                newPQ->pop();
                end = std::chrono::high_resolution_clock::now();
                unsigned long long operationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                heapTimePop << operationTime << ";" << "1;" << newPQ->size() << "\n";
            }
            whileSize++;
        }

        delete newPQ;
        heapTimePop.close();

        logPass("HeapTestComplexityPop succesfully finished");*/

    //}

    HeapTestTimeComplexityPop::HeapTestTimeComplexityPop() : SimpleTest("HeapTimeComplexityTestPop")
    {
    }
    void HeapTestTimeComplexityPop::test()
    {
        structures::PriorityQueue<int>* newHeap = new structures::Heap<int>();
        structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("HeapTimeComplexityTestPop.csv");

        int priority1;
        
        int data;

        int whileSize = 1;
        srand(time(NULL));
        while (whileSize <= 100) {
            for (int i = 0; i < 1000 * whileSize; i++) {
                priority1 = rand() % 100000 + 1;
                newHeap->push(priority1, i);
            }
            for (int i = 0; i < 1000; i++) {
                

                startStopwatch();
                newHeap->pop();
                stopStopwatch();
                fileLog->logDuration(0, getElapsedTime(), std::to_string(newHeap->size()));
            }
            whileSize++;
        }

        delete newHeap;
        delete fileLog;

        logPass("HeapTestComplexityPop succesfully finished");

    }

    HeapTestTimeComplexityPeek::HeapTestTimeComplexityPeek() : SimpleTest("HeapTimeComplexityTestPeek")
    {
    }
    void HeapTestTimeComplexityPeek::test()
    {
        structures::PriorityQueue<int>* newHeap = new structures::Heap<int>();
        structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("HeapTimeComplexityTestPeek.csv");

        int priority1;

        int data;

        int whileSize = 1;
        srand(time(NULL));
        while (whileSize <= 100) {
            for (int i = 0; i < 1000 * whileSize; i++) {
                priority1 = rand() % 100000 + 1;
                newHeap->push(priority1, i);
            }
            for (int i = 0; i < 1000; i++) {


                startStopwatch();
                newHeap->peek();
                stopStopwatch();
                fileLog->logDuration(0, getElapsedTime(), std::to_string(newHeap->size()));
            }
            whileSize++;
        }

        delete newHeap;
        delete fileLog;

        logPass("HeapTestComplexityPeek succesfully finished");

    }

    PQTwoListsTestTimeComplexityPush::PQTwoListsTestTimeComplexityPush() : SimpleTest("PQTwoListsTimeComplexityTestPush")
    {
    }
    void PQTwoListsTestTimeComplexityPush::test()
    {
        structures::PriorityQueue<int>* newPQ = new structures::PriorityQueueTwoLists<int>();
        structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("PQTwoListsTimeComplexityTestPush.csv");

        int priority1;
        int priority2;
        int data;

        int whileSize = 1;
        srand(time(NULL));
        while (whileSize <= 100) {
            for (int i = 0; i < 1000 * whileSize; i++) {
                priority1 = rand() % 100000 + 1;
                newPQ->push(priority1, i);
            }
            for (int i = 0; i < 1000; i++) {
                data = rand() % 100 + 1;
                priority2 = rand() % 100000 + 1;

                startStopwatch();
                newPQ->push(priority2, data);
                stopStopwatch();
                fileLog->logDuration(0, getElapsedTime(), std::to_string(newPQ->size()));
            }
            whileSize++;
        }

        delete newPQ;
        delete fileLog;

        logPass("PQTwoListsTestComplexityPush succesfully finished");

    }

    PQTwoListsTestTimeComplexityPop::PQTwoListsTestTimeComplexityPop() : SimpleTest("PQTwoListsTimeComplexityTestPop")
    {
    }
    void PQTwoListsTestTimeComplexityPop::test()
    {
        structures::PriorityQueue<int>* newPQ = new structures::PriorityQueueTwoLists<int>();
        structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("PQTwoListsTimeComplexityTestPop.csv");

        int priority1;

        int data;

        int whileSize = 1;
        srand(time(NULL));
        while (whileSize <= 100) {
            for (int i = 0; i < 1000 * whileSize; i++) {
                priority1 = rand() % 100000 + 1;
                newPQ->push(priority1, i);
            }
            for (int i = 0; i < 1000; i++) {


                startStopwatch();
                newPQ->pop();
                stopStopwatch();
                fileLog->logDuration(0, getElapsedTime(), std::to_string(newPQ->size()));
            }
            whileSize++;
        }

        delete newPQ;
        delete fileLog;

        logPass(" PQTwoListsTestComplexityPop succesfully finished");

    }

    PQTwoListsTestTimeComplexityPeek::PQTwoListsTestTimeComplexityPeek() : SimpleTest(" PQTwoListsTimeComplexityTestPeek")
    {
    }
    void  PQTwoListsTestTimeComplexityPeek::test()
    {
        structures::PriorityQueue<int>* newPQ = new structures::PriorityQueueTwoLists<int>();
        structures::FileLogConsumer* fileLog = new structures::FileLogConsumer(" PQTwoListsTimeComplexityTestPeek.csv");

        int priority1;

        int data;

        int whileSize = 1;
        srand(time(NULL));
        while (whileSize <= 100) {
            for (int i = 0; i < 1000 * whileSize; i++) {
                priority1 = rand() % 100000 + 1;
                newPQ->push(priority1, i);
            }
            for (int i = 0; i < 1000; i++) {


                startStopwatch();
                newPQ->peek();
                stopStopwatch();
                fileLog->logDuration(0, getElapsedTime(), std::to_string(newPQ->size()));
            }
            whileSize++;
        }

        delete newPQ;
        delete fileLog;

        logPass(" PQTwoListsTestComplexityPeek succesfully finished");

    }

    //MERANIE ÈASU testy koniec


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
        addTest(new TwoListsPush());
        addTest(new TwoListsPop());
        addTest(new TwoListsPeek());
        addTest(new TwoListsAssign());
        addTest(new TwoListsClear());

        addTest(new TwoListsPerformanceTest());

        addTest(new PQTwoListsTestTimeComplexityPush());
        addTest(new PQTwoListsTestTimeComplexityPop());
        addTest(new PQTwoListsTestTimeComplexityPeek());
        

    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapPush());
        addTest(new HeapPop());
        addTest(new HeapPeek());
        addTest(new HeapAssign());

        addTest(new HeapPerformanceTest());

        addTest(new HeapTestTimeComplexityPush());
        addTest(new HeapTestTimeComplexityPop());
        addTest(new HeapTestTimeComplexityPeek());
        
    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
        addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
    }
}