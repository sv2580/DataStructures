#pragma once

#include "../test.h"
#include "../../structures/table/table.h"
#include "../../file_log_consumer.h"
#include "../../structures/heap_monitor.h"
namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania tabulky avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class TableTestInterface
		: public SimpleTest
	{
	public:
		TableTestInterface();
		void test() override;

	protected:
		virtual structures::Table<int, int>* makeTable() = 0;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class BinarySearchTreeTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class SortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

		/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class BinarySearchTreeTestOverall
		: public ComplexTest
	{
	public:
		BinarySearchTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class SortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		SortedSequenceTableTestOverall();
	};

	
    //****************Druha uloha
   
    class TablePerformanceTest : public SimpleTest {
    public:
        TablePerformanceTest();
        void testTable(structures::Table<int, int>* table, char script, std::string file, int count);
    };


    class SortedSequenceTablePerformanceTest : public TablePerformanceTest {
    public:
        void test() override;
    };


    class BinarySearchTreePerformanceTest : public TablePerformanceTest {
    public:
        void test() override;
    };

    //****************Tretia uloha

    class TableTimeAnalysis : public SimpleTest {
    public:
        TableTimeAnalysis();
        void testInsert(structures::Table<int,int>* table, std::string file);
        void testRemove(structures::Table<int,int>* table, std::string file);
        void testTryFind(structures::Table<int,int>* table, std::string file);
    };

    class SortedSequenceTableTimeAnalysis : public TableTimeAnalysis {
    public:
        void test() override;
    };


    class BinarySearchTreeTimeAnalysis : public TableTimeAnalysis {
    public:
        void test() override;
    };

//**************************************************
//clear, find&tryfind, insert, remove, containsKey, equalsTable, assign
	class TableTryAndFindTest : SimpleTest{
		TableTryAndFindTest();
		void testClear(structures::Table<int,int>* table);
	};

	class SortedSequenceTableTryAndFindTest : public TableTryAndFindTest {
    public:
        void test() override;
    };

    class BinarySearchTreeTryAndFindTest : public TableTryAndFindTest {
    public:
        void test() override;
    };

	class TableInsertTest : SimpleTest{
		TableInsertTest();
		void testInsert(structures::Table<int,int>* table);
	};

	class SortedSequenceTableInsertTest : public TableInsertTest {
    public:
        void test() override;
    };

    class BinarySearchTreeInsertTest : public TableInsertTest {
    public:
        void test() override;
    };

	class TableRemoveTest : SimpleTest{
		TableRemoveTest();
		void testRemove(structures::Table<int,int>* table);
	};

	class SortedSequenceTableRemoveTest : public TableRemoveTest {
    public:
        void test() override;
    };


    class BinarySearchTreeRemoveTest : public TableRemoveTest {
    public:
        void test() override;
    };

	class TableContainsKeyTest : SimpleTest{
		TableContainsKeyTest();
		void testContainsKey(structures::Table<int,int>* table);
	}; 

	class SortedSequenceTableContainsKeyTest : public TableContainsKeyTest {
    public:
        void test() override;
    };


    class BinarySearchTreeContainsKeyTest : public TableContainsKeyTest {
    public:
        void test() override;
    };

	class TableEqualsTableTest : SimpleTest{
		TableEqualsTableTest();
		void testEqualsTable(structures::Table<int,int>* table1, structures::Table<int,int>* table2);
	};

	class SortedSequenceTableEqualsTableTest : public TableEqualsTableTest {
    public:
        void test() override;
    };


    class BinarySearchTreeEqualsTableTest : public TableEqualsTableTest {
    public:
        void test() override;
    };

	class SortedSequenceTableAssignTest : public SimpleTest {
    public:
		SortedSequenceTableAssignTest();
        void test() override;
    };

    class BinarySearchTreeAssignTest : public SimpleTest {
    public:
		BinarySearchTreeAssignTest();
        void test() override;
    };

//**************************************************
	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class HashTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class LinkedTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class TreapTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class UnsortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};


	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class HashTableTestOverall
		: public ComplexTest
	{
	public:
		HashTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class LinkedTableTestOverall
		: public ComplexTest
	{
	public:
		LinkedTableTestOverall();
	};


	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class TreapTestOverall
		: public ComplexTest
	{
	public:
		TreapTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class UnsortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		UnsortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju tabulku.
	/// </summary>
	class TableTestOverall
		: public ComplexTest
	{
	public:
		TableTestOverall();
	};
}