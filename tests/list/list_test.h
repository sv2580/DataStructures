#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"

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
}