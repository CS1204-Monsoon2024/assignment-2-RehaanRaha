#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {

private:
    vector<int> table;  
    int m;              // The size of the hash table
    int numElements;    // The number of elements in the hash table
    double loadFactor_threshold = 0.8;  // The load factor of the hash table
    int max_probe_attempts = 50;

    // Hash function: h(k) = k % m
    int hashFunction(int key) {
        return key % m;  // Return the index by applying mod operation
    }

    // Prime checker function
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n == 3) return true;
        if (n % 2 == 0) return false;
        if (n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Time to find the next prime
    int nextPrime(int n) {
        while(!isPrime(n)) {
            n++;
        }
        return n;
    }

// Resizing table
    void resizeTable() {
        int old_m = m;
        m = nextPrime(2 * old_m); // Double and finding next nearest prime

        cout << "Table resized from" << old_m << "to" << m << endl;

        vector<int> old_table = table;
        table.clear();
        table.resize(m, -1); // Initialize the new table with -1
        numElements = 0; // Reset number of elements

        // Rehashing the old elements
        for (int i = 0; i < old_m; i++) {
            if (old_table[i] != -1) {
                insert(old_table[i]);  //Inserting the old elements into the new table
            }
        }
    }

    double loadFactor() {
        return (double)numElements / m;
    }



public:
    // Constructor
    HashTable(int size) {
        m = size;
        table.resize(m, -1); // Initialise table with size m, all values are -1
        numElements = 0; 
    }

    // Inserting key into Hash Table
    void insert(int key) {
        if (loadFactor() > loadFactor_threshold) {
            resizeTable(); 
        }

        int index = hashFunction(key); // Gotta get the Index Key
        int i = 0;
        int newIndex = index;

        // Quadtratic probing to find empty slot
        while (table[newIndex] != -1) {
            if (table[newIndex] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
            if (i > max_probe_attempts){
                cout << "Max probing limit reached!" << endl;
                return;
            }

            newIndex = (index + i * i) % m; // Quadratic probing done right unlike my quiz
        }

        table[newIndex] = key;
        numElements++; // Increment number of elements
    }

    // Search Function

    bool search(int key) {
        int index = hashFunction(key); 
        int i = 0;
        int newIndex = index;

        while (table[newIndex] != -1) {
            if(table[newIndex] == key) {
                return newIndex; // Found the key!
            }
            i++;
            newIndex = (index + i * i) % m; // Same Quadratic probing
        }

        return -1; // Not found :(
    }

    // Remove Function
    
    void remove(int key) {
        int index = search(key);

        if (index == -1) {
            cout << "Element not found" << endl;
            return;
        }

        table[index] = -1; // Marking cell as empty
        numElements--; // Decrement number of elements
    }

    


    // Displaying the hash table
    void printTable() {
        for (int i = 0; i < m; ++i) {
            if (table[i] == -1)
                cout << "- ";
            else
                cout << table[i] << " ";
        }
    }
};

