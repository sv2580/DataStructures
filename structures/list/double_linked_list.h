#pragma once

#include "list.h"

namespace structures
{
	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.

	/// <summary> Obojstranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>


	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class DoubleLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DoubleLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~DoubleLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		DoubleLinkedListItem<T>* getNext();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(DoubleLinkedListItem<T>* next);

		/// <summary> Getter predchadzajuceho prvku zretazeneho zoznamu. </summary>
	 /// <returns> Predchadzajuci prvok zretazeneho zoznamu. </returns>
		DoubleLinkedListItem<T>* getPrev();

		/// <summary> Setter predchadzajuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy predchadzajuci prvok zretazeneho zoznamu. </param>
		void setPrev(DoubleLinkedListItem<T>* prev);


	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		DoubleLinkedListItem<T>* _next;
		DoubleLinkedListItem<T>* _prev;



	};

	template<typename T>
	class DoubleLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		DoubleLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		DoubleLinkedList(DoubleLinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~DoubleLinkedList();

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		T& at(int index) override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		T removeAt(int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() override;


	private:
		DoubleLinkedListItem<T>* getItemAtIndex(int index);


		/// <summary> Pocet prvkov v zozname. </summary>
		size_t _size;
		/// <summary> Prvy prvok zoznamu. </summary>
		DoubleLinkedListItem<T>* _first;
		/// <summary> Posledny prvok zoznamu. </summary>
		DoubleLinkedListItem<T>* _last;
	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class  DoubleLinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			DoubleLinkedListIterator(DoubleLinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~DoubleLinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			DoubleLinkedListItem<T>* _position;
		};
	};

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedList() :
		_size(0),
		_first(nullptr),
		_last(nullptr)
	{
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
		: _size(0)
	{
		this->assign(other);
	}

	template<typename T>
	inline DoubleLinkedList<T>::~DoubleLinkedList()
	{
		clear();
		_size = 0;
		_first = nullptr;
		_last = nullptr;
	}

	template<typename T>
	inline size_t DoubleLinkedList<T>::size()
	{
		return _size;
	}

	template<typename T>
	inline Structure& DoubleLinkedList<T>::assign(Structure& other)
	{
		if (this != &other) {
			DoubleLinkedList<T>& otherList = dynamic_cast<DoubleLinkedList<T>&>(other);
			clear();
			for (T data : otherList) {
				add(data);
			}
		}
		return *this;
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::equals(Structure& other)
	{
		DoubleLinkedList<T>* otherList = dynamic_cast<DoubleLinkedList<T>*>(&other);
		if (otherList == nullptr) {
			return false;
		}
		DoubleLinkedListItem<T>* item = _first;
		DoubleLinkedListItem<T>* otherItem = otherList->_first;
		while (item != nullptr) {
			if (item->accessData() != otherItem->accessData()) {
				return false;
			}

			item = item->getNext();
			otherItem = otherItem->getNext();
		}
		return true;
	}

	template<typename T>
	inline T& DoubleLinkedList<T>::at(int index)
	{
		DoubleLinkedListItem<T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline void DoubleLinkedList<T>::add(const T& data)
	{
		DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
		if (_size == 0) {
			_first = newItem;
			_last = newItem;
		}
		else {
			_last->setNext(newItem);
			newItem->setPrev(_last);
			_last = newItem;
		}
		_size++;
	}

	template<typename T>
	inline void DoubleLinkedList<T>::insert(const T& data, int index)
	{
		if (index == static_cast<int>(_size)) {
			add(data);
		}
		else {
			Utils::rangeCheckExcept(index, _size, "Invalid index");
			DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
			if (index == 0) {
				newItem->setNext(_first);
				_first->setPrev(newItem);
				_first = newItem;
			}
			else {
				DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
				DoubleLinkedListItem<T>* nextItem = prevItem->getNext();

				newItem->setNext(nextItem);
				newItem->setPrev(prevItem);
				prevItem->setNext(newItem);
				nextItem->setPrev(newItem);
			}
			_size++;
		}
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index == -1) {
			return false;
		}
		else {
			removeAt(index);
			return true;
		}
	}

	template<typename T>
	inline T DoubleLinkedList<T>::removeAt(int index)
	{
		Utils::rangeCheckExcept(index, _size, "Invalid index");
		DoubleLinkedListItem<T>* delItem;
		if (_first == _last) {
			delItem = _first;
			_first = nullptr;
			_last = nullptr;
		}
		else {
			if (index == 0)
			{
				delItem = _first;
				_first = _first->getNext();
				_first->setPrev(nullptr);


			}
			else {
				DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
				delItem = prevItem->getNext();
				if (_last == delItem) {
					_last = prevItem;
					_last->setNext(nullptr);
				}
				else {
					DoubleLinkedListItem<T>* nextItem = delItem->getNext();
					nextItem->setPrev(prevItem);
					prevItem->setNext(nextItem);
				}


			}
		}
		T result = delItem->accessData();
		delete delItem;
		_size--;

		return result;
	}

	template<typename T>
	inline int DoubleLinkedList<T>::getIndexOf(const T& data)
	{
		if (_size != 0)
		{
			int index = 0;
			DoubleLinkedListItem<T>* thisItem = _first;
			DoubleLinkedListItem<T>* dataItem = new DoubleLinkedListItem<T>(data);

			while (index <= _size)
			{
				DoubleLinkedListItem<T>* nextItem = dataItem->getNext();
				thisItem = nextItem;
				if (thisItem == dataItem)
				{
					return index;
				}
				index++;
			}

		}
		return -1;
	}

	template<typename T>
	inline void DoubleLinkedList<T>::clear()
	{
		if (_size != 0) {
			DoubleLinkedListItem<T>* delItem = _first;
			while (delItem != nullptr) {
				DoubleLinkedListItem<T>* nextItem = delItem->getNext();
				delete delItem;
				delItem = nextItem;
			}
			_size = 0;
			_first = nullptr;
			_last = nullptr;
		}
	}

	template<typename T>
	inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
	{
		return new DoubleLinkedListIterator(_first);

	}

	template<typename T>
	inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
	{
		return new DoubleLinkedListIterator(nullptr);
	}

	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
	{
		Utils::rangeCheckExcept(index, _size, "Invalid index!");
		DoubleLinkedListItem<T>* result;
		if (index > (_size + 1) / 2) {
			result = _last;
			for (size_t i = _size; i > _size - index - 1; i--)
			{
				result = result->getPrev();
			}
		}
		else {
			result = _first;
			for (size_t i = 0; i < index; i++)
			{
				result = result->getNext();
			}
		}
		return result;

	}


	template<typename T>
	inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
		DataItem<T>(data),
		_next(nullptr),
		_prev(nullptr)
	{
	}

	template<typename T>
	inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
		DataItem<T>(other),
		_next(other._next),
		_prev(other._next)
	{
	}

	template<typename T>
	inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
	{
		_next = nullptr;
		_prev = nullptr;
	}

	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
	{
		return _next;
	}

	template<typename T>
	inline void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
	{
		_next = next;
	}

	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrev()
	{
		return _prev;
	}

	template<typename T>
	inline void DoubleLinkedListItem<T>::setPrev(DoubleLinkedListItem<T>* prev)
	{
		_prev = prev;
	}





	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedListIterator::DoubleLinkedListIterator(DoubleLinkedListItem<T>* position)
	{
		_position = position;
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedListIterator::~DoubleLinkedListIterator()
	{
		_position = nullptr;
	}

	template<typename T>
	inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator=(Iterator<T>& other)
	{
		_position = dynamic_cast<const DoubleLinkedListIterator&>(other)._position;
		return *this;
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::DoubleLinkedListIterator::operator!=(Iterator<T>& other)
	{
		return _position != dynamic_cast<const DoubleLinkedListIterator&>(other)._position;
	}

	template<typename T>
	inline T DoubleLinkedList<T>::DoubleLinkedListIterator::operator*()
	{
		return _position->accessData();
	}

	template<typename T>
	inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator++()
	{
		_position = _position->getNext();
		return *this;
	}


}