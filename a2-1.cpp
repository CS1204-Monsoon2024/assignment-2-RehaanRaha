#include <iostream>

using namespace std;

const int m = 1e9 + 7;  // Modulo to prevent overflow

// Node structure for the linked list

struct Node {
    int data;
    Node* next;

    // Constructor to initialize node data
    Node(int value) : data(value), next(nullptr) {}

};

// LinkedList with head and tail pointers
class HashLinkedList {
private:
    Node* head;       // head pointer
    Node* tail;       // tail pointer
    int size;         // no. of nodes in LL
    int hashValue;    // Hash value for the entire list
    const int prime = 31;  // Prime number used for hashing

public:
    // Constructor to initialize an empty linked list
    HashLinkedList() : head(nullptr), tail(nullptr), size(0), hashValue(0) {}

    // Insert function
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {  // Check if the list is empty
            head = tail = newNode;  // The new node is the head and the tail since the list is empty
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
        updateHash(val);  // Update hash whenever a new node is inserted
    }

    // Function to update the hash value as we insert new elements
    void updateHash(int val) {
        // Hash computation using a rolling hash method
        hashValue = (hashValue * prime + val) % m;
    }

    // Function to get the current hash value of the linked list
    int getHash() const {
        return hashValue;
    }

    // Search function - me searching for my grade in DSA
    bool search(int val) {  // bool is used since the function returns true/false
        Node* temp = head;
        while (temp) {
            if (temp->data == val) {  // Check if the current node's data matches the search value
                return true;  // The searched item exists
            }
            temp = temp->next;  // Move to the next node - it iterates throughout the list
        }
        return false;  // Element is absent - like my marks in the midsem
    }

    // Delete function
    void deleting(int val) {
        if (!head) {
            cout << "Element cannot be deleted since the list is empty" << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        // To delete the head node
        if (head->data == val) {
            temp = head;
            head = head->next;  // Set the head to one element ahead
            delete temp;         // Free the memory by deleting temp
            // If we want to update hash after deletion, we'd need to recalculate hash from scratch
            recalculateHash();
            return;
        }

        // Traverse the list to find the element to delete
        while (temp && temp->data != val) {
            prev = temp;         // Track the previous node
            temp = temp->next;   // Move to the next node
        }

        // If the value doesn't exist in the list
        if (!temp) {
            return;
        }

        // Unlink the node and delete it
        prev->next = temp->next;
        delete temp;  // Free the memory

        // Recalculate the hash after deletion
        recalculateHash();
    }

    // Function to recalculate the entire hash value after a deletion
    void recalculateHash() {
        hashValue = 0;  // Reset hash for each element
        Node* temp = head; // set the current node to temp
        while (temp) { // iterate through the list 
            updateHash(temp->data);  // Update hash for this particular element
            temp = temp->next;
        }
    }
};