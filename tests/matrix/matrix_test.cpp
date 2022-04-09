#include "matrix_test.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"

using namespace structures;
namespace tests
{
	tests::MatrixTestInterface::MatrixTestInterface() :
		SimpleTest("Interface")
	{
	}

	void tests::MatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
		SimpleTest::logPass("Compiled.");

	}


	void CoherentMatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
		SimpleTest::logPass("Compiled.");
	}

	structures::Matrix<int>* CoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	void IncoherentMatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
		SimpleTest::logPass("Compiled.");
	}

	structures::Matrix<int>* IncoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestOverall::CoherentMatrixTestOverall() :
		ComplexTest("CoherentMatrix")
	{
		addTest(new CoherentMatrixTestInterface());
		addTest(new CoherentMatrixPerformanceTest());
		addTest(new CoherentMatrixTestAt());
		addTest(new CoherentMatrixTestEquals());
		addTest(new CoherentMatrixTestAssign());
		addTest(new CoherentMMatrixTestCopy());
		addTest(new CoherentMatrixTimeAnalysis());
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncoherentMatrixPerformanceTest());
		addTest(new IncoherentMatrixTestAt());
		addTest(new IncoherentMatrixTestEquals());
		addTest(new IncoherentMatrixTestAssign());
		addTest(new IncoherentMatrixTestCopy());
		addTest(new IncoherentMatrixTimeAnalysis());



	}

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
	}


	MatrixPerformanceTest::MatrixPerformanceTest() :
		SimpleTest("PerformanceTest")
	{
	}

	void MatrixPerformanceTest::test()
	{
	}

	void IncoherentMatrixPerformanceTest::test()
	{
		char script = 'A';
		int sizeA, sizeB;
		for (size_t i = 0; i < 4; i++)
		{
			switch (script)
			{
			case 'A':
				sizeA = 10;
				sizeB = 50;
				break;
			case 'B':
				sizeA = 2000;
				sizeB = 500;
				break;
			case 'C':
				sizeA = 50;
				sizeB = 10;
				break;
			default:
				sizeA = 500;
				sizeB = 2000;
				break;
			}
			std::string fileName = "SuborInc";
			fileName.append(&script);
			fileName +=".csv";
			this->testMatrix(new structures::IncoherentMatrix<int>(sizeA, sizeB), script, fileName, 1000000);
			script++;
			SimpleTest::logPass("Incoherent matrix performance test of one scenario finished.");
		}
		SimpleTest::logPass("Incoherent matrix performance test finished.");
	}

	void CoherentMatrixPerformanceTest::test()
	{
		char script = 'A';
		int sizeA, sizeB;
		for (size_t i = 0; i < 4; i++)
		{
			switch (script)
			{
			case 'A':
				sizeA = 10;
				sizeB = 50;
				break;
			case 'B':
				sizeA = 2000;
				sizeB = 500;
				break;
			case 'C':
				sizeA = 50;
				sizeB = 10;
				break;
			default:
				sizeA = 500;
				sizeB = 2000;
				break;
			}
			std::string fileName = "SuborCoh";
			fileName.append(&script);
			fileName += ".csv";
			structures::CoherentMatrix<int>* coh = new CoherentMatrix<int>(sizeA, sizeB);
			this->testMatrix(coh, script, fileName, 1000000);
			script++;
			SimpleTest::logPass("Coherent matrix performance test of one scenario finished.");
			delete coh;
		}
		SimpleTest::logPass("Coherent matrix performance test finished.");
	}


	void MatrixPerformanceTest::testMatrix(structures::Matrix<int>* matrix, char script, std::string file, int count)
	{
		int operationColumn, operationRow, operationAt;
		switch (script)
		{
		case 'A':
			operationColumn = 5;
			operationRow = 5;
			operationAt = 90;
			break;
		case 'B':
			operationColumn = 5;
			operationRow = 5;
			operationAt = 90;
			break;
		case 'C':
			operationColumn = 10;
			operationRow = 30;
			operationAt = 60;
			break;
		case 'D':
			operationColumn = 10;
			operationRow = 30;
			operationAt = 60;
			break;
		}
		matrix->size();
		structures::FileLogConsumer* consumer = new structures::FileLogConsumer(file);
		std::string message = "Testing script ";
		message.append(&script);
		consumer->logMessage(structures::LogType::Info, message);
		consumer->logMessage(structures::LogType::Info, "Colums x Rows ; " + std::to_string(matrix->getColumnCount()) + ";" + std::to_string(matrix->getRowCount()));
		matrix->at(1, 1);

		srand(time(0));

		for (int i = 0; i < count; i++)
		{
			int random = rand() % 100 + 1;
			if (random <= operationRow) {
				startStopwatch();
				matrix->getRowCount();
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "getRowCount");

			}
			else if (operationRow < random && random <= operationColumn + operationRow) {
				startStopwatch();
				matrix->getColumnCount();
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "getColumnCount");

			}
			else {
				int indexA = rand() % matrix->getRowCount();
				int indexB = rand() % matrix->getColumnCount();
				startStopwatch();
				matrix->at(indexA, indexB);
				stopStopwatch();
				consumer->logDuration(0, getElapsedTime(), "at ; " + std::to_string(indexA) + ";" + std::to_string(indexB));
			}

		}
		delete consumer;
	}

	MatrixTimeAnalysis::MatrixTimeAnalysis() : SimpleTest("TimeAnalysis")
	{
	}

	void MatrixTimeAnalysis::test()
	{
	}

	void MatrixTimeAnalysis::testMatrixAt(structures::Matrix<int>* matrix, structures::FileLogConsumer* consumer)
	{
		std::string message = "Column count " + std::to_string(matrix->getColumnCount());
		logInfo(message);
		consumer->logMessage(LogType::Info, message);
		message = "Row count " + std::to_string(matrix->getRowCount());
		consumer->logMessage(LogType::Info, message);
		srand(0);
		for (size_t i = 0; i < 100; i++)
		{
			int index1 = rand() % matrix->getRowCount();
			int index2 = rand() % matrix->getColumnCount();

			startStopwatch();
			matrix->at(index1, index2);
			stopStopwatch();
			consumer->logDuration(0, getElapsedTime(), "at");

		}
	}

	void MatrixTimeAnalysis::testMatrixAssign(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2, FileLogConsumer* consumer)
	{
		std::string message = "Column count " + std::to_string(matrix1->getColumnCount());
		consumer->logMessage(LogType::Info, message);
		message = "Row count " + std::to_string(matrix1->getRowCount());
		consumer->logMessage(LogType::Info, message);
		srand(0);
		for (size_t i = 0; i < 100; i++)
		{
			startStopwatch();
			matrix1->assign(*matrix2);
			stopStopwatch();
			consumer->logDuration(0, getElapsedTime(), "assign");

		}
	}



	void CoherentMatrixTimeAnalysis::test()
	{
		std::string file = "CoherentTimeAt.csv";
		structures::FileLogConsumer* logger = new structures::FileLogConsumer(file);
		std::string file2 = "CoherentTimeAssign.csv";
		structures::FileLogConsumer* logger2 = new structures::FileLogConsumer(file2);

		for (size_t i = 100; i <= 1000; i += 100)
		{
			for (size_t j = 100; j <= 1000; j += 100)
			{
				Matrix<int>* matrix = new CoherentMatrix<int>(i, j);
	
				this->testMatrixAt(matrix, logger);

				Matrix<int>* matrix2 = new CoherentMatrix<int>(i, j);
				this->testMatrixAssign(matrix, matrix2, logger2);				
				

				delete matrix;
				delete matrix2;

			}
		}

		delete logger;
		delete logger2;
	}

	void IncoherentMatrixTimeAnalysis::test()
	{
		std::string file = "IncoherentTimeAt.csv";
		structures::FileLogConsumer* logger = new structures::FileLogConsumer(file);
		std::string file2 = "IncoherentTimeAssign.csv";
		structures::FileLogConsumer* logger2 = new structures::FileLogConsumer(file2);
		for (size_t i = 100; i <= 1000; i += 100)
		{
			for (size_t j = 100; j <= 1000; j += 100)
			{
				Matrix<int>* matrix = new IncoherentMatrix<int>(i, j);
				this->testMatrixAt(matrix, logger);
				Matrix<int>* matrix2 = new IncoherentMatrix<int>(i, j);
				this->testMatrixAssign(matrix, matrix2, logger2);
				delete matrix;

			}
		}
		delete logger;
		delete logger2;
	}




	/// UNIT TESTY
	MatrixTestAt::MatrixTestAt() :
		SimpleTest("TestAt")
	{

	}

	void MatrixTestAt::test()
	{
	}


	void MatrixTestAt::testAt(structures::Matrix<int>* matrix)
	{
		this->logInfo("Testing at - matrix with size 6x5");
		this->logInfo("Setting matrix[i][j] with numbers i");
		for (size_t i = 0; i < matrix->getRowCount(); i++)
		{
			for (size_t j = 0; j < matrix->getColumnCount(); j++)
			{
				(*matrix).at(i, j) = i;
			}
		}
		this->logInfo("Reading matrix");
		for (size_t i = 0; i < matrix->getRowCount(); i++)
		{
			std::string array;
			for (size_t j = 0; j < matrix->getColumnCount(); j++)
			{
				array += std::to_string((*matrix).at(i, j));
			}
			this->logInfo(array);
		}
		this->logInfo("Setting number to wrong indexes matrix[-1][-1]");
		try {
			(*matrix).at(-1, -1) = 1;
		}
		catch (std::out_of_range) {
			logError("Exception out of range");
		}
		this->logInfo("Getting number from wrong indexes matrix[rowCount][columnCount]");
		try {
			int number = (*matrix).at(matrix->getRowCount(), matrix->getColumnCount());
		}
		catch (std::out_of_range) {
			logError("Exception out of range");
		}
		delete matrix;
		this->logPass("Test compiled.");
	}

	void IncoherentMatrixTestAt::test()
	{
		testAt(new IncoherentMatrix<int>(6, 5));
	}

	void CoherentMatrixTestAt::test()
	{
		testAt(new IncoherentMatrix<int>(6, 5));
	}

	MatrixTestEquals::MatrixTestEquals() : SimpleTest("TestEquals")
	{
	}


	void MatrixTestEquals::test()
	{
	}

	void MatrixTestEquals::testEquals(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2)
	{
		this->logInfo("Testing equals - matrix1 & matrix2");

		if ((*matrix1).equals(*matrix2)) {
			this->logPass("Matrixes are equal.");
		}
		else {
			this->logError("Matrixes are not equal.");
		}
		delete matrix2;
	}

	void IncoherentMatrixTestEquals::test()
	{
		this->logInfo("Creating new matrix1 size 10x25, all values are 0");
		structures::Matrix<int>* matrix1 = new IncoherentMatrix<int>(10, 25);
		this->logInfo("Creating new matrix2 size 25x10, all values are 0");
		structures::Matrix<int>* matrix2 = new IncoherentMatrix<int>(25, 10);
		testEquals(matrix1, matrix2);
		this->logInfo("Creating new matrix2 size 10x25, setting matrix2[9][24] = 1, other values are 0");
		matrix2 = new IncoherentMatrix<int>(10, 25);
		(*matrix2).at(9, 24) = 1;
		testEquals(matrix1, matrix2);
		this->logInfo("Creating new matrix2 size 10x25, all values are 0");
		matrix2 = new IncoherentMatrix<int>(10, 25);
		testEquals(matrix1, matrix2);
		this->logPass("Test compiled.");
		delete matrix1;


	}

	void CoherentMatrixTestEquals::test()
	{
		this->logInfo("Creating new matrix1 size 10x25, all values are 0");
		structures::Matrix<int>* matrix1 = new CoherentMatrix<int>(10, 25);
		this->logInfo("Creating new matrix2 size 25x10, all values are 0");
		structures::Matrix<int>* matrix2 = new CoherentMatrix<int>(25, 10);
		testEquals(matrix1, matrix2);
		this->logInfo("Creating new matrix2 size 10x25, setting matrix2[9][24] = 1, other values are 0");
		matrix2 = new CoherentMatrix<int>(10, 25);
		(*matrix2).at(9, 24) = 1;
		testEquals(matrix1, matrix2);
		this->logInfo("Creating new matrix2 size 10x25, all values are 0");
		matrix2 = new CoherentMatrix<int>(10, 25);
		testEquals(matrix1, matrix2);
		this->logPass("Test compiled.");
		delete matrix1;
	}


	MatrixTestAssign::MatrixTestAssign() : SimpleTest("TestAssign")
	{
	}

	void MatrixTestAssign::test()
	{
	}

	void MatrixTestAssign::testAsign(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2)
	{
		srand(0);
		this->logInfo("Testing assigning - matrix1 into matrix2");

		this->logInfo("Setting random values into first matrix");
		for (size_t i = 0; i < matrix1->getRowCount(); i++)
		{
			for (size_t j = 0; j < matrix1->getColumnCount(); j++)
			{
				(*matrix1).at(i, j) = rand() % 10;
			}
		}
		this->logInfo("Setting random values into second matrix");
		for (size_t i = 0; i < matrix2->getRowCount(); i++)
		{
			for (size_t j = 0; j < matrix2->getColumnCount(); j++)
			{
				(*matrix2).at(i, j) = rand() % 10;
			}
		}
		this->logInfo("Matrix 1: ");
		readMatrix(*matrix1);
		this->logInfo("Matrix 2 before assigning: ");
		readMatrix(*matrix2);

		this->logInfo("Assigning matrix 1 into matrix 2...");

		try {
			matrix2->assign(*matrix1);
		}
		catch (...) {
			logError("Assigning is not possible");
			delete matrix2;
			delete matrix1;
			return;
		}

		this->logInfo("Matrix 2 after assigning: ");
		readMatrix(*matrix2);

		this->logInfo("Test of equality");
		if ((*matrix1).equals(*matrix2)) {
			this->logPass("Matrixes are equal.");
		}
		else {
			this->logError("Matrixes are not equal.");
		}
		delete matrix2;
		delete matrix1;

		this->logPass("Test compiled.");
	}

	void IncoherentMatrixTestAssign::test()
	{
		this->logInfo("Testing assigning - matrix1 sizes 5x5 into matrix2 sizes 5x3");
		testAsign(new IncoherentMatrix<int>(5, 5), new IncoherentMatrix<int>(5, 3));
		this->logInfo("Testing assigning - matrix1 sizes 5x5 into matrix2 sizes 5x5");
		testAsign(new IncoherentMatrix<int>(5, 5), new IncoherentMatrix<int>(5, 5));
	}

	void CoherentMatrixTestAssign::test()
	{
		this->logInfo("Testing assigning - matrix1 sizes 5x5 into matrix2 sizes 5x3");
		testAsign(new CoherentMatrix<int>(5, 5), new CoherentMatrix<int>(5, 3));
		this->logInfo("Testing assigning - matrix1 sizes 5x5 into matrix2 sizes 5x5");
		testAsign(new CoherentMatrix<int>(5, 5), new CoherentMatrix<int>(5, 5));
	}

	void MatrixTestAssign::readMatrix(structures::Matrix<int>& matrix)
	{
		for (size_t i = 0; i < matrix.getRowCount(); i++)
		{
			std::string array;
			for (size_t j = 0; j < matrix.getColumnCount(); j++)
			{
				array += std::to_string((matrix).at(i, j));
			}
			this->logInfo(array);
		}
	}
	MatrixTestCopy::MatrixTestCopy() : SimpleTest("TestCopy")
	{
	}

	void MatrixTestCopy::test()
	{
	}


	void IncoherentMatrixTestCopy::test()
	{
		this->logInfo("Creating and setting random values into first matrix");
		srand(0);

		IncoherentMatrix<int>* matrix = new IncoherentMatrix<int>(5, 5);
		for (size_t i = 0; i < matrix->getRowCount(); i++)
		{
			for (size_t j = 0; j < matrix->getColumnCount(); j++)
			{
				(*matrix).at(i, j) = rand() % 10;
			}
		}
		this->logInfo("Testing copy constructor, creating new copied matrix");
		Matrix<int>* copy = new IncoherentMatrix<int>(*matrix);
		this->logInfo("Testing equals - matrix1 & matrix2");

		if ((*matrix).equals(*copy)) {
			this->logPass("Matrixes are equal.");
			this->logPass("Test compiled.");

		}
		else {
			this->logError("Matrixes are not equal.");
		}
		delete matrix;
		delete copy;
	}



	void CoherentMMatrixTestCopy::test()
	{
		this->logInfo("Creating and setting random values into first matrix");
		srand(0);

		CoherentMatrix<int>* matrix = new CoherentMatrix<int>(5, 5);
		for (size_t i = 0; i < matrix->getRowCount(); i++)
		{
			for (size_t j = 0; j < matrix->getColumnCount(); j++)
			{
				(*matrix).at(i, j) = rand() % 10;
			}
		}
		this->logInfo("Testing copy constructor, creating new copied matrix");
		Matrix<int>* copy = new CoherentMatrix<int>(*matrix);
		this->logInfo("Testing equals - matrix1 & matrix2");

		if ((*matrix).equals(*copy)) {
			this->logPass("Matrixes are equal.");
			this->logPass("Test compiled.");

		}
		else {
			this->logError("Matrixes are not equal.");
		}

		delete matrix;
		delete copy;
	}


}