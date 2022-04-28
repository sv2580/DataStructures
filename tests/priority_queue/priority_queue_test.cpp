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
    PriorityQueueTestPop::PriorityQueueTestPop() : SimpleTest("Pop")
    {
    }
    void PriorityQueueTestPop::testPop(structures::PriorityQueue<int>* list)
    {
        logInfo("Testing pop, first pushing in the queue with priorities 0,1,...");
        std::string s = "";
        for (int i = 0; i < 10; i++)
        {
            list->push(i,i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        s = "";
        for (int i = 0; i <  list->size(); i++)
        {
            s += std::to_string(list->pop());
        }
        logInfo("Popped values:" + s);

        logInfo("Trying to pop another value");
        list->pop();
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
        for (int i = 0; i < list->size(); i++)
        {
            s += std::to_string(list->pop());
        }
        logInfo("Popped values:" + s);
    }


    PriorityQueueTestPeek::PriorityQueueTestPeek() : SimpleTest("Peek")
    {
    }

    void PriorityQueueTestPeek::testPeek(structures::PriorityQueue<int>* list)
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
        logInfo("Assigning to second queue");
        list1->assign(*list2);
        logInfo("Popping second queue to see the values");
        for (int i = 0; i < list2->size(); i++)
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
    }


    TwoListsCopy::TwoListsCopy() : SimpleTest("Copy")
    {
    }

    void TwoListsCopy::test()
    {
        structures::PriorityQueueTwoLists<int>* list1 = new structures::PriorityQueueTwoLists<int>();
        logInfo("Testing assign, first pushing in the list with priorities 0,1,.. to first Queue");
        std::string s = "";
        for (int i = 0; i < 10; i++)
        {
            list1->push(i, i);
            s += std::to_string(i);
        }
        logInfo("Pushed values:" + s);
        logInfo("Copying to second");
        structures::PriorityQueueTwoLists<int>* list2 = new structures::PriorityQueueTwoLists<int>(*list1);
        logInfo("Popping second queue to see the values");
        for (int i = 0; i < list2->size(); i++)
        {
            s += std::to_string(list2->pop());
        }
        logInfo("Popped values:" + s);
    }


    HeapPop::HeapPop()
    {
    }

    void HeapPop::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        testPop(heap);
        delete heap;
    }


    TwoListsPop::TwoListsPop()
    {
    }

    void TwoListsPop::test()
    {
        structures::PriorityQueueTwoLists<int>* list = new structures::PriorityQueueTwoLists<int>();
        testPop(list);
        delete list;
    }


    HeapPush::HeapPush()
    {
    }

    void HeapPush::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        testPush(heap);
        delete heap;
    }


    TwoListsPush::TwoListsPush()
    {
    }

    void TwoListsPush::test()
    {
        structures::PriorityQueueTwoLists<int>* list = new structures::PriorityQueueTwoLists<int>();
        testPush(list);
        delete list;
    }


    HeapPeek::HeapPeek()
    {
    }

    void HeapPeek::test()
    {
        structures::Heap<int>* heap = new structures::Heap<int>();
        testPeek(heap);
        delete heap;
    }


    TwoListsPeek::TwoListsPeek()
    {
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

        testAssign(heap,heap2);
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