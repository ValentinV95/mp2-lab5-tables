// DataItem methods
/*#include "HashTable.h"

// DataItem methods
DataItem::DataItem(int key, int data) {
    this->key = key;
    this->data = data;
}

int DataItem::getData() const {
    return this->data;
}

void DataItem::setData(int data) {
    this->data = data;
}

int DataItem::getKey() const {
    return this->key;
}

void DataItem::setKey(int key) {
    this->key = key;
}


// HashTable methods
HashTable::HashTable(int SIZE) {
    this->SIZE = SIZE;
    this->table = new DataItem * [SIZE];

    for (int i = 0; i < SIZE; i++) {
        this->table[i] = new DataItem(-1, -1);
    }

}

int HashTable::hashCode(int key) {
    return key % this->SIZE;
}

DataItem* HashTable::search(int key) {


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

void HashTable::insert(int key, int data) {
    DataItem* newElement = new DataItem(key, data);

    int hashIndex = hashCode(key);

    if (this->table[hashIndex]->getKey() == key) {
        printf("Element with index: %d already exists \n", this->table[hashIndex]->getKey());
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

void HashTable::deleteItem(int key) {
    int hashIndex = hashCode(key);

    for (int i = 0; i < this->SIZE; i++) {

        if (this->table[hashIndex]->getKey() == key) {

            // set another item with key and data -1
            std::cout << "Item with key: " << this->table[hashIndex]->getKey()
                << " was deleted" << std::endl;
            DataItem* itemNoLongerExists = new DataItem(-1, -1);
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

void HashTable::display() {

    for (int i = 0; i < SIZE; i++) {
        if (this->table[i]->getKey() != -1)
            printf("(%d,%d)", this->table[i]->getKey(), this->table[i]->getData());
        else
            printf(" ~~ ");
    }

    printf("\n");
}*/