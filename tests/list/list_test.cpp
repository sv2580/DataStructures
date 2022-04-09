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

	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
	}

// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
	}

// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
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
			l1 += list->at(i);
			l2 += list2->at(i);
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

	ListEquals::ListEquals() : SimpleTest("assign")
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
			list->add(rand() % 10);
			l1 += list->at(i);
		}

		logInfo(l1);
		l1 = "";
		logInfo("Inserting random values to list - last place, end, middle");
		list->insert(rand() % 10, 0);
		list->insert(rand() % 10, 5);
		list->insert(rand() % 10, 10);
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += list->at(i);
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
			list->add(rand() % 10);
			l1 += list->at(i);
		}

		logInfo(l1);
		l1 = "";
		logInfo("Deleting random values from list - last place, end, middle");
		list->removeAt(0);
		list->removeAt(5);
		list->removeAt(10);
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += list->at(i);
		}
		logInfo(l1);
		l1 = "";

		logInfo("Trying to remove value");
		list->tryRemove(list->at(5));
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += list->at(i);
		}
		logInfo(l1);
		logPass("Test compilled");
	}

	ListRemove::ListRemove() : SimpleTest("assign")
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
			l1 += list->at(i);
		}

		logInfo(l1);
		logInfo("Clearing list and trying to writing it out");
		list->clear();
		l1 = "";
		for (size_t i = 0; i < list->size(); i++)
		{
			l1 += list->at(i);
		}
		logInfo(l1);
		logPass("Test compilled");

	}

	ListClear::ListClear() : SimpleTest("assign")
	{

	}


	


}