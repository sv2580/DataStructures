#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/double_linked_list.h"

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

	class ArrayListTestAddRemove
		: public SimpleTest
	{
	public:
		ArrayListTestAddRemove();
		void test() override;
	};

	class ArrayListTestEquals
		: public SimpleTest
	{
	public:
		ArrayListTestEquals();
		void test() override;
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
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class DoubleLinkedListTestInterface
		: public ListTestInterface
	{
	public:
		DoubleLinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTestAddRemove
		: public SimpleTest
	{
	public:
		DoubleLinkedListTestAddRemove();
		void test() override;
	};

	class DoubleLinkedListTestEquals
		: public SimpleTest
	{
	public:
		DoubleLinkedListTestEquals();
		void test() override;
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
	/// Zahrna v sebe vsetky testy, ktore testuju DoubleLinkedList.
	/// </summary>
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
}