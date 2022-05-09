#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany haldou. Implementujucim typom haldy je struktura ArrayList. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class Heap : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Heap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Halda, z ktorej sa prevezmu vlastnosti. </param>
		Heap(Heap<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do haldy. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z haldy. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je halda prazdna. </exception>
		T pop() override;

	protected:
		/// <summary> Vrati index v ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je ArrayList prazdny. </exception>
		int indexOfPeek() override;

	private:
		/// <summary> Vrati index v ArrayList-e, na ktorom by sa mal nachadzat otec daneho prvku. </summary>
		/// <param name = "index"> Index prvku, ktoreho otca chceme vratit. </param>
		/// <returns> Index, na ktorom ba sa mal nachadzat otec prvku. </returns>
		int getParentIndex(int index);

		/// <summary> Vrati index v ArrayList-e, na ktorom by mal mat dany prvok syna s najvacsou prioritou. </summary>
		/// <param name = "index"> Index prvku, ktoreho syna chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat syn prvku. </returns>
		int getGreaterSonIndex(int index);
	};

	template<typename T>
	Heap<T>::Heap() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	Heap<T>::Heap(Heap<T>& other) :
		Heap<T>()
	{
		assign(other);
	}

	template<typename T>
	inline Structure& Heap<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueList<T>&>(other));
	}

	template<typename T>
	void Heap<T>::push(int priority, const T& data)
	{
		PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));

		int current = static_cast<int>(PriorityQueueList<T>::list_->size()) - 1;
		int parent = getParentIndex(current);
		while(parent >= 0 && PriorityQueueList<T>::list_->at(current)->getPriority() < PriorityQueueList<T>::list_->at(parent)->getPriority())
		{
			Utils::swap(PriorityQueueList<T>::list_->at(current), PriorityQueueList<T>::list_->at(parent));
			current = parent;
			parent = getParentIndex(current);
		}
	}

	template<typename T>
	T Heap<T>::pop()
	{
		PriorityQueueItem<T>* item = (*PriorityQueueList<T>::list_).at(0);
		
		PriorityQueueList<T>::list_->at(0) = PriorityQueueList<T>::list_->at(static_cast<int>(PriorityQueueList<T>::list_->size()) - 1);
		PriorityQueueList<T>::list_->removeAt(static_cast<int>(PriorityQueueList<T>::list_->size()) - 1);

		int current = 0;
		int son = getGreaterSonIndex(current);
		
		
		while (son < static_cast<int>(PriorityQueueList<T>::list_->size())
			&& PriorityQueueList<T>::list_->at(current)->getPriority() > PriorityQueueList<T>::list_->at(son)->getPriority())
		{
		Utils::swap(PriorityQueueList<T>::list_->at(son), PriorityQueueList<T>::list_->at(current));
			current = son;
			son = getGreaterSonIndex(current);
		}

		T result = item->accessData();
		delete item;
		return result;
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(int index)
	{
		return (index - 1) / 2;
	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(int index)
	{
		int size = static_cast<int>(PriorityQueueList<T>::list_->size());
		int lsonindex = 2 * index + 1;
		int rsonindex = 2 * index + 2;
		PriorityQueueItem<T>* lson = lsonindex < size ? PriorityQueueList<T>::list_->at(lsonindex) : nullptr;
		PriorityQueueItem<T>* rson = rsonindex < size ? PriorityQueueList<T>::list_->at(rsonindex) : nullptr;
		if (lson != nullptr && rson != nullptr)
			return lson->getPriority() < rson->getPriority() ? lsonindex : rsonindex;
		else
			return lsonindex;
	}
	template<typename T>
	inline int Heap<T>::indexOfPeek()
	{
		if (PriorityQueueList<T>::list_->size() == 0) {
			throw std::logic_error("Heap<T>::indexOfPeek:: Heap is empty.");
		}

		return 0;
	}
}