// hash_table


#include <iostream>

using namespace std;

class HashTable {
private:

	int capacity;
	int** table;

	int const_c, const_d;

public:

	HashTable();
	HashTable(int capacity);
	int hashFunction(int key);
	void insertItem(int key, int data);

	int getPrime(int value);
	bool checkPrime(int value);

};

HashTable::HashTable()
{
	int size = this->capacity = 1;
	table = new int* [size];

	for (int i = 0; i < this->capacity; i++) {
		table[i] = nullptr;
	}
}

HashTable::HashTable(int capacity)
{
	int size = getPrime(capacity);
	this->capacity = size;
	table = new int* [size];

	for (int i = 0; i < this->capacity; i++) {
		table[i] = nullptr;
	}
}

int HashTable::hashFunction(int key)
{
	int hash_value, final_value, i = 1;

	hash_value = key % capacity;
	final_value = hash_value;

	while (table[final_value] != nullptr) {
		final_value = (hash_value + const_c * i + const_d * i * i) % this->capacity;
		i++;
	}

	return final_value;
}

void HashTable::insertItem(int key, int data)
{
	int index = hashFunction(key);
	table[index][0] = data;
}

int HashTable::getPrime(int value)
{
	if (value <= 1)
		return false;

	if (value % 2 == 0)
		value++;

	while (!checkPrime(value))
		value += 2;

	return value;
}

bool HashTable::checkPrime(int value)
{
	if (value <= 1)
		return false;

	for (int i = 2; i < value; i++)
		if (value % i == 0)
			return false;

	return true;
}

int main() {



	return 0;

}

