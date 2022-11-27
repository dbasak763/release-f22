/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
    elems++;
    double ratio = (double)elems / size;
    if (ratio >= 0.7) {
        resizeTable();
        std::cout << "new size: " << size << std::endl;
    }
    size_t original_hash_index = hashes::hash(key, size);
    size_t hash_index = original_hash_index;
    size_t k = 0;
    while (table[hash_index] != NULL) {
        k++;
        hash_index = (original_hash_index + k) % size;
    }
    table[hash_index] = new std::pair<K, V>(key, value);
    should_probe[hash_index] = true;
  
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    int i = findIndex(key);
    if (i != -1) {
        delete table[i];
        table[i] = NULL;
        --elems;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    unsigned int hash_index = hashes::hash(key, size);
    size_t m = size;
    while (m > 0) {
        if (table[hash_index] != NULL) {
            if (table[hash_index] -> first == key) {
                return hash_index;
            }
        } else {
            if (!should_probe[hash_index]) {
                return -1;
            }
        }
        hash_index++;
        if (hash_index == size) {
            hash_index = 0;
        }
        m--;
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     size_t new_size = findPrime(size * 2);
     std::pair<K, V>** new_table = new std::pair<K, V>*[new_size];
     delete[] should_probe;
     should_probe = new bool[new_size];
     for (size_t i = 0; i < new_size; i++) {
        new_table[i] = NULL;
        should_probe[i] = false;
     }
     for (size_t i = 0; i < size; i++) {
        if (table[i] != NULL) {
            size_t new_hash_index = hashes::hash(table[i]->first, new_size);
            size_t final_hash_index = new_hash_index;
            size_t k = 0;
            while (new_table[final_hash_index] != NULL) {
                k++;
                final_hash_index = (new_hash_index + k) % new_size;
            }
            new_table[final_hash_index] = table[i];
            should_probe[final_hash_index] = true;
        }
     }
     delete[] table;
     size = new_size;
     table = new_table;
}
