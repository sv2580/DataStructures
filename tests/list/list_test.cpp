#include "list_test.h"
#include "../../file_log_consumer.h"

namespace tests
{
	// ListTestInterface:

	ListTestInterface::ListTestInterface(std::string name) :
		SimpleTest(std::move(name))
	{
	}

	void ListTestInterface::test()
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

	// ArrayListTestInterface:

	ArrayListTestInterface::ArrayListTestInterface() :
		ListTestInterface("Interface")
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

	structures::List<int>* ArrayListTestInterface::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

	DoubleLinkedListTestInterface::DoubleLinkedListTestInterface() : ListTestInterface("Interface")
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

	structures::List<int>* DoubleLinkedListTestInterface::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}


	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

	// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
		addTest(new ArrayListEquals());
		addTest(new ArrayListAddInsert());
		addTest(new ArrayListAssign());
		addTest(new ArrayListCopy());
		addTest(new ArrayListClear());
		addTest(new ArrayListRemove());
		addTest(new ArrayListPerformanceTest());
		addTest(new ArrayListTimeAnalysis());
	}

	// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		//addTest(new LinkedListTestInterface());
	}

	DoubleLinkedListTestOverall::DoubleLinkedListTestOverall() :
		ComplexTest("DoubleLinkedList")
	{
		addTest(new DoubleLinkedListTestInterface());
		addTest(new DoubleLinkedListEquals());
		addTest(new DoubleLinkedListAddInsert());
		addTest(new DoubleLinkedListAssign());
		addTest(new DoubleLinkedListCopy());
		addTest(new DoubleLinkedListClear());
		addTest(new DoubleLinkedListRemove());

		addTest(new DoubleLinkedListPerformanceTest());
		addTest(new DoubleLinkedListTimeAnalysis());
	}

	// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
		addTest(new DoubleLinkedListTestOverall());
	}

	ListPerformanceTest::ListPerformanceTest() : SimpleTest("Performance test")
	{
	}

	void ListPerformanceTest::test()
	{
	}

	void ListPerformanceTest::testList(structures::List<int>* list, char script, std::string file, int count)
	{
		int insert, removeAt, at, getIndexOf;
		switch (script)
		{
		case 'A':
			insert = 20;
			removeAt = 20;
			at = 50;
			getIndexOf = 10;
			break;
		case 'B':
			insert = 35;
			removeAt = 35;
			at = 20;
			getIndexOf = 10;
			break;
		case 'C':
			insert = 45;
			removeAt = 45;
			at = 5;
			getIndexOf = 5;
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
				int index;
				if (!list->isEmpty()) {
					 index = rand() % list->size();
				}
				else
					 index = 0;

				startStopwatch();
				list->insert(index, index);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(list->size()));

			}
			else if (insert < random && random <= insert + removeAt) {
				if (!list->isEmpty()) {
					int index = rand() % list->size();
					startStopwatch();
					list->removeAt(index);
					stopStopwatch();
					consumer->logDuration(0, getElapsedTime(), "removeAt ; " + std::to_string(list->size()));
				}
			}
			else if (insert + removeAt < random && random <= insert + removeAt + at) {
				if (!list->isEmpty()) {
					int index = rand() % list->size();
					startStopwatch();
					list->at(index);
					stopStopwatch();
					consumer->logDuration(0, getElapsedTime(), "at ; " + std::to_string(list->size()));
				}
			}
			else {
				if (!list->isEmpty()) {

					int random = rand() % list->size();
					startStopwatch();
					list->getIndexOf(random);
					stopStopwatch();
					consumer->logDuration(0, getElapsedTime(), "getIndexOf ; " + std::to_string(list->size()));
				}
			}

		}
		
		delete consumer;
	}



	void ArrayListPerformanceTest::test()
	{
		char script = 'A';
		for (int i = 0; i < 3; i++)
		{
			structures::List<int>* list = new structures::ArrayList<int>();
			std::string file = "ArrayList";
			file.append(&script);
			this->testList(list, script, file + ".csv", 100000);
			script++;
			delete list;
		}
	}


	void DoubleLinkedListPerformanceTest::test()
	{
		char script = 'A';
		for (int i = 0; i < 3; i++)
		{
			structures::List<int>* list = new structures::DoubleLinkedList<int>();
			std::string file = "DoubleLinkedList";
			file.append(&script);
			this->testList(list, script, file + ".csv", 100000);
			script++;
			delete list;
		}
	}


//




	ListTimeAnalysis::ListTimeAnalysis() : SimpleTest("TimeAnalysis")
	{
	}

	void ListTimeAnalysis::testListAt(structures::List<int>* list, std::string file)
	{
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov budee v zozname
			int size = list->size();
			for (int j = 0; j < (1000 * i) - size; j++) //naplnenie zoznamu tisic*i prvkov
			{
				list->add(i);
			}
			for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
			{
				int index = rand() % list->size();
				startStopwatch();
				list->at(index);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "at ; " + std::to_string(list->size()));
			}
		}
		delete consumer;
		delete list;

	}

	void ListTimeAnalysis::testListRemoveAt(structures::List<int>* list, std::string file)
	{
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov budee v zozname
			int size = list->size();
			for (int j = 0; j <  (1000 * i) - size; j++) //naplnenie zoznamu tisic*i prvkov
			{

				list->add(i);
			}
			for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
			{
				int index = rand() % list->size();
				startStopwatch();
				list->removeAt(index);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "removeAt ; " + std::to_string(list->size()));
			}
		}
		delete consumer;
		delete list;

	}

	void ListTimeAnalysis::testInsert(structures::List<int>* list, std::string file)
	{
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		for (int i = 1; i <= 100; i++) { //pocet kolko * tisic prvkov budee v zozname
			int size = list->size();
			for (int j = 0; j < (1000 * i) - size; j++) //naplnenie zoznamu tisic*i prvkov
			{
				list->add(i);
			}
			for (int j = 0; j < 100; j++) //vykonanie operacie 100 krat pre danu velkost
			{
				int index = rand() % list->size();
				startStopwatch();
				list->insert(j,index);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "insert ; " + std::to_string(list->size()));
			}
		}
		delete consumer;
		delete list;
	}


	void ArrayListTimeAnalysis::test()
	{
		this->testListAt(new structures::ArrayList<int>(), "AL_Time_At.csv");
		this->testListRemoveAt(new structures::ArrayList<int>(), "AL_Time_RemoveAt.csv");
		this->testInsert(new structures::ArrayList<int>(), "AL_Time_Insert.csv");


	}


	void DoubleLinkedListTimeAnalysis::test()
	{
		this->testListAt(new structures::DoubleLinkedList<int>(), "DLL_Time_At.csv");
		this->testListRemoveAt(new structures::DoubleLinkedList<int>(), "DLL_Time_RemoveAt.csv");
		this->testInsert(new structures::DoubleLinkedList<int>(), "DLL_Time_Insert.csv");
	}


	//assign,equals,at,add,insert,remove,clear



	void ListAssign::test()
	{
	}

	void ListAssign::testAssign(structures::List<int>* list, structures::List<int>* list2)
	{
		logInfo("Testing assing values to first list and assigning to second");

		for (size_t i = 0; i < 25; i++)
		{
			list->add(i);
		}
		list2->assign(*list);
		if (list2->equals(*list))
			logPass("Lists are equal");
		else
			logError("Lists are not equal");
	}

	ListAssign::ListAssign() : SimpleTest("assign")
	{
	}


	void ListEquals::test()
	{
	}

	void ListEquals::testEquals(structures::List<int>* list, structures::List<int>* list2)
	{
		logInfo("Adding random values to lists");
		srand(0);
		std::string l1 = "";
		std::string l2 = "";

		for (size_t i = 0; i < 10; i++)
		{
			list->add(rand() % 10);
			list2->add(rand() % 10);
			l1 += std::to_string(list->at(i));
			l2 += std::to_string(list2->at(i));
		}

		for (size_t i = 0; i < 10; i++)
		{
			list->add(rand() % 10);
			list2->add(rand() % 10);
			l1 += std::to_string(list->at(i));
			l2 += std::to_string(list2->at(i));
		}

		logInfo(l1);
		logInfo(l2);
		if (list2->equals(*list))
			logPass("Lists are equal");
		else
			logError("Lists are not equal");
		logInfo("Adding assigning values from list1 to list2");
		list2->assign(*list);
		if (list2->equals(*list))
			logPass("Lists are equal");
		else
			logError("Lists are not equal");
	}

	ListEquals::ListEquals() : SimpleTest("Equals")
	{
	}

	void ListAddInsert::test()
	{
	}

	ListAddInsert::ListAddInsert() : SimpleTest("Add&Insert")
	{
	}

	void ListAddInsert::testAddInsert(structures::List<int>* list)
	{

		logInfo("Adding random values to list");
		srand(0);
		std::string l1 = "";

		for (size_t i = 0; i < 10; i++)
		{
			list->add(i+1);
		}

		for (size_t i = 0; i < 10; i++)
		{
			l1 += std::to_string(list->at(i));
		}


		logInfo(l1);
		l1 = "";
		logInfo("Inserting 0 to list - last place, end, middle");
		list->insert(0, 0);
		list->insert(0, 5);
		list->insert(0, 12);
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += std::to_string(list->at(i));
		}
		logInfo(l1);
		logPass("Test compilled");
	}



	void ListRemove::test()
	{
	}

	void ListRemove::testRemove(structures::List<int>* list)
	{
		logInfo("Adding random values to list");
		srand(0);
		std::string l1 = "";

		for (size_t i = 0; i < 10; i++)
		{
			list->insert(rand() % 10,list->size() - 1);
			l1 += std::to_string(list->at(i));
		}

		logInfo(l1);
		l1 = "";
		logInfo("Deleting values from list - last place, end, middle");
		list->removeAt(0);
		list->removeAt(3);
		list->removeAt(7);
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += std::to_string(list->at(i));
		}
		logInfo(l1);
		l1 = "";

		logInfo("Trying to remove value that is on the 0 index");
		list->tryRemove(list->at(0));
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += std::to_string(list->at(i));
		}
		logInfo(l1);
		logPass("Test compilled");
	}

	ListRemove::ListRemove() : SimpleTest("Remove")
	{
	}


	void ListClear::test()
	{
	}

	void ListClear::testClear(structures::List<int>* list)
	{
		logInfo("Adding random values to list");
		srand(0);
		std::string l1 = "";

		for (size_t i = 0; i < 10; i++)
		{
			list->add(rand() % 10);
			l1 += std::to_string(list->at(i));
		}

		logInfo(l1);
		logInfo("Clearing list and trying to writing it out");
		list->clear();
		l1 = "";
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += std::to_string(list->at(i));
		}
		logInfo(l1);
		logPass("Test compilled");

	}

	ListClear::ListClear() : SimpleTest("Clear")
	{

	}


	void DoubleLinkedListAssign::test()
	{
		structures::List<int>* list = new structures::DoubleLinkedList<int>();
		structures::List<int>* list2 = new structures::DoubleLinkedList<int>();

		this->testAssign(list, list2);

		delete list;
		delete list2;
	}

	void DoubleLinkedListEquals::test()
	{
		structures::List<int>* list = new structures::DoubleLinkedList<int>();
		structures::List<int>* list2 = new structures::DoubleLinkedList<int>();

		this->testEquals(list, list2);

		delete list;
		delete list2;
	}


	void DoubleLinkedListAddInsert::test()
	{
		structures::List<int>* list = new structures::DoubleLinkedList<int>();

		this->testAddInsert(list);

		delete list;
	}


	void DoubleLinkedListRemove::test()
	{
		structures::List<int>* list = new structures::DoubleLinkedList<int>();

		this->testRemove(list);

		delete list;
	}


	void DoubleLinkedListClear::test()
	{
		structures::List<int>* list = new structures::DoubleLinkedList<int>();

		this->testClear(list);

		delete list;
	}


	void ArrayListAssign::test()
	{
		structures::List<int>* list = new structures::ArrayList<int>();
		structures::List<int>* list2 = new structures::ArrayList<int>();

		this->testAssign(list, list2);

		delete list;
		delete list2;
	}


	void ArrayListEquals::test()
	{
		structures::List<int>* list = new structures::ArrayList<int>();
		structures::List<int>* list2 = new structures::ArrayList<int>();

		this->testEquals(list, list2);

		delete list;
		delete list2;
	}


	void ArrayListAddInsert::test()
	{
		structures::List<int>* list = new structures::ArrayList<int>();

		this->testAddInsert(list);

		delete list;
	}


	void ArrayListRemove::test()
	{
		structures::List<int>* list = new structures::ArrayList<int>();

		this->testRemove(list);

		delete list;
	}


	void ArrayListClear::test()
	{
		structures::List<int>* list = new structures::ArrayList<int>();

		this->testClear(list);

		delete list;
	}



	DoubleLinkedListCopy::DoubleLinkedListCopy() : SimpleTest("Copy")
	{
	}

	void DoubleLinkedListCopy::test()
	{

		logInfo("Testing copy, adding values to first list and copying the first list to second");
		structures::DoubleLinkedList<int>* list = new structures::DoubleLinkedList<int>();

		for (size_t i = 0; i < 25; i++)
		{
			list->add(i);
		}
		structures::DoubleLinkedList<int>* list2 = new structures::DoubleLinkedList<int>(*list);

		if (list2->equals(*list))
			logPass("Lists are equal");
		else
			logError("Lists are not equal");

		delete list;
		delete list2;
	}



	ArrayListCopy::ArrayListCopy() : SimpleTest("Copy")
	{
	}

	void ArrayListCopy::test()
	{

		logInfo("Testing copy, adding values to first list and copying the first list to second");
		structures::ArrayList<int>* list = new structures::ArrayList<int>();

		for (size_t i = 0; i < 25; i++)
		{
			list->add(i);
		}
		structures::ArrayList<int>* list2 = new structures::ArrayList<int>(*list);

		if (list->equals(*list2))
			logPass("Lists are equal");
		else
			logError("Lists are not equal");

		delete list;
		delete list2;
	}






}