#pragma once
#include <iostream>

template <typename T>
struct element
{
	element() {
		data = T();
	}

	element(T d) :data(d) {	}

	T data;
};

template <typename T>
class unordered
{
private:
	struct node {

		node(int k, element<T> elem) {
			key = k;
			pelem = new element<T>(elem.data);
			next = nullptr;
		}

		int key;
		element<T>* pelem;
		node* next;
	};

	node* head;

public:

	unordered() {
		head = nullptr;
	}

	bool empty() {
		return (head == nullptr);
	}

	void cprint() {
		if (head != nullptr) {
			auto temp = head;
			while (temp != nullptr) {
				std::cout << "\nkey:\t" << temp->key << "\tdata(int):\t" << temp->pelem->data;
				temp = temp->next;
			}
		}
	}

	element<T> find(int key) {
		node* temp = head;
		while ((temp != nullptr) && (temp->key != key)) {
			temp = temp->next;
		}
		if (temp != nullptr) {
			return *(temp->pelem);
		}
		return element<T>();

	}

	void remove(int k) {
		if (head != nullptr) {
			node* temp = head;

			if (head->key == k) {
				head = head->next;
				delete(temp);
				return;
			}

			while ((temp->next != nullptr) && (temp->next->key != k)) {
				temp = temp->next;
			}

			if (temp->next != nullptr) {
				if (temp->next->key != k) {
					return;
				}
				node* n = temp->next;
				temp->next = temp->next->next;
			}

		}
		return;
	}

	void add(int k, T data) {
		element<T> elem = element<T>(data);
		if (head == nullptr) {
			node* n = new node(k, elem);
			head = n;
		}
		else {
			node* temp = head;
			while ((temp->next != nullptr) && (temp->key != k)) {
				temp = temp->next;
			}
			if (temp->key == k) {
				temp->pelem = new element<T>(elem.data);
				return;
			}
			node* n = new node(k, elem);
			temp->next = n;
		}
	}

	element<T>& operator[] (const int k) {
		node* temp = head;
		if (temp != nullptr) {
			while ((temp != nullptr) && (temp->key != k)) {
				temp = temp->next;
			}
			auto nel = element<T>();
			if (temp != nullptr) {
				temp->pelem;
				return *(temp->pelem);
			}
			return nel;
		}
	}
};

