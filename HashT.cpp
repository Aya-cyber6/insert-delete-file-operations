#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Node structure for the linked list within each hash table entry
struct Node {
    string name;
    int id;
    Node* next;

    // Constructor
    Node(const string& n, int i) : name(n), id(i), next(nullptr) {}
};

const int TABLE_SIZE = 10;

struct HashTable {
    Node* table[TABLE_SIZE]; // Array of linked list heads

    HashTable() {
        // Initialize all linked list heads to nullptr
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    // Hash function
    int hash(const string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % TABLE_SIZE;
    }

    // Function to add a student into the hash table
    void addStudent(const string& name, int id) {
        int index = hash(name);
        Node* newNode = new Node(name, id); // create new node
        newNode->next = table[index]; // assingn the new node to the current head(table[index])
        table[index] = newNode; // Update the head pointer to the new node
        saveChangesToFile("students.txt"); // Save changes to file after insertion
    }

    // Function to delete a student from the hash table
    void deleteStudenr(const string& name) {
        int index = hash(name);
        Node* current = table[index];
        Node* prev = nullptr;

        // Search for the student in the linked list
        while (current != nullptr && current->name != name) {
            prev = current;
            current = current->next;
        }

        // If student is found, remove it from the linked list
        if (current != nullptr) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            saveChangesToFile("students.txt"); // Save changes to file after deletion
        }
    }

    // Function to save changes to file
    void saveChangesToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
            return;
        }

        // Iterate over each bucket in the hash table
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = table[i];
            // Iterate over each node in the linked list at the current bucket
            while (current) {
                file << current->name << " " << current->id << endl;
                current = current->next;
            }
        }

        file.close();
    }

    // Function to print the hash table
    void printTable() {
        cout << "Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "[" << i << "]: ";
            Node* current = table[i];
            while (current) {
                cout << "Name: " << current->name << ", ID: " << current->id << " -> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }
};

// Function to read student information from file and add to hash table
void readStudentsFromFile(HashTable& hashtable, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int id;

        // Parse student information
        if (ss >> name >> id) {
            // Add student to hash table
            hashtable.addStudent(name, id);
        } else {
            cerr << "Warning: Unable to parse line: " << line << endl;
        }
    }

    file.close();
}

int main() {
    HashTable hashtable; // Create a hash table

    readStudentsFromFile(hashtable, "students.txt"); // Read student information from file and add to hash table

    hashtable.printTable(); // Print the hash table

    // Example usage of insert and delete functions
    hashtable.addStudent("Kate", 111); // Insert a new student
    hashtable.deleteStudenr("Ivy"); // Remove a student

    cout << "\nAfter modifications:" << endl;
    hashtable.printTable(); // Print the hash table after modifications

    return 0;
}
