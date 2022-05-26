#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/array/array.h"
#include "../../structures/table/unsorted_sequence_table.h"
#include "../../file_log_consumer.h"
#include <fstream>;

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

	//UNIT testy

	TableInsertTest::TableInsertTest() : SimpleTest("Insert/Find/TryFind/Remove")
	{
	}

	void TableInsertTest::insertTest(structures::Table<int, int>* table)
	{
		logInfo("naplnenie 1-10 (key = data)");
		std::string hodnoty = "";
		for (int i = 1; i <= 10; i++)
		{
			table->insert(i, i);
			hodnoty += std::to_string(i);
			hodnoty += " ";


		}
		logInfo("INSERT vypis" + hodnoty);
		hodnoty = "";
		for (int i = 1; i <= 10; i++)
		{
			int found = table->find(i);
			hodnoty += std::to_string(found);
			hodnoty += " ";
		}
		logInfo("FIND vypis:" + hodnoty);
		hodnoty = "";
		logInfo("INSERT 11");
		table->insert(11, 11);
		for (int i = 1; i <= 11; i++)
		{
			int found = table->find(i);
			hodnoty += std::to_string(found);
			hodnoty += " ";
		}
		logInfo("after INSERT:" + hodnoty);
		logPass("11 na konci");
		table->remove(2);
		logInfo("REMOVE 2");

		hodnoty = "";
		for (int i = 1; i <= 11; i++)
		{
			if (i == 2) {
				i++;
			}
			int found = table->find(i);
			hodnoty += std::to_string(found);
			hodnoty += " ";
		}

		logInfo("after REMOVE:" + hodnoty);
		logInfo("kontrola TRYFIND 2");
		int dvojka = 2;
		SimpleTest::assertTrue(table->tryFind(2, dvojka) == false, "nenajdena");

		logInfo("INSERT 2");
		table->insert(2, 2);
		hodnoty = "";
		for (int i = 1; i <= 11; i++)
		{
			int found = table->find(i);
			hodnoty += std::to_string(found);
			hodnoty += " ";
		}
		logInfo("after INSERT:" + hodnoty);

	}

	void SSTableInsert::test()
	{
		structures::SortedSequenceTable<int, int>* ssTable = new structures::SortedSequenceTable<int, int>();
		insertTest(ssTable);
		delete ssTable;
	}



	void BSTreeInsert::test()
	{
		structures::BinarySearchTree<int, int>* bsTree = new structures::BinarySearchTree<int, int>();
		insertTest(bsTree);
		delete bsTree;
	}

	TableAssignTest::TableAssignTest() : SimpleTest("Assign/Equals")
	{
	}

	void TableAssignTest::assignTest(structures::Table<int, int>* table1, structures::Table<int, int>* table2) {
		logInfo("naplnenie TABLE1 1-10 (key = data)");
		std::string hodnoty = "";
		for (int i = 1; i <= 10; i++)
		{
			table1->insert(i, i);
			hodnoty += std::to_string(i);
			hodnoty += " ";
		}

		logInfo("TABLE1: " + hodnoty);

		logInfo("naplnenie TABLE2 11-20 (key = data)");
		hodnoty = "";
		for (int i = 11; i <= 20; i++)
		{
			table2->insert(i, i);
			hodnoty += std::to_string(i);
			hodnoty += " ";
		}

		logInfo("TABLE2: " + hodnoty);
		table1->assign(*table2);
		logInfo("ASSIGN");
		std::string hodnoty2 = "";
		for (int i = 11; i <= 20; i++)
		{
			table1->find(i);
			hodnoty2 += std::to_string(i);
			hodnoty2 += " ";
		}
		logInfo("TABLE1 after ASSIGN: " + hodnoty2);
		SimpleTest::assertTrue(hodnoty == hodnoty2, "rovnaju sa (==)");
		SimpleTest::assertTrue(table1->equals(*table2), "rovnaju sa (equals)");


	}


	void SSTableAssign::test()
	{
		structures::SortedSequenceTable<int, int>* ssTable1 = new structures::SortedSequenceTable<int, int>();
		structures::SortedSequenceTable<int, int>* ssTable2 = new structures::SortedSequenceTable<int, int>();
		assignTest(ssTable1, ssTable2);
		delete ssTable1;
		delete ssTable2;
	}



	void BSTreeAssign::test()
	{
		structures::BinarySearchTree<int, int>* bsTree1 = new structures::BinarySearchTree<int, int>();
		structures::BinarySearchTree<int, int>* bsTree2 = new structures::BinarySearchTree<int, int>();
		assignTest(bsTree1, bsTree2);
		delete bsTree1;
		delete bsTree2;
	}

	TablePerformanceTest::TablePerformanceTest() : SimpleTest("PerformanceTest")
	{
	}

	void TablePerformanceTest::tableTest(structures::Table<int, int>* table, char script, std::string file)
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
		structures::List<int>* keysArray = new structures::ArrayList<int>();
		message.append(&script);
		consumer->logMessage(structures::LogType::Info, message);
		srand(time(0));
		for (int i = 0; i < 100000; i++)
		{
			int random = rand() % 100 + 1;
			if (random <= insert) {
				int key = rand() % 100000;
				while (table->containsKey(key)) {
					key = rand() % 100000 + 1;
				}
				keysArray->add(key);
				startStopwatch();
				table->insert(key, i);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(table->size()));
			}
			else if (insert < random && random <= insert + remove) {
				if (!table->isEmpty() || !keysArray->isEmpty()) {
					int key = keysArray->at(0);
					keysArray->removeAt(0);
					startStopwatch();
					table->remove(key);
					stopStopwatch();
					consumer->logDuration(0, getElapsedTime(), "remove ; " + std::to_string(table->size()));
				}
			}
			else {
				if (!table->isEmpty() || !keysArray->isEmpty()) {
					int key = rand() % 100000 + 1;
					int data;
					startStopwatch();
					table->tryFind(key, data);
					stopStopwatch();
					consumer->logDuration(0, getElapsedTime(), "tryFind ; " + std::to_string(table->size()));
				}
			}

		}
		delete keysArray;
		delete consumer;
	}



	void SSTablePerformanceTest::test()
	{
		char script = 'A';
		for (int i = 0; i < 3; i++)
		{
			structures::Table<int, int>* ssTable = new structures::SortedSequenceTable<int, int>();
			std::string file = "SSTable";
			file.append(&script);
			this->tableTest(ssTable, script, file + ".csv");
			script++;
			delete ssTable;
		}

	}


	void BSTreePerformanceTest::test()
	{
		char script = 'A';
		for (int i = 0; i < 3; i++)
		{
			structures::Table<int, int>* bsTree = new structures::BinarySearchTree<int, int>();
			std::string file = "BSTree";
			file.append(&script);
			this->tableTest(bsTree, script, file + ".csv");
			script++;
			delete bsTree;
		}
	}



	SSTableTestTimeComplexityInsert::SSTableTestTimeComplexityInsert() : SimpleTest("SSTableTestTimeComplexityInsert")
	{
	}
	void SSTableTestTimeComplexityInsert::test()
	{
		structures::Table<int, int>* newSSTable = new structures::SortedSequenceTable<int, int>();
		structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("SSTableTestTimeComplexityInsert");

		int key1;
		int key2;
		int data;

		int whileSize = 1;
		srand(time(NULL));

		while (whileSize <= 100) {
			for (int i = 0; i < 1000 * whileSize; i++) {
				key1 = rand() % 100000 + 1;
				while (newSSTable->containsKey(key1)) {
					key1 = rand() % 100000 + 1;
				}
				newSSTable->insert(key1, i);

			}
			for (int i = 0; i < 1000; i++) {
				data = rand() % 100 + 1;
				key2 = rand() % 100000 + 1;
				while (newSSTable->containsKey(key2)) {
					key2 = rand() % 100000 + 1;
				}
				startStopwatch();
				newSSTable->insert(key2, data);
				stopStopwatch();
				fileLog->logDuration(0, getElapsedTime(), std::to_string(newSSTable->size()));
			}
			whileSize++;
		}


		delete newSSTable;
		delete fileLog;

		logPass("SSTableTestTimeComplexityInsert succesfully finished");

	}


	SSTableTestTimeComplexityRemove::SSTableTestTimeComplexityRemove() : SimpleTest("SSTableTestTimeComplexityRemove")
	{
	}
	void SSTableTestTimeComplexityRemove::test()
	{
		structures::Table<int, int>* newSSTable = new structures::SortedSequenceTable<int, int>();
		structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("SSTableTestTimeComplexityRemove");
		structures::List<int>* keysArray = new structures::ArrayList<int>();
		int key1;
		int key2;
		int data;

		int whileSize = 1;
		srand(time(NULL));

		while (whileSize <= 100) {
			for (int i = 0; i < 1000 * whileSize; i++) {
				key1 = rand() % 100000 + 1;
				while (newSSTable->containsKey(key1)) {
					key1 = rand() % 100000 + 1;
				}
				keysArray->add(key1);
				newSSTable->insert(key1, i);
			}
			for (int i = 0; i < 1000; i++) {

				key2 = keysArray->at(1);
				keysArray->removeAt(1);
				startStopwatch();
				newSSTable->remove(key2);
				stopStopwatch();
				fileLog->logDuration(0, getElapsedTime(), std::to_string(newSSTable->size()));
			}
			whileSize++;
		}


		delete newSSTable;
		delete fileLog;
		delete keysArray;

		logPass("SSTableTestTimeComplexityRemove succesfully finished");

	}


	SSTableTestTimeComplexityTryFind::SSTableTestTimeComplexityTryFind() : SimpleTest("SSTableTestTimeComplexityTryFind")
	{
	}
	void SSTableTestTimeComplexityTryFind::test()
	{
		structures::Table<int, int>* newSSTable = new structures::SortedSequenceTable<int, int>();
		structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("SSTableTestTimeComplexityTryFind");
		structures::List<int>* keysArray = new structures::ArrayList<int>();

		int key1;
		int key2;
		int data;

		int whileSize = 1;
		srand(time(NULL));

		while (whileSize <= 100) {
			for (int i = 0; i < 1000 * whileSize; i++) {
				key1 = rand() % 100000 + 1;
				while (newSSTable->containsKey(key1)) {
					key1 = rand() % 100000 + 1;
				}
				keysArray->add(key1);
				newSSTable->insert(key1, i);

			}
			for (int i = 0; i < 1000; i++) {
				data = rand() % 100 + 1;
				//key2 = rand() % 100000 + 1;

				key2 = keysArray->at(1);
				keysArray->removeAt(1);
				startStopwatch();
				newSSTable->insert(key2, data);
				stopStopwatch();
				fileLog->logDuration(0, getElapsedTime(), std::to_string(newSSTable->size()));
			}
			whileSize++;
		}


		delete newSSTable;
		delete fileLog;
		delete keysArray;


		logPass("SSTableTestTimeComplexityTryFind succesfully finished");

	}

	BSTreeTestTimeComplexityInsert::BSTreeTestTimeComplexityInsert() : SimpleTest("BSTreeTestTimeComplexityInsert")
	{
	}
	void BSTreeTestTimeComplexityInsert::test()
	{
		structures::Table<int, int>* newBSTree = new structures::BinarySearchTree<int, int>();
		structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("SSTableTestTimeComplexityInsert");

		int key1;
		int key2;
		int data;

		int whileSize = 1;
		srand(time(NULL));

		while (whileSize <= 100) {
			for (int i = 0; i < 1000 * whileSize; i++) {
				key1 = rand() % 100000 + 1;
				while (newBSTree->containsKey(key1)) {
					key1 = rand() % 100000 + 1;
				}
				newBSTree->insert(key1, i);

			}
			for (int i = 0; i < 1000; i++) {
				data = rand() % 100 + 1;
				key2 = rand() % 100000 + 1;
				while (newBSTree->containsKey(key2)) {
					key2 = rand() % 100000 + 1;
				}
				startStopwatch();
				newBSTree->insert(key2, data);
				stopStopwatch();
				fileLog->logDuration(0, getElapsedTime(), std::to_string(newBSTree->size()));
			}
			whileSize++;
		}


		delete newBSTree;
		delete fileLog;

		logPass("SSTableTestTimeComplexityInsert succesfully finished");

	}


	BSTreeTestTimeComplexityRemove::BSTreeTestTimeComplexityRemove() : SimpleTest("BSTreeTestTimeComplexityRemove")
	{
	}
	void BSTreeTestTimeComplexityRemove::test()
	{
		structures::Table<int, int>* newBSTree = new structures::BinarySearchTree<int, int>();
		structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("BSTreeTestTimeComplexityRemove");
		structures::List<int>* keysArray = new structures::ArrayList<int>();
		int key1;
		int key2;
		int data;

		int whileSize = 1;
		srand(time(NULL));

		while (whileSize <= 100) {
			for (int i = 0; i < 1000 * whileSize; i++) {
				key1 = rand() % 100000 + 1;
				while (newBSTree->containsKey(key1)) {
					key1 = rand() % 100000 + 1;
				}
				keysArray->add(key1);
				newBSTree->insert(key1, i);
			}
			for (int i = 0; i < 1000; i++) {

				key2 = keysArray->at(1);
				keysArray->removeAt(1);
				startStopwatch();
				newBSTree->remove(key2);
				stopStopwatch();
				fileLog->logDuration(0, getElapsedTime(), std::to_string(newBSTree->size()));
			}
			whileSize++;
		}


		delete newBSTree;
		delete fileLog;
		delete keysArray;

		logPass("SSTableTestTimeComplexityRemove succesfully finished");

	}


	BSTreeTestTimeComplexityTryFind::BSTreeTestTimeComplexityTryFind() : SimpleTest("BSTreeTestTimeComplexityTryFind")
	{
	}
	void BSTreeTestTimeComplexityTryFind::test()
	{
		structures::Table<int, int>* newBSTree = new structures::BinarySearchTree<int, int>();
		structures::FileLogConsumer* fileLog = new structures::FileLogConsumer("BSTreeTestTimeComplexityTryFind");
		structures::List<int>* keysArray = new structures::ArrayList<int>();

		int key1;
		int key2;
		int data;

		int whileSize = 1;
		srand(time(NULL));

		while (whileSize <= 100) {
			for (int i = 0; i < 1000 * whileSize; i++) {
				key1 = rand() % 100000 + 1;
				while (newBSTree->containsKey(key1)) {
					key1 = rand() % 100000 + 1;
				}
				keysArray->add(key1);
				newBSTree->insert(key1, i);

			}
			for (int i = 0; i < 1000; i++) {
				data = rand() % 100 + 1;
				//key2 = rand() % 100000 + 1;

				key2 = keysArray->at(1);
				keysArray->removeAt(1);
				startStopwatch();
				newBSTree->insert(key2, data);
				stopStopwatch();
				fileLog->logDuration(0, getElapsedTime(), std::to_string(newBSTree->size()));
			}
			whileSize++;
		}


		delete newBSTree;
		delete fileLog;
		delete keysArray;

		logPass("BSTreeTestTimeComplexityTryFind succesfully finished");

	}




	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
		addTest(new BSTreeInsert());
		addTest(new BSTreeAssign());
		addTest(new BSTreePerformanceTest());
		addTest(new BSTreeTestTimeComplexityInsert());
		addTest(new BSTreeTestTimeComplexityRemove());
		addTest(new BSTreeTestTimeComplexityTryFind());
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

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
		addTest(new SSTableInsert());
		addTest(new SSTableAssign());
		addTest(new SSTablePerformanceTest());
		addTest(new SSTableTestTimeComplexityInsert());
		addTest(new SSTableTestTimeComplexityRemove());
		addTest(new SSTableTestTimeComplexityTryFind());
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
}