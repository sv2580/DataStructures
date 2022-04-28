#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/double_linked_list.h"
#include "../../structures/heap_monitor.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania listu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ListTestInterface
		: public SimpleTest
	{
	public:
		ListTestInterface(std::string name);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody ArrayListu.
	/// </summary>
	class ArrayListTestInterface
		: public ListTestInterface
	{
	public:
		ArrayListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTestInterface
		: public ListTestInterface
	{
	public:
		DoubleLinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class LinkedListTestInterface
		: public ListTestInterface
	{
	public:
		LinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList.
	/// </summary>
	class ArrayListTestOverall
		: public ComplexTest
	{
	public:
		ArrayListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju LinkedList.
	/// </summary>
	class LinkedListTestOverall
		: public ComplexTest
	{
	public:
		LinkedListTestOverall();
	};

	class DoubleLinkedListTestOverall
		: public ComplexTest
	{
	public:
		DoubleLinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList a LinkedList.
	/// </summary>
	class ListTestOverall :
		public ComplexTest
	{
	public:
		ListTestOverall();
	};

	class ListAssign : public SimpleTest {
	public: 
		void test() override;
		void testAssign(structures::List<int>* list, structures::List<int>* list2);
		ListAssign();
	};

	class ListEquals : public SimpleTest {
	public:
		void test() override;
		void testEquals(structures::List<int>* list, structures::List<int>* list2);
		ListEquals();
	};


	class ListAddInsert : public SimpleTest {
	public:
		void test() override;
		ListAddInsert();
		void testAddInsert(structures::List<int>* list);
	};


	class ListRemove : public SimpleTest {
	public:
		void test() override;
		void testRemove(structures::List<int>* list);
		ListRemove();
	};

	class ListClear : public SimpleTest {
	public:
		void test() override;
		void testClear(structures::List<int>* list);
		ListClear();
	};



	class DoubleLinkedListAssign : public ListAssign {
	public:
		void test() override;
	};

	class DoubleLinkedListEquals : public ListEquals {
	public:
		void test() override;
	};


	class DoubleLinkedListAddInsert : public ListAddInsert {
	public:
		void test() override;
	};


	class DoubleLinkedListRemove : public ListRemove {
	public:
		void test() override;
	};

	class DoubleLinkedListClear : public ListClear {
	public:
		void test() override;
	};

	class DoubleLinkedListCopy : public SimpleTest {
	public:
		DoubleLinkedListCopy();
		void test() override;

	};

	class ArrayListCopy : public SimpleTest {
	public:
		ArrayListCopy();
		void test() override;
	};
	class ArrayListAssign : public ListAssign {
	public:
		void test() override;
	};

	class ArrayListEquals : public ListEquals {
	public:
		void test() override;
	};

	class ArrayListAddInsert : public ListAddInsert {
	public:
		void test() override;
	};


	class ArrayListRemove : public ListRemove {
	public:
		void test() override;
	};

	class ArrayListClear : public ListClear {
	public:
		void test() override;
	};

    //**********druha uloha**********
	class ListPerformanceTest : public SimpleTest {
	public:
		ListPerformanceTest();
		void test() override;
		void ListPerformanceTest::testList(structures::List<int>* list, char script, std::string file, int count);
	};


	class ArrayListPerformanceTest : public ListPerformanceTest {
	public:
		void test() override;
	};


	class DoubleLinkedListPerformanceTest : public ListPerformanceTest {
	public:
		void test() override;
	};


	//**********tretia uloha**********


	class ListTimeAnalysis : public SimpleTest {
	public:
		ListTimeAnalysis();
		void testListAt(structures::List<int>* list, std::string file);
		void testListRemoveAt(structures::List<int>* list, std::string file);
		void testInsert(structures::List<int>* list, std::string file);

	};


	class ArrayListTimeAnalysis : public ListTimeAnalysis {
	public:
		void test() override;
	};


	class DoubleLinkedListTimeAnalysis : public ListTimeAnalysis {
	public:
		void test() override;
	};






	class ListMaker {
	public: 
		virtual structures::List<int>* makeList() const = 0;
	};

	class ArrayListMaker : ListMaker {
		// Inherited via ListMaker
		virtual structures::List<int>* makeList() const override;
	};
}