#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

		TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		//addTest(new HashTableTestOverall());
		//addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		//addTest(new TreapTestOverall());
		//addTest(new UnsortedSequenceTableTestOverall());
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
	}


    TablePerformanceTest::TablePerformanceTest() : SimpleTest("PerformanceTest")
    {
    }

        void testTable(structures::Table<int, int>* table, char script, std::string file, int count)
    {
        int insert, remove, tryFind;
        switch (script)
        {
        case 'A':
            insert = 20;
            remove = 20;
            tryFind = 60;
            break;
        case 'B':
            insert = 40;
            remove = 0;
            tryFind = 20;
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
            if (random <= insert) {
                int priority = rand() % 100000;
                startStopwatch();
                table->insert(priority, i);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(table->size()));
            }
            else if (insert < random && random <= insert + remove) {
                if (!table->isEmpty()) {
                    startStopwatch();
                    table->remove();
                    stopStopwatch();
                    consumer->logDuration(0, getElapsedTime(), "remove ; " + std::to_string(table->size()));
                }
            }
            else {
                if (!table->isEmpty()) {
                    startStopwatch();
                    table->tryFind();
                    stopStopwatch();
                    consumer->logDuration(0, getElapsedTime(), "tryFind ; " + std::to_string(table->size()));
                }
            }

        }

        delete consumer;
    }



    void SortedSequenceTablePerformanceTest::test()
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


    void BinarySearchTreePerformanceTest::test()
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


    TableTimeAnalysis::TableTimeAnalysis() : SimpleTest("TimeAnalysis")
    {
    }

    void TableTimeAnalysis::testInsert(structures::Table<int,int>* table, std::string file)
    {
        structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov bude v queue
            int size = priorityQueue->size();
            for (int j = 0; j < (1000 * i) - size; j++) //naplnenie queue tisic*i prvkov
            {
                int priority = rand() % 1000 * i; 
                priorityQueue->insert(priority, j);
            }
            for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
            {
                int priority = rand() % 1000 * i;
                startStopwatch();
                priorityQueue->insert(priority, j);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(priorityQueue->size()));
            }
        }
        delete consumer;
        delete priorityQueue;

    }

    void TableTimeAnalysis::testRemove(structures::Table<int,int>* table, std::string file)
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
                priorityQueue->remove();
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "remove ; " + std::to_string(priorityQueue->size()));
            }
        }
        delete consumer;
        delete priorityQueue;

    }

    void TableTimeAnalysis::testTryFind(structures::Table<int,int>* table, std::string file)
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
                priorityQueue->tryFind();
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "tryFind ; " + std::to_string(priorityQueue->size()));
            }
        }
        delete consumer;
        delete priorityQueue;
    }


    void HeapTimeAnalysis::test()
    {
        this->testPop(new structures::Heap<int>(), "Heap_Pop.csv");
        this->testPeek(new structures::Heap<int>(), "Heap_Peek.csv");
        this->testPush(new structures::Heap<int>(), "Heap_Push1.csv");


    }


    void TwoListsTimeAnalysis::test()
    {
        this->testPush(new structures::PriorityQueueTwoLists<int>(), "TwoLists_Push.csv");
        this->testPop(new structures::PriorityQueueTwoLists<int>(), "TwoLists_Pop.csv");
        this->testPeek(new structures::PriorityQueueTwoLists<int>(), "TwoLists_Peek.csv");
    }



	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}


	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	
	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
	}


	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
	}


}