#pragma once

#include "../test.h"
#include "../../structures/table/table.h"
#include "../../file_log_consumer.h"
#include <fstream>;

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

	// UNIT TESTY
	// 
	
	class TableInsertTest
		: public SimpleTest
	{
	public:
		TableInsertTest();
		void insertTest(structures::Table<int, int>* table);
	};

	class SSTableInsert
		: public TableInsertTest
	{
	public:
		void test() override;
	};

	class BSTreeInsert
		: public TableInsertTest
	{
	public:
		void test() override;
	};

	class TableAssignTest
		: public SimpleTest
	{
	public:
		TableAssignTest();
		void assignTest(structures::Table<int, int>* table1, structures::Table<int, int>* table2);
	};

	class SSTableAssign
		: public TableAssignTest
	{
	public:
		void test() override;
	};

	class BSTreeAssign
		: public TableAssignTest
	{
	public:
		void test() override;
	};


	class TablePerformanceTest : public SimpleTest {
	public:
		TablePerformanceTest();
		void TablePerformanceTest::tableTest(structures::Table<int, int>* priorityQueue, char script, std::string file);
	};


	class SSTablePerformanceTest : public TablePerformanceTest {
	public:
		void test() override;
	};


	class BSTreePerformanceTest : public TablePerformanceTest {
	public:
		void test() override;
	};


	class SSTableTestTimeComplexityInsert : public SimpleTest {
	public:
		SSTableTestTimeComplexityInsert();
		void test() override;
	};

	class SSTableTestTimeComplexityRemove : public SimpleTest {
	public:
		SSTableTestTimeComplexityRemove();
		void test() override;
	};

	class SSTableTestTimeComplexityTryFind : public SimpleTest {
	public:
		SSTableTestTimeComplexityTryFind();
		void test() override;
	};

	class BSTreeTestTimeComplexityInsert : public SimpleTest {
	public:
		BSTreeTestTimeComplexityInsert();
		void test() override;
	};

	class BSTreeTestTimeComplexityRemove : public SimpleTest {
	public:
		BSTreeTestTimeComplexityRemove();
		void test() override;
	};

	class BSTreeTestTimeComplexityTryFind : public SimpleTest {
	public:
		BSTreeTestTimeComplexityTryFind();
		void test() override;
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
	class SortedSequenceTableTestInterface
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
	class BinarySearchTreeTestOverall
		: public ComplexTest
	{
	public:
		BinarySearchTreeTestOverall();
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
	class SortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		SortedSequenceTableTestOverall();
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