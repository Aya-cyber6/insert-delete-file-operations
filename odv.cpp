#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
struct LinkedList
{
    string name;
    int age;
    LinkedList* next;
    LinkedList (const string& n, int i) : name(n), age(i), next(nullptr) {}
};

string line;
LinkedList myList;
ifstream myFile("students.txt");

while (getline(myFile, line))
{
    addToList(myList, line);

}
myFile.close();

void addToList(LinkedList &list, string data) {
    Node* newNode = new Node(data);
    newNode->next = list.head;
}