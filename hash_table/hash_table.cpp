// hash_table


#include <iostream>

using namespace std;

class HashTable {
private:

	int capacity;
	int fullness;
	int** table;

	int const_c, const_d;

public:

	HashTable();
	HashTable(int capacity);
	int hashFunction(int key);
	void insertItem(int key, int data);
	void checkSize();

	int getPrime(int value);
	bool checkPrime(int value);
	void set_constant_values();

	void displayHash();

private:
	void setCapacity();

};

HashTable::HashTable()
{
	int size = this->capacity = 1;
	table = new int* [size];

	for (int i = 0; i < this->capacity; i++) {
		table[i] = nullptr;
	}

	set_constant_values();
}

HashTable::HashTable(int capacity)
{
	int size = getPrime(capacity);
	this->capacity = size;
	table = new int* [size];

	for (int i = 0; i < this->capacity; i++) {
		table[i] = nullptr;
	}

	set_constant_values();
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
	this->fullness++;
	checkSize();
	int index = hashFunction(key);
	table[index] = new int(data);
}

int HashTable::getPrime(int value)
{
	if (value <= 1)
		return false;

	if (value % 2 == 0)
		value++;

	do 
	{
		value += 2;
	}
	while (!checkPrime(value));

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

void HashTable::set_constant_values()
{
	this->const_c = rand() % this->capacity;
	this->const_d = rand() % this->capacity;
}

void HashTable::checkSize()
{
	double fraction = (this->fullness / this->capacity) * 100;
	
	if (fraction > 75)
		setCapacity();

}

void HashTable::setCapacity()
{
	int new_capacity = getPrime(this->capacity);
	this->capacity = new_capacity;
	set_constant_values();
}

void HashTable::displayHash()
{
	for (int i = 0; i < this->capacity; i++) 
	{
		cout << "table[" << i << "]";
		cout << "-->" << this->table[i][0];
		cout << endl;
	}
}

int main() 
{

	int keys[] = { 1234567, 2345678, 3456789, 4567890, 5678901, 6789012, 7890123 };
	int values[] = { 1, 2, 3, 4, 5, 6, 7 };
	int size = sizeof(values) / sizeof(values[0]);


	HashTable ht = HashTable(size);

	for (int i = 0; i < size; i++)
		ht.insertItem(keys[i], values[i]);

	ht.displayHash();

	ht.insertItem(123, 444);
	ht.insertItem(124, 555);
	ht.insertItem(125, 666);

	ht.displayHash();

	return 0;
}

