#include <iostream>
#include <vector>
#include <list>

typedef unsigned long long UInt64;
typedef unsigned int UInt32;

template <class T>
struct hash_node
{
	UInt64 key_;
	T val_;

	hash_node(UInt64 key, T val) :
	key_(key),
	val_(val)
	{}
	hash_node(const hash_node& hn)
	{
		key_ = hn.key_;
		val_ = hn.val_;
	}
};

template <class T>
class hash_table
{
private:
	friend class hash_table;
	std::vector<std::list<hash_node<T>* > > * table;
	UInt32 sz_;
public:
	// constructor
	hash_table(size_t sz);
	// destructor
	~hash_table();
	// copy constructor
	hash_table(const hash_table<T>& tbl);
	// copy assignment operator overload
	hash_table& operator=(const hash_table<T>& tbl);
	// insert a key and value pair into the table
	void insert(UInt64 key, T val);
	// look up an element in the table
	T& look_up(UInt64 key);
	// [] operator overload to look up
	// an element
	T& operator[](UInt64 key);
	// remove an element from the table
	// and return a copy
	T remove(UInt64 key);
	// get the size of the table
	size_t size();

};

// constructor
template <class T>
hash_table<T>::hash_table(size_t sz)
{
	table = new std::vector<std::list<hash_node<T>* > >(sz);
	sz_ = sz;
}

// destructor
template <class T>
hash_table<T>::~hash_table()
{
	delete table;
}

// copy constructor
template <class T>
hash_table<T>::hash_table(const hash_table<T>& tbl)
{
	for (int i = 0; i < tbl.table->size(); i++) {
		table->push_back(std::list<hash_node<T>*> ());
		for (auto it = tbl.table->at(i).begin(); 
			it != tbl.table->at(i).end(); it++) {
			table->at(i).push_back(new hash_node<T>(*it));
		}
	}
}

// copy assignment operator overload
template <class T>
hash_table<T>& hash_table<T>::operator=(const hash_table<T>& tbl)
{
	table->clear();
	for (int i = 0; i < tbl.table->size(); i++) {
		table->push_back(std::list<hash_node<T>*> ());
		for (auto it = tbl.table->at(i).begin(); 
			it != tbl.table->at(i).end(); it++) {
			table->at(i).push_back(new hash_node<T>(*it));
		}
	}
}

// insert a key and value pair into the table
template <class T>
void hash_table<T>::insert(UInt64 key, T val)
{

	table->at(key % sz_).push_back(new hash_node<T>(key,val));
}

// look up an element in the table
template <class T>
T& hash_table<T>::look_up(UInt64 key)
{
	for (auto it = table->at(key % sz_).begin(); 
		it != table->at(key % sz_).end(); it++) {
		if ((*it)->key_ == key) {
			return (*it)->val_;
		}
	}
	T * tmp = new T();
	return *tmp;
}

// [] operator overload to look up
// an element
template <class T>
T& hash_table<T>::operator[](UInt64 key)
{
	for (auto it = table->at(key % sz_).begin(); 
		it != table->at(key % sz_).end(); it++) {
		if ((*it)->key_ == key) {
			return (*it)->val_;
		}
	}
	T * tmp = new T();
	return *tmp;
}

// remove an element from the table
// and return a copy
template <class T>
T hash_table<T>::remove(UInt64 key)
{
	T tmp;
	for (auto it = table->at(key % sz_).begin(); 
		it != table->at(key % sz_).end(); it++) {
		if ((*it)->key_ == key) {
			tmp = (*it)->val_;
			table->at(key % sz_).erase(it);
			return tmp;
		}
	}
	tmp = T();
	return tmp;
}

template <class T>
size_t hash_table<T>::size()
{
	size_t sz = 0;
	for (int i = 0; i < table->size(); i++) {
		sz += table->at(i).size();
	}
	return sz;
}
