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
    TableTestInterface::TableTestInterface() : SimpleTest("Interface")
    {
    }

    void TableTestInterface::test()
    {
        int x = 0;
        structures::Table<int, int> *table = this->makeTable();
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

    TableTestOverall::TableTestOverall() : ComplexTest("Table")
    {
        addTest(new BinarySearchTreeTestOverall());
        // addTest(new HashTableTestOverall());
        // addTest(new LinkedTableTestOverall());
        addTest(new SortedSequenceTableTestOverall());
        // addTest(new TreapTestOverall());
        // addTest(new UnsortedSequenceTableTestOverall());
    }

    structures::Table<int, int> *BinarySearchTreeTestInterface::makeTable()
    {
        return new structures::BinarySearchTree<int, int>();
    }

    structures::Table<int, int> *SortedSequenceTableTestInterface::makeTable()
    {
        return new structures::SortedSequenceTable<int, int>();
    }

    BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() : ComplexTest("BinarySearchTree")
    {
        addTest(new BinarySearchTreeTestInterface());
    }

    SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() : ComplexTest("SortedSequenceTable")
    {
        addTest(new SortedSequenceTableTestInterface());
    }

    TablePerformanceTest::TablePerformanceTest() : SimpleTest("PerformanceTest")
    {
    }

    void TablePerformanceTest::testTable(structures::Table<int, int> *table, char script, std::string file, int count)
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
        structures::FileLogConsumer *consumer = new structures::FileLogConsumer(file);
        std::string message = "Testing script ";
        message.append(&script);
        consumer->logMessage(structures::LogType::Info, message);
        srand(time(0));
        for (int i = 0; i < count; i++)
        {
            int random = rand() % 100 + 1;
            if (random <= insert)
            {
                int key = rand() % count;
                startStopwatch();
                table->insert(key, i);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(table->size()));
            }
            else if (insert < random && random <= insert + remove)
            {
                if (!table->isEmpty())
                {
                    int key = rand() % count;

                    startStopwatch();
                    table->remove(key);
                    stopStopwatch();
                    consumer->logDuration(0, getElapsedTime(), "remove ; " + std::to_string(table->size()));
                }
            }
            else
            {
                int data;
                int key = rand() % count;
                startStopwatch();
                table->tryFind(key,data);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "tryFind ; " + std::to_string(table->size()));
            }
        }

        delete consumer;
    }

    void SortedSequenceTablePerformanceTest::test()
    {
        char script = 'A';
        for (int i = 0; i < 3; i++)
        {
            structures::Table<int, int> *table = new structures::SortedSequenceTable<int, int>();
            std::string file = "SortedSequenceTable";
            file.append(&script);
            this->testTable(table, script, file + ".csv", 100000);
            script++;
            delete table;
        }
    }

    void BinarySearchTreePerformanceTest::test()
    {
        char script = 'A';
        for (int i = 0; i < 3; i++)
        {
            structures::Table<int, int> *table = new structures::BinarySearchTree<int, int>();
            std::string file = "BinarySearchTree";
            file.append(&script);
            this->testTable(table, script, file + ".csv", 100000);
            script++;
            delete table;
        }
    }

    TableTimeAnalysis::TableTimeAnalysis() : SimpleTest("TimeAnalysis")
    {
    }

    void TableTimeAnalysis::testInsert(structures::Table<int, int> *table, std::string file)
    {
        structures::FileLogConsumer *consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++)
        { // pocet kolko * tisic prvkov bude v queue
            int size = table->size();
            for (int j = 0; j < (1000 * i) - size; j++) // naplnenie queue tisic*i prvkov
            {
                table->insert(table->size(), j);
            }
            for (int j = 0; j < 100; j++) // vykonanie operacie 100 krat pre danu velkost
            {
                startStopwatch();
                table->insert(table->size(), j);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(table->size()));
            }
        }
        delete consumer;
        delete table;
    }

    void TableTimeAnalysis::testRemove(structures::Table<int, int> *table, std::string file)
    {
        structures::FileLogConsumer *consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++)
        { // pocet kolko * tisic prvkov bude v queue
            int size = table->size();
            for (int j = 0; j < (1000 * i) - size; j++) // naplnenie queue tisic*i prvkov
            {
                table->insert(table->size(), j);
            }
            for (int j = 0; j < 100; j++) // vykonanie operacie 100 krat pre danu velkost
            {
                int key = rand() % table->size();
                startStopwatch();
                table->remove(key);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "remove ; " + std::to_string(table->size()));
            }
        }
        delete consumer;
        delete table;
    }

    void TableTimeAnalysis::testTryFind(structures::Table<int, int> *table, std::string file)
    {
        structures::FileLogConsumer *consumer = new structures::FileLogConsumer(file);
        for (int i = 1; i <= 100; i++)
        { // pocet kolko * tisic prvkov bude v queue
            int size = table->size();
            for (int j = 0; j < (1000 * i) - size; j++) // naplnenie queue tisic*i prvkov
            {
                table->insert(table->size(), j);
            }
            for (int j = 0; j < 100; j++) // vykonanie operacie 100 krat pre danu velkost
            {
                int key = rand() % table->size();
                int data;
                startStopwatch();
                table->tryFind(key, data);
                stopStopwatch();
                consumer->logDuration(0, getElapsedTime(), "tryFind ; " + std::to_string(table->size()));
            }
        }
        delete consumer;
        delete table;
    }

    void SortedSequenceTableTimeAnalysis::test()
    {
        this->testInsert(new structures::SortedSequenceTable<int, int>(), "Heap_Insert.csv");
        this->testRemove(new structures::SortedSequenceTable<int, int>, "Heap_Remove.csv");
        this->testTryFind(new structures::SortedSequenceTable<int, int>, "Heap_TryFind.csv");
    }

    void BinarySearchTreeTimeAnalysis::test()
    {
        this->testTryFind(new structures::BinarySearchTree<int, int>, "BinarySearchTree_TryFind.csv");
        this->testInsert(new structures::BinarySearchTree<int, int>, "BinarySearchTree_Insert.csv");
        this->testRemove(new structures::BinarySearchTree<int, int>, "BinarySearchTree_Remove.csv");
    }

    structures::Table<int, int> *HashTableTestInterface::makeTable()
    {
        return new structures::HashTable<int, int>();
    }

    structures::Table<int, int> *LinkedTableTestInterface::makeTable()
    {
        return new structures::LinkedTable<int, int>();
    }

    structures::Table<int, int> *TreapTestInterface::makeTable()
    {
        return new structures::Treap<int, int>();
    }

    structures::Table<int, int> *UnsortedSequenceTableTestInterface::makeTable()
    {
        return new structures::UnsortedSequenceTable<int, int>();
    }

    HashTableTestOverall::HashTableTestOverall() : ComplexTest("HashTable")
    {
        addTest(new HashTableTestInterface());
    }

    LinkedTableTestOverall::LinkedTableTestOverall() : ComplexTest("LinkedTable")
    {
        addTest(new LinkedTableTestInterface());
    }

    TreapTestOverall::TreapTestOverall() : ComplexTest("Treap")
    {
        addTest(new TreapTestInterface());
    }

    UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() : ComplexTest("UnsortedSequenceTable")
    {
        addTest(new UnsortedSequenceTableTestInterface());
    }

}