/**
 * @file IdMap.h
 * @author AokiMinoru (personal-git@aokiminoru.work)
 * @brief Equatable付きクラスのmap
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ID_MAP_H
#define ID_MAP_H
/*
#include <vector>
#include <utility>
#include "Equatable.h"
#include "TypeExtensions.h"


class IdVector: public std::vector<Equatable> {
	public:
	Equatable* first() {
		return this->isEmpty() ? NULL : &this->front();
	}
	
	Equatable* first(uuid_t id) {
		for(int i = 0; i < this->size(); i++) {
			if(uuid_compare(this->at(i).id, id) == 0) {
				return &this->at(i);
			}
		}
		return NULL;
	}

	int index(uuid_t id) {
		for(int i = 0; i < this->size(); i++) {
			if(uuid_compare(this->at(i).id, id) == 0) {
				return i;
			}
		}
		return -1;
	}
	

	Equatable* last() {
		return this->isEmpty() ? NULL : &this->back();
	}

	bool isEmpty() {
		return this->empty();
	}

	bool contains(uuid_t id) {
		for(int i = 0; i < this->size(); i++) {
			if(uuid_compare(this->at(i).id, id) == 0) {
				return true;
			}
		}
		return false;
	}

	void append(Equatable data) {
		this->push_back(data);
	}
	
	void remove(uuid_t id) {
		int index = this->index(id);
		if(index >= 0) {
			this->erase(this->begin() + this->index(id));
		}
	}

	void removeFirst() {
		this->erase(this->begin());
	}

	void removeLast() {
		this->pop_back();
	}

	void removeAll() {
		this->clear();
	}

	int count() {
		return this->size();
		//void test(Equatable hoge&) {printfDx("id: ", hoge.id);}
		
		//ForEach<Equatable>(this, test);
		std::vector<int> nums { 1, 2, 3, 4, 5 };
	//ForEach<int>(nums, [](int &num){ printfDx("%d", num); });
	ForEach<std::vector<int>>(nums, [](int &num) { printfDx("%d", num);  });

	std::vector<Equatable> VecTest;
	VecTest.push_back(Equatable());
	Filter(VecTest, [](Equatable &item){return item.id[0] == 'a';});
	}
};
*/
// TODO: map, reduce, filter
	

	

#endif