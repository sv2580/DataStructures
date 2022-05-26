#include "list_test.h"

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

	ArrayListTestAddRemove::ArrayListTestAddRemove() :
		SimpleTest("ArrayList test add and remove")
	{
	}
	void ArrayListTestAddRemove::test()
	{
		structures::List<int>* testAAR = new structures::ArrayList<int>();
		for (int i = 0; i < 10; i++) {
			testAAR->add(5 + i);

		}

		SimpleTest::assertTrue(testAAR->size() == (10), "ArrayList::size() plny");
		
			testAAR->removeAt(4);


		SimpleTest::assertTrue(testAAR->size() == (9), "ArrayList::size() o jeden menej");
		std::string vypis = "";
		/*for (int i = 0; i < 9; i++) {
			vypis = std::to_string(testAAR->at(i));

		}*/
		vypis = std::to_string(testAAR->at(0));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(1));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(2));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(3));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(4));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(5));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(6));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(7));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(8));
		SimpleTest::logInfo(vypis);
		
		
		testAAR->insert(8, 4);

		SimpleTest::assertTrue(testAAR->size() == (10), "ArrayList::size() plny na 4 8");
		vypis = std::to_string(testAAR->at(0));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(1));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(2));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(3));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(4));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(5));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(6));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(7));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(8));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(9));
		SimpleTest::logInfo(vypis);
		delete testAAR;
	}


	ArrayListTestEquals::ArrayListTestEquals() :
		SimpleTest("ArrayList test equals")
	{
	}
	void ArrayListTestEquals::test()
	{
		structures::List<int>* testE1 = new structures::ArrayList<int>();
		for (int i = 0; i < 10; i++) {
			testE1->add(1 + i*2);

		}

		structures::List<int>* testE2 = new structures::ArrayList<int>();
		for (int i = 0; i < 10; i++) {
			testE2->add(5 + i);

		}

		SimpleTest::assertTrue(testE2->equals(*testE1) == false, "ArrayList::equals() nerovnaju sa");
		testE2->assign(*testE1);

		SimpleTest::assertTrue(testE2->equals(*testE1) == true, "ArrayList::equals() rovnaju sa");

		delete testE1;
		delete testE2;
	}

// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

// DoubleLinkedListTestInterface:

	DoubleLinkedListTestInterface::DoubleLinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* DoubleLinkedListTestInterface::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

	DoubleLinkedListTestAddRemove::DoubleLinkedListTestAddRemove() :
		SimpleTest("DoubleLinkedList test add and remove")
	{
	}
	void DoubleLinkedListTestAddRemove::test()
	{
		structures::List<int>* testAAR = new structures::DoubleLinkedList<int>();
		for (int i = 0; i < 10; i++) {
			testAAR->add(5 + i);

		}

		SimpleTest::assertTrue(testAAR->size() == (10), "DoubleLinkedList::size() plny");

		testAAR->removeAt(4);


		SimpleTest::assertTrue(testAAR->size() == (9), "DoubleLinkedList::size() o jeden menej");

		std::string vypis = "";
		/*for (int i = 0; i < 9; i++) {
			vypis = std::to_string(testAAR->at(i));

		}*/
		vypis = std::to_string(testAAR->at(0));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(1));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(2));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(3));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(4));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(5));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(6));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(7));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(8));
		SimpleTest::logInfo(vypis);


		testAAR->insert(8, 4);

		SimpleTest::assertTrue(testAAR->size() == (10), "DoubleLinkedList::size() plny na 4 8");
		vypis = std::to_string(testAAR->at(0));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(1));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(2));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(3));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(4));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(5));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(6));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(7));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(8));
		SimpleTest::logInfo(vypis);
		vypis = std::to_string(testAAR->at(9));
		SimpleTest::logInfo(vypis);

		delete testAAR;
	}


	DoubleLinkedListTestEquals::DoubleLinkedListTestEquals() :
		SimpleTest("DoubleLinkedList test equals")
	{
	}
	void DoubleLinkedListTestEquals::test()
	{
		structures::List<int>* testE1 = new structures::DoubleLinkedList<int>();
		for (int i = 0; i < 10; i++) {
			testE1->add(1 + i * 2);

		}

		structures::List<int>* testE2 = new structures::DoubleLinkedList<int>();
		for (int i = 0; i < 10; i++) {
			testE2->add(5 + i);

		}

		SimpleTest::assertTrue(testE2->equals(*testE1) == false, "DoubleLinkedList::equals() nerovnaju sa");
		testE2->assign(*testE1);

		SimpleTest::assertTrue(testE2->equals(*testE1) == true, "DoubleLinkedList::equals() rovnaju sa");

		delete testE1;
		delete testE2;
	}

// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
		addTest(new ArrayListTestAddRemove());
		addTest(new ArrayListTestEquals());
		
	}

// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
	}

	// DoubleLinkedListTestOverall:

	DoubleLinkedListTestOverall::DoubleLinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new DoubleLinkedListTestInterface());
		addTest(new DoubleLinkedListTestAddRemove());
		addTest(new DoubleLinkedListTestEquals());
	}

// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
		addTest(new DoubleLinkedListTestOverall());
	}
}