#pragma once

#include "matrix.h"
#include "../array/array.h"
#include <stdexcept>
#include "../heap_monitor.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

	private:
		Array<T>* _matrix;
		size_t _rowCount;
		size_t _columnCount;
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount)
		: Matrix<T>(),
		_rowCount(rowCount),
		_columnCount(columnCount)
	{
		_matrix = new Array<T>(_rowCount * _columnCount);
		for (size_t i = 0; i < _rowCount * _columnCount; i++)
		{
			(*_matrix)[i] = NULL;
		}
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other)
		: Matrix<T>(),
		_rowCount(other._rowCount),
		_columnCount(other._columnCount),
		_matrix(new Array<T>(*other._matrix))
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete _matrix;
		_matrix = nullptr;
		_columnCount = 0;
		_rowCount = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		CoherentMatrix<T>& otherMatrix = dynamic_cast<CoherentMatrix<T>&>(other);
		if (otherMatrix._columnCount == _columnCount && otherMatrix._rowCount == _rowCount) {
			if (this != &other) {
				_rowCount = otherMatrix._rowCount;
				_columnCount = otherMatrix._columnCount;
				delete _matrix;
				_matrix = new Array<T>(*otherMatrix._matrix);
			}
			return *this;
		}
		else {
			throw "Wrong sizes";
		}
	}
	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		CoherentMatrix<T>& otherMatrix = dynamic_cast<CoherentMatrix<T>&>(other);

		if (_rowCount != otherMatrix.getRowCount() || _columnCount != otherMatrix.getColumnCount()) {
			return false;
		}

		for (size_t i = 0; i < otherMatrix.size(); i++)
		{
			if ((*_matrix)[i] != (*otherMatrix._matrix)[i]) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return _rowCount * _columnCount;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return _rowCount;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return _columnCount;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, _rowCount, "Invalid index");
		Utils::rangeCheckExcept(columnIndex, _columnCount, "Invalid index");

		return (*_matrix)[columnIndex * rowIndex + columnIndex];
	}
}