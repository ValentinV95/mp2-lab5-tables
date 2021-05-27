#pragma once
#include <iostream>

template <typename K, typename T>
class Ordered
{private:
	struct Node {
		Node() {
			prev = nullptr;
			next = nullptr;
		}

		Node(K k, T d) {
			key = k;
			data = d;
			next = nullptr;
			prev = nullptr;
		}

		Node* next;
		Node* prev;
		T data;
		K key;
	};

	Node* head;
public:
	
	Ordered() {
		head = nullptr;
	}

	bool empty() {
		return (head == nullptr);
	}

	void add(K k, T d) {
		Node* n = new Node(k, d);
		if (head == nullptr) {
			head = n;
			return;
		}

		auto temp = head;

		while ((temp->next != nullptr)&&(temp->key < k)) {
			temp = temp->next;
		}

		if (temp->next != nullptr) {
			if (temp->key == k) {
				temp->data = d;
				return;
			}
			if (temp != head) {
				temp = temp->prev;
				n->next = temp->next;
				temp->next = n;
				n->prev = temp;
				n->next->prev = n;
				return;
			}
			else {
				head->next = n;
				n->prev = head;
				return;
			}
		}
		else {
			if (temp->key == k) {
				temp->data = d;
				return;
			}
			if (temp->key > k) {
				if (temp != head) {
					temp = temp->prev;
					n->next = temp->next;
					temp->next = n;
					n->prev = temp;
					n->next->prev = n;
					return;
				}
				else {
					head->next = n;
					n->prev = head;
					return;
				}
			}

			temp->next = n;
			n->prev = temp;
		}
	}

	T find(K k) {
		auto temp = head;
		while (temp != nullptr) {
			if (temp->key == k) {
				return temp->data;
			}
			temp = temp->next;
		}
		if (temp == nullptr) {
			return T();
		}
	}

	void remove(K k) {
		auto temp = head;

		while (temp != nullptr) {
			if (temp->key == k) {
				if (temp == head) {
					head = head->next;
					head->prev = nullptr;
					delete(temp);
					return;
				}
				if (temp->next != nullptr) {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
				else {
					temp->prev->next = temp->next;
				}

				delete(temp);
				return;
			}
			temp = temp->next;
		}
	}
	//for testing only
	void cprint() {
		if (head != nullptr) {
			auto temp = head;
			while (temp != nullptr) {
				std::cout << "\nkey:\t" << temp->key << "\tdata(int):\t" << temp->data;
				temp = temp->next;
			}
		}
	}
};

