#pragma once

#include "../test.h"
#include "../../structures/priority_queue/priority_queue.h"
#include "../../structures/priority_queue/priority_queue_list.h"
#include "../../structures/heap_monitor.h"
#include "../../file_log_consumer.h"

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

    //****************Druha uloha
   
    class PriorityQueuePerformanceTest : public SimpleTest {
    public:
        PriorityQueuePerformanceTest();
        void PriorityQueuePerformanceTest::testPriorityQueue(structures::PriorityQueue<int>* priorityQueue, char script, std::string file, int count);
    };


    class HeapPerformanceTest : public PriorityQueuePerformanceTest {
    public:
        void test() override;
    };


    class TwoListsPerformanceTest : public PriorityQueuePerformanceTest {
    public:
        void test() override;
    };

    //****************Tretia uloha

    class PriorityQueueTimeAnalysis : public SimpleTest {
    public:
        PriorityQueueTimeAnalysis();
        void testPush(structures::PriorityQueue<int>* priorityQueue, std::string file);
        void testPop(structures::PriorityQueue<int>* priorityQueue, std::string file);
        void testPeek(structures::PriorityQueue<int>* priorityQueue, std::string file);

    };


    class HeapTimeAnalysis : public PriorityQueueTimeAnalysis {
    public:
        void test() override;
    };


    class TwoListsTimeAnalysis : public PriorityQueueTimeAnalysis {
    public:
        void test() override;
    };

    
    //****************Unit testy
    class PriorityQueueTestPop
        : public SimpleTest
    {
    public:
        PriorityQueueTestPop();
        void testPop(structures::PriorityQueue<int>* list);
    };

    class HeapPop
        : public PriorityQueueTestPop
    {
    public:
        void test() override;
    };

    class TwoListsPop
        : public PriorityQueueTestPop
    {
    public:
        void test() override;
    };
    class PriorityQueueTestPush
        : public SimpleTest
    {
    public:
        PriorityQueueTestPush();
        void testPush(structures::PriorityQueue<int>* list) ;
    };

    class HeapPush
        : public PriorityQueueTestPush
    {
    public:
        void test() override;
    };

    class TwoListsPush
        : public PriorityQueueTestPush
    {
    public:
        void test() override;
    };

    class PriorityQueueTestPeek
        : public SimpleTest
    {
    public:
        PriorityQueueTestPeek();
        void testPeek(structures::PriorityQueue<int>* list);
    };

    class HeapPeek
        : public PriorityQueueTestPeek
    {
    public:
        void test() override;
    };

    class TwoListsPeek
        : public PriorityQueueTestPeek
    {
    public:
        void test() override;
    };

    class PriorityQueueTestAssign
        : public SimpleTest
    {
    public:
        PriorityQueueTestAssign();
        void testAssign(structures::PriorityQueue<int>* list1, structures::PriorityQueue<int>* list2);
    };

    class HeapAssign
        : public PriorityQueueTestAssign
    {
    public:
        void test() override;
    };

    class TwoListsAssign
        : public PriorityQueueTestAssign
    {
    public:
        void test() override;
    };


    class HeapCopy
        : public SimpleTest
    {
    public:
        HeapCopy();
        void test() override;
    };

    class TwoListsCopy
        : public SimpleTest
    {
    public:
        TwoListsCopy();
        void test() override;
    };
    //*******************************************

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