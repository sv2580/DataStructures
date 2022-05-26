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

	TableTestOverall::TableTestOverall() : ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		// addTest(new HashTableTestOverall());
		// addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		// addTest(new TreapTestOverall());
		// addTest(new UnsortedSequenceTableTestOverall());
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() : ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
		addTest(new BinarySearchClearTest());
		addTest(new BinarySearchTreeAssignTest());
		addTest(new BinarySearchTreeContainsKeyTest());
		addTest(new BinarySearchTreeEqualsTest());
		addTest(new BinarySearchTreeInsertTest());
		addTest(new BinarySearchTreeRemoveTest());
		addTest(new BinarySearchTreeTryAndFindTest());


		addTest(new BinarySearchTreePerformanceTest());
		addTest(new BinarySearchTreeTimeAnalysis());



	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() : ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
		addTest(new SortedSequenceTableClearTest());
		addTest(new SortedSequenceTableAssignTest());
		addTest(new SortedSequenceTableContainsKeyTest());
		addTest(new SortedSequenceTableEqualsTest());
		addTest(new SortedSequenceTableInsertTest());
		addTest(new SortedSequenceTableRemoveTest());
		addTest(new SortedSequenceTableTryAndFindTest());


		addTest(new SortedSequenceTablePerformanceTest());
		addTest(new SortedSequenceTableTimeAnalysis());
	}

	TablePerformanceTest::TablePerformanceTest() : SimpleTest("PerformanceTest")
	{
	}

	void TablePerformanceTest::testTable(structures::Table<int, int>* table, char script, std::string file, int count)
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
			remove = 40;
			tryFind = 20;
			break;
		}
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		std::string message = "Testing script ";
		message.append(&script);
		consumer->logMessage(structures::LogType::Info, message);
		srand(time(0));
		structures::ArrayList<int>* keyes = new structures::ArrayList<int>();

		for (int i = 0; i < count; i++)
		{
			int random = rand() % 100 + 1;
			if (random <= insert)
			{
				int key = rand() % count;
				while (table->containsKey(key)) {
					key = rand() % count;
				}
				keyes->add(key);

				startStopwatch();
				table->insert(key, i);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(table->size()));
			}
			else if (insert < random && random <= insert + remove)
			{
				if (!table->isEmpty())
				{
					int key = keyes->removeAt(rand() % keyes->size());

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
				table->tryFind(key, data);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "tryFind ; " + std::to_string(table->size()));
			}
		}
		delete keyes;
		delete consumer;
	}

	void SortedSequenceTablePerformanceTest::test()
	{
		char script = 'A';
		for (int i = 0; i < 2; i++)
		{
			structures::Table<int, int>* table = new structures::SortedSequenceTable<int, int>();
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
		for (int i = 0; i < 2; i++)
		{
			structures::Table<int, int>* table = new structures::BinarySearchTree<int, int>();
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

	void TableTimeAnalysis::testInsert(structures::Table<int, int>* table, std::string file)
	{
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		srand(time(0));


		for (int i = 1; i <= 1000; i++)
		{
			int size = table->size();
			for (int j = 0; j < (10 * i) - size; j++)
			{
				bool added = false;
				while (!added) {
					int key = rand() % 15000;
					if (!table->containsKey(key)) {
						table->insert(key, j);
						added = true;
					}
				}
			}
			for (int j = 0; j < 10; j++) // vykonanie operacie 100 krat pre danu velkost
			{
				bool added = false;
				while (!added) {
					int key = rand() % 15000;
					if (!table->containsKey(key)) {
						startStopwatch();
						table->insert(key, j);
						stopStopwatch();
						consumer->logDuration(0, getElapsedTime(), std::to_string(table->size()) + ";insert ");
						added = true;
					}					
				}
			}
		}
		delete consumer;
		delete table;
	}

	void TableTimeAnalysis::testRemove(structures::Table<int, int>* table, std::string file)
	{
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		int insert = 0;
		structures::ArrayList<int>* keyes = new structures::ArrayList<int>();
		for (int i = 1; i <= 1000; i++)
		{ // pocet kolko * tisic prvkov bude v queue
			int size = table->size();
			for (int j = 0; j < (10 * i) - size; j++) // naplnenie queue tisic*i prvkov
			{
				table->insert(insert, insert);
				insert++;
				keyes->add(insert);

			}
			for (int j = 0; j < 10; j++) // vykonanie operacie 100 krat pre danu velkost
			{
				int key = keyes->removeAt(rand() % keyes->size());
					startStopwatch();
					table->remove(key);
					stopStopwatch();

				consumer->logDuration(0, getElapsedTime(), std::to_string(table->size()) + ";remove ");
			}
		}
		delete consumer;
		delete table;
		delete keyes;

	}

	void TableTimeAnalysis::testTryFind(structures::Table<int, int>* table, std::string file)
	{
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		int insert = 0;

		for (int i = 1; i <= 1000; i++)
		{ // pocet kolko * 100 prvkov bude v queue
			int size = table->size();
			for (int j = 0; j < (10 * i) - size; j++) // naplnenie queue 100*i prvkov
			{
				table->insert(insert, insert);
				insert++;

			}
			for (int j = 0; j < 10; j++) // vykonanie operacie 100 krat pre danu velkost
			{
				int key = rand() % 10000;
				int data;

				startStopwatch();
				table->tryFind(key, data);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), std::to_string(table->size()) + ";tryFind ");
			}
			if (table->size() == 100000) {
				int here = 0;
			}
		}
		delete consumer;
		delete table;

	}

	void SortedSequenceTableTimeAnalysis::test()
	{
		this->testInsert(new structures::SortedSequenceTable<int, int>(), "SortedSequenceTable_Insert.csv");
		this->testRemove(new structures::SortedSequenceTable<int, int>(), "SortedSequenceTable_Remove.csv");
		this->testTryFind(new structures::SortedSequenceTable<int, int>(), "SortedSequenceTable_TryFind.csv");
	}

	void BinarySearchTreeTimeAnalysis::test()
	{
		this->testTryFind(new structures::BinarySearchTree<int, int>(), "BinarySearchTree_TryFind.csv");
		this->testInsert(new structures::BinarySearchTree<int, int>(), "BinarySearchTree_Insert.csv");
		this->testRemove(new structures::BinarySearchTree<int, int>(), "BinarySearchTree_Remove.csv");
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

	TableTryAndFindTest::TableTryAndFindTest() : SimpleTest("TryFindAndTry")
	{
	}

	void TableTryAndFindTest::testTryAndFind(structures::Table<int, int>* table)
	{
		logInfo("Inserting values into table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			table->insert(i, i);
			s = std::to_string(i) + "|" + std::to_string(i);
		}

		logInfo(s);

		logInfo("Testing find value with key 5");
		int returned = table->find(5);
		logInfo(std::to_string(returned));

		this->logInfo("Trying to find value with key 15");
		try {
			table->find(15);
		}
		catch (std::out_of_range) {
			logError("Key is not there");
		}

		this->logInfo("TryFind value with key 3");
		bool found = table->tryFind(3, returned);
		logInfo("TryFind:" + std::to_string(found));
		this->logInfo("TryFind value with key 15");
		found = table->tryFind(15, returned);
		logInfo("TryFind:" + std::to_string(found));
	}


	void SortedSequenceTableTryAndFindTest::test()
	{
		structures::Table<int, int>* table = new structures::SortedSequenceTable<int, int>();
		this->testTryAndFind(table);
		delete table;
	}


	void BinarySearchTreeTryAndFindTest::test()
	{
		structures::Table<int, int>* table = new structures::BinarySearchTree<int, int>();
		this->testTryAndFind(table);
		delete table;
	}


	TableInsertTest::TableInsertTest() : SimpleTest("Insert")
	{
	}

	void TableInsertTest::testInsert(structures::Table<int, int>* table)
	{
		logInfo("Inserting values into table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			int random = rand() % 10;
			table->insert(i, random);
			s = std::to_string(i) + " | " + std::to_string(random);
		}
		logInfo(s);

		logInfo("Getting values through foreach");

		s = "Key | Data";
		for (auto item : *table) {
			logInfo(s);
			s = std::to_string(item->getKey()) + "|" + std::to_string(item->accessData()) + "\n";
		}
		logInfo(s);

	}


	void SortedSequenceTableInsertTest::test()
	{
		structures::Table<int, int>* table = new structures::SortedSequenceTable<int, int>();
		this->testInsert(table);
		delete table;
	}


	void BinarySearchTreeInsertTest::test()
	{
		structures::Table<int, int>* table = new structures::BinarySearchTree<int, int>();
		this->testInsert(table);
		delete table;
	}


	TableRemoveTest::TableRemoveTest() : SimpleTest("Remove")
	{
	}

	void TableRemoveTest::testRemove(structures::Table<int, int>* table)
	{
		logInfo("Inserting values into table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			int random = rand() % 10;
			table->insert(i, random);
			s = std::to_string(i) + " | " + std::to_string(random);
		}
		logInfo(s);
		logInfo("Removing values with key 9, 4 and 0 from table");
		table->remove(9);
		table->remove(4);
		table->remove(0);

		s = "Key | Data";
		for (auto item : *table) {
			logInfo(s);
			s = std::to_string(item->getKey()) + "|" + std::to_string(item->accessData()) + "\n";
		}
		logInfo(s);

		this->logInfo("Trying to remove value with key 15");
		try {
			table->remove(15);
		}
		catch (std::logic_error) {
			logError("Key is not there");
		}

	}


	void SortedSequenceTableRemoveTest::test()
	{
		structures::Table<int, int>* table = new structures::SortedSequenceTable<int, int>();
		this->testRemove(table);
		delete table;
	}


	void BinarySearchTreeRemoveTest::test()
	{
		structures::Table<int, int>* table = new structures::BinarySearchTree<int, int>();
		this->testRemove(table);
		delete table;
	}


	TableContainsKeyTest::TableContainsKeyTest() : SimpleTest("ContainsKey")
	{
	}

	void TableContainsKeyTest::testContainsKey(structures::Table<int, int>* table)
	{
		logInfo("Inserting values into table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);

			table->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i);
		}
		logInfo(s);
		logInfo("Does table contains key 9: " + std::to_string(table->containsKey(9)));
		logInfo("Does table contains key 15: " + std::to_string(table->containsKey(15)));
	}


	void SortedSequenceTableContainsKeyTest::test()
	{
		structures::Table<int, int>* table = new structures::SortedSequenceTable<int, int>();
		this->testContainsKey(table);
		delete table;
	}


	void BinarySearchTreeContainsKeyTest::test()
	{
		structures::Table<int, int>* table = new structures::BinarySearchTree<int, int>();
		this->testContainsKey(table);
		delete table;
	}

	SortedSequenceTableAssignTest::SortedSequenceTableAssignTest() : SimpleTest("Assign")
	{
	}

	void SortedSequenceTableAssignTest::test()
	{
		structures::SortedSequenceTable<int, int>* table1 = new structures::SortedSequenceTable<int, int>();
		structures::SortedSequenceTable<int, int>* table2 = new structures::SortedSequenceTable<int, int>();

		logInfo("Inserting values into first table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			table1->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		s = "";
		logInfo("Assigning second table to the first");

		table2->assign(*table1);
		s = "Key | Data";
		for (auto item : *table2) {
			logInfo(s);
			s = std::to_string(item->getKey()) + "|" + std::to_string(item->accessData()) + "\n";
		}
		logInfo(s);

		delete table1;
		delete table2;
	}


	BinarySearchTreeAssignTest::BinarySearchTreeAssignTest() : SimpleTest("Assign")
	{
	}

	void BinarySearchTreeAssignTest::test()
	{
		structures::BinarySearchTree<int, int>* table1 = new structures::BinarySearchTree<int, int>();
		structures::BinarySearchTree<int, int>* table2 = new structures::BinarySearchTree<int, int>();

		logInfo("Inserting values into first table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			table1->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		s = "";
		logInfo("Assigning second table to the first");

		table2->assign(*table1);
		s = "Key | Data";
		for (auto item : *table2) {
			logInfo(s);
			s = std::to_string(item->getKey()) + "|" + std::to_string(item->accessData()) + "\n";
		}
		logInfo(s);

		delete table1;
		delete table2;
	}



	TableClear::TableClear() : SimpleTest("Clear")
	{
	}

	void TableClear::testClear(structures::Table<int, int>* table)
	{
		logInfo("Inserting values into first table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			table->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		s = "";
		logInfo("Clear table");
		table->clear();
		logInfo("Table size " + std::to_string(table->size()));

	}


	void SortedSequenceTableClearTest::test()
	{
		structures::Table<int, int>* table = new structures::SortedSequenceTable<int, int>();
		this->testClear(table);
		delete table;
	}



	void BinarySearchClearTest::test()
	{
		structures::Table<int, int>* table = new structures::BinarySearchTree<int, int>();
		this->testClear(table);
		delete table;
	}


	SortedSequenceTableEqualsTest::SortedSequenceTableEqualsTest() : SimpleTest("Equals")
	{
	}

	void SortedSequenceTableEqualsTest::test()
	{
		structures::SortedSequenceTable<int, int>* table1 = new structures::SortedSequenceTable<int, int>();
		structures::SortedSequenceTable<int, int>* table2 = new structures::SortedSequenceTable<int, int>();

		logInfo("Inserting values into first table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			table1->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		s = "";
		logInfo("Inserting values into second table");
		s = "Key | Data";
		for (int i = 0; i < 9; i++)
		{
			table2->insert(i, i);
			logInfo(s);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		logInfo("Are they equal: " + std::to_string(table1->equals(*table2)));

		logInfo("Inserting value 9,9 into second table");
		table2->insert(9, 9);
		logInfo("Are they equal: " + std::to_string(table1->equals(*table2)));


		delete table1;
		delete table2;
	}


	BinarySearchTreeEqualsTest::BinarySearchTreeEqualsTest() : SimpleTest("Equals")
	{
	}

	void BinarySearchTreeEqualsTest::test()
	{
		structures::BinarySearchTree<int, int>* table1 = new structures::BinarySearchTree<int, int>();
		structures::BinarySearchTree<int, int>* table2 = new structures::BinarySearchTree<int, int>();

		logInfo("Inserting values into first table");
		std::string s = "Key | Data";
		for (int i = 0; i < 10; i++)
		{
			logInfo(s);
			table1->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		s = "";
		logInfo("Inserting values into second table");
		s = "Key | Data";
		for (int i = 0; i < 9; i++)
		{
			logInfo(s);
			table2->insert(i, i);
			s = std::to_string(i) + " | " + std::to_string(i) + "\n";
		}
		logInfo(s);
		logInfo("Are they equal: " + std::to_string(table1->equals(*table2)));


		logInfo("Inserting value 9,9 into second table");
		table2->insert(9, 9);
		logInfo("Are they equal: " + std::to_string(table1->equals(*table2)));

		delete table1;
		delete table2;
	}


}