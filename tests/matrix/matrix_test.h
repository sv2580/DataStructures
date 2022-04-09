#pragma once

#include "../test.h"
#include "../../structures/matrix/matrix.h"
#include "../../structures/_logger/logger.h"
#include "../../structures/heap_monitor.h"
#include "../../file_log_consumer.h"
using namespace structures;
namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania matice avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class MatrixTestInterface
		: public SimpleTest
	{
	public:
		MatrixTestInterface();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody koherentnej matice.
	/// </summary>
	class CoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	public:
		void test() override;
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};


	/// <summary>
	/// Zavola vsetky metody nekoherentnej matice.
	/// </summary>
	class IncoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	public: 
		void test() override;
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherentMatrix.
	/// </summary>
	class CoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		CoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju IncoherentMatrix.
	/// </summary>
	class IncoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		IncoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherrentMatrix a IncoherrentMatrix.
	/// </summary>
	class MatrixTestOverall
		: public ComplexTest
	{
	public:
		MatrixTestOverall();
	};


	//******** Druha uloha

	class MatrixPerformanceTest : public SimpleTest {
	public: 
		MatrixPerformanceTest();
		 void test() override;
		 //virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
		 void MatrixPerformanceTest::testMatrix(structures::Matrix<int>* matrix, char script, std::string file, int count);
	};


	class CoherentMatrixPerformanceTest : public MatrixPerformanceTest {
	public:
		void test() override;
	};


	class IncoherentMatrixPerformanceTest : public MatrixPerformanceTest {
	public:
		void test() override;
	};

	//******** Tretia uloha

	class MatrixTimeAnalysis : public SimpleTest {
	public:
		MatrixTimeAnalysis();
		void test() override;
		void testMatrixAt(structures::Matrix<int>* matrix, structures::FileLogConsumer* consumer);
		void testMatrixAssign(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2, structures::FileLogConsumer* consumer);


	};


	class CoherentMatrixTimeAnalysis : public MatrixTimeAnalysis {
	public:
		void test() override;
	};


	class IncoherentMatrixTimeAnalysis : public MatrixTimeAnalysis {
	public:
		void test() override;
	};


	//******* Unit testy
	class MatrixTestAt : public SimpleTest {
	public:
		MatrixTestAt();
		void test() override;
		void testAt(structures::Matrix<int>* matrix);
	};
	class IncoherentMatrixTestAt : public MatrixTestAt {
	public:
		void test() override;
	};

	class CoherentMatrixTestAt : public MatrixTestAt {
	public:
		void test() override;
	};


	class MatrixTestEquals : public SimpleTest {
	public:
		MatrixTestEquals();
		void test() override;
		void testEquals(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2);
	};

	class IncoherentMatrixTestEquals : public MatrixTestEquals {
	public:
		void test() override;
	};

	class CoherentMatrixTestEquals : public MatrixTestEquals {
	public:
		void test() override;
	};

	class MatrixTestAssign : public SimpleTest {
	public:
		MatrixTestAssign();
		void test() override;
		void testAsign(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2);
		void readMatrix(structures::Matrix<int>& matrix);
	};
	class IncoherentMatrixTestAssign : public MatrixTestAssign {
	public:
		void test() override;
	};

	class CoherentMatrixTestAssign : public MatrixTestAssign {
	public:
		void test() override;
	};

	class MatrixTestCopy : public SimpleTest {
	public:
		MatrixTestCopy();
		void test() override;
	};


	class IncoherentMatrixTestCopy : public MatrixTestCopy {
	public:
		void test() override;
	};

	class CoherentMMatrixTestCopy : public MatrixTestCopy {
	public:
		void test() override;
	};



}
