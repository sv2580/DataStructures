#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete this->shortList_;
		delete this->longList_;
		this->shortList_ = nullptr;
		this->longList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		if (this != &other)
		{
			PriorityQueueTwoLists<T>& list = dynamic_cast<PriorityQueueTwoLists<T>&>(other);

			this->clear();
			delete this->shortList_;
			delete this->longList_;

			this->shortList_->assign(*list.shortList_);
			this->longList_->assign(*list.longList_);

			this->longList_->clear();
		}
		return *this;

	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return this->longList_->size() + this->shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();

		for (int i = 0; i < longList_->size(); i++)
		{
			delete (*longList_).at(i);
		}

		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		
		if (longList_->size() == 0)
		{
			PriorityQueueItem<T>* last = shortList_->pushAndRemove(priority,data);
			if (last != nullptr) {
				longList_->add(new PriorityQueueItem<T>(priority, data));
			}
		}
		else {
			longList_->add(new PriorityQueueItem<T>(priority, data));
		} 

	}

	

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		T result = shortList_->pop();
		if (shortList_->size() == 0 || longList_->size() > 0) {
			int newCap = sqrt(longList_->size());
				if (newCap < 4)
					newCap = 4;
			shortList_->trySetCapacity(newCap);
			LinkedList<PriorityQueueItem<T>*>* list = new  LinkedList<PriorityQueueItem<T>*>();
			for(PriorityQueueItem<T>* item : *longList_) {
				PriorityQueueItem<T>* newItem = shortList_->pushAndRemove(item->getPriority(), item->accessData());
				if (newItem != nullptr) {
					list->add(newItem);
				}
			}
			longList_->clear();
			longList_->assign(*list);
			delete list;
		}
		return result;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		if (shortList_->size() == 0) {
			throw std::logic_error("PriorityQueueTwoLists<T>::peek: Short list is empty");
		}
		else 
			return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		return shortList_->peekPriority();
	}
}