#pragma once


#include <iostream>
template<typename T>
struct DataItem {
private:
    T data;
    int key;

public:
    DataItem(int key, T data) {
        this->key = key;
        this->data = data;
    }

    T getData() const {
        return this->data;
    }

    void setData(T data) {
        this->data = data;
    }

    int getKey() const {
        return this->key;
    }

    void setKey(int key) {
        this->key = key;
    }
};

template <typename T>
class HashTable {
    int SIZE;
    DataItem<T>** table;

    int hashCode(int key) {
        return key % this->SIZE;
    }

public:
    HashTable(int SIZE) {
        this->SIZE = SIZE;
        this->table = new DataItem<T> * [SIZE];

        for (int i = 0; i < SIZE; i++) {
            this->table[i] = new DataItem<T>(-1, -1);
        }

    }

    DataItem<T>* search(int key) {


        int hashIndex = hashCode(key);

        if (this->table[hashIndex]->getKey() == -1)
            return nullptr;

        for (int i = 0; i < this->SIZE; i++) {
            if (this->table[hashIndex]->getKey() == key)
                return this->table[hashIndex];

            //go to next cell
            ++hashIndex;

            hashIndex %= this->SIZE;
            //     std::cout << "search index: " <<hashIndex << std::endl;
        }

        return nullptr;
    }

    void insert(int key, T data) {
        DataItem<T>* newElement = new DataItem<T>(key, data);

        int hashIndex = hashCode(key);

        if (this->table[hashIndex]->getKey() == key) {
            //printf("Element with index: %d already exists \n", this->table[hashIndex]->getKey());
            return;
        }


        if (this->table[hashIndex]->getKey() == -1) {
            this->table[hashIndex] = newElement;
            return;
        }
        else {
            for (int j = 0; j < this->SIZE; j++) {
                int hashIndexWithQuadProbing = (hashIndex + j * j) % this->SIZE;

                //          printf("element: (%d,%d) ", this->table[hashIndexWithQuadProbing]->getKey(),
               //                  this->table[hashIndexWithQuadProbing]->getData());
               //           std::cout << "quad probing index: " << hashIndexWithQuadProbing << std::endl;
                          //  int tableKey = this->table[hashIndexWithQuadProbing]->getKey();

                if (this->table[hashIndexWithQuadProbing]->getKey() == -1) {
                    //            std::cout << "init of the table[" << hashIndexWithQuadProbing << "]" << std::endl;
                    this->table[hashIndexWithQuadProbing] = newElement;
                    return;
                }
            }
        }

    }

    void deleteItem(int key) {
        int hashIndex = hashCode(key);

        for (int i = 0; i < this->SIZE; i++) {

            if (this->table[hashIndex]->getKey() == key) {

                // set another item with key and data -1
                std::cout << "Item with key: " << this->table[hashIndex]->getKey()
                    << " was deleted" << std::endl;
                DataItem<T>* itemNoLongerExists = new DataItem<T>(-1, -1);
                this->table[hashIndex] = itemNoLongerExists;
                return;
            }
            //go to next cell
            ++hashIndex;

            hashIndex %= SIZE;
            //  std::cout << hashIndex << std::endl;
        }

        std::cout << "Item with key: " << key
            << " wasn't found" << std::endl;
    }

    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (this->table[i]->getKey() != -1)
                printf("(%d,%d)", this->table[i]->getKey(), this->table[i]->getData());
            else
                printf(" ~~ ");
        }
        printf("\n");
    }
};

