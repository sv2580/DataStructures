#pragma once

#include "../test.h"
#include "../../structures/priority_queue/priority_queue.h"
#include "../../structures/priority_queue/priority_queue_list.h"
#include "../../structures/heap_monitor.h"
#include "../../file_log_consumer.h"
#include <fstream>;

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania prioritneho frontu avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class PriorityQueueTestInterface
        : public SimpleTest
    {
    public:
        PriorityQueueTestInterface();
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() = 0;
    };

    // UNIT TESTY
    // 
     //PUSH testy
    class PriorityQueuePushTest
        : public SimpleTest
    {
    public:
        PriorityQueuePushTest();
        void pushTest(structures::PriorityQueue<int>* list);
    };

    class HeapPush
        : public PriorityQueuePushTest
    {
    public:
        void test() override;
    };

    class TwoListsPush
        : public PriorityQueuePushTest
    {
    public:
        void test() override;
    };

    //POP testy
    class PriorityQueuePopTest
        : public SimpleTest
    {
    public:
        PriorityQueuePopTest();
        void popTest(structures::PriorityQueue<int>* list);
    };

    class HeapPop
        : public PriorityQueuePopTest
    {
    public:
        void test() override;
    };

    class TwoListsPop
        : public PriorityQueuePopTest
    {
    public:
        void test() override;
    };

    //PEEK testy
    class PriorityQueuePeekTest
        : public SimpleTest
    {
    public:
        PriorityQueuePeekTest();
        void peekTest(structures::PriorityQueue<int>* list);
    };

    class HeapPeek
        : public PriorityQueuePeekTest
    {
    public:
        void test() override;
    };

    class TwoListsPeek
        : public PriorityQueuePeekTest
    {
    public:
        void test() override;
    };

    //ASSIGN testy
    class PriorityQueueAssignTest
        : public SimpleTest
    {
    public:
        PriorityQueueAssignTest();
        void assignTest(structures::PriorityQueue<int>* list1, structures::PriorityQueue<int>* list2);
    };

    class HeapAssign
        : public PriorityQueueAssignTest
    {
    public:
        void test() override;
    };

    class TwoListsAssign
        : public PriorityQueueAssignTest
    {
    public:
        void test() override;
    };

    //CLEAR testy
  

    class TwoListsClear
        : public SimpleTest
    {
    public:
        TwoListsClear();
        void test() override;
    };

    //Koniec UNIT TESTY

    //SCENARE TESTY
    class PQPerformanceTest : public SimpleTest {
    public:
        PQPerformanceTest();
        void PQPerformanceTest::PQtest(structures::PriorityQueue<int>* priorityQueue, char script, std::string file, int count);
    };


    class HeapPerformanceTest : public PQPerformanceTest {
    public:
        void test() override;
    };


    class TwoListsPerformanceTest : public PQPerformanceTest {
    public:
        void test() override;
    };
    //Koniec SCENARE TESTY

    //MERANIE CASU testy

    class HeapTestTimeComplexityPush : public SimpleTest {
    public:
        HeapTestTimeComplexityPush();
        void test() override;
    };
    
    class HeapTestTimeComplexityPop : public SimpleTest {
    public:
        HeapTestTimeComplexityPop();
        void test() override;
    };

    class HeapTestTimeComplexityPeek : public SimpleTest {
    public:
        HeapTestTimeComplexityPeek();
        void test() override;
    };

    class PQTwoListsTestTimeComplexityPush : public SimpleTest {
    public:
        PQTwoListsTestTimeComplexityPush();
        void test() override;
    };

    class PQTwoListsTestTimeComplexityPop : public SimpleTest {
    public:
        PQTwoListsTestTimeComplexityPop();
        void test() override;
    };

    class PQTwoListsTestTimeComplexityPeek : public SimpleTest {
    public:
        PQTwoListsTestTimeComplexityPeek();
        void test() override;
    };

    //MESRANIE CASU testy koniec

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLinkedListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueTwoListsTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class HeapTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueUnsortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLimitedSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLinkedListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLinkedListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueTwoListsTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTwoListsTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class HeapTestOverall
        : public ComplexTest
    {
    public:
        HeapTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju prioritny front.
    /// </summary>
    class PriorityQueueTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTestOverall();
    };
}