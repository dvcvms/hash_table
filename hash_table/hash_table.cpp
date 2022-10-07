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
	~HashTable();

	void insertItem(int key, int data);
	void deleteItem(int key);
	void displayHash();

private:

	int hashFunction(int key, int selector);
	void checkSize();
	void increaseTableSize(int new_capacity);

	void setCapacity(int key);
	int getPrime(int value);
	bool checkPrime(int value);
	void set_constant_values();
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

int HashTable::hashFunction(int key, int selector)
{
	int hash_value, final_value, i = 1;

	hash_value = key % capacity;
	final_value = hash_value;

	if (selector == 1) {
		while (table[final_value] != nullptr) {
			final_value = (hash_value + const_c * i + const_d * i * i) % this->capacity;
			i++;
		}
	}

	return final_value;
}

void HashTable::insertItem(int key, int data)
{
	this->fullness++;
	checkSize();
	int index = hashFunction(key, 1);
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

	for (int i = 2; i <= round(sqrt(value)); i++)
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
	double fraction = ((double) this->fullness / this->capacity) * 100;


	if (fraction > 75)
		setCapacity(this->capacity);
	
	if (fraction < 25 && fullness > 15)
		setCapacity(this->fullness);



	
}

void HashTable::increaseTableSize(int new_capacity)
{
	//int new_index;
	int** new_table;
	new_table = new int* [new_capacity];
	
	for (int i = 0; i < new_capacity; i++)
		new_table[i] = nullptr;

	for (int i = 0; i < this->capacity; i++)
		if (this->table[i] != nullptr) {
			//new_index = hashFunction(i);
			//cout << this->table[i] << endl;
			//cout << this->table[i][0];
			
			new_table[i] = this->table[i];
		}

	this->table = new_table;
}

void HashTable::setCapacity(int key)
{
	int new_capacity = getPrime(key);
	increaseTableSize(new_capacity);
	this->capacity = new_capacity;
	set_constant_values();
}

void HashTable::displayHash()
{
	for (int i = 0; i < this->capacity; i++) 
	{
		cout << "table[" << i << "]";
		
		if (this->table[i] != nullptr)
			cout << "-->" << this->table[i][0];
		else
			cout << "-->null";
		
		cout << endl;
	}
}

void HashTable::deleteItem(int key) 
{
	int index = hashFunction(key, 0);

	if (this->table[index] != nullptr)
	{
		delete this->table[index];
		this->table[index] = nullptr;
	}

	this->fullness--;
	checkSize();
}

HashTable::~HashTable() 
{
	for (int i = 0; i < this->capacity; i++)
		delete this->table[i];

	delete this->table;

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
	
	cout << endl << endl;
	
	ht.displayHash();

	ht.deleteItem(7890123);

	cout << endl << endl;

	ht.displayHash();

	return 0;
}

