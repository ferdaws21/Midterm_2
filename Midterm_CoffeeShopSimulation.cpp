#include <iostream>
#include <string>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        string data;  // Customer name
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Add a customer at the end of the line
    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Add a VIP customer at the front of the line
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Serve the customer at the front of the line (remove first customer)
    void pop_front() {
        if (!head) {
            cout << "Line is empty." << endl;
            return;
        }
        Node* temp = head;
        cout << temp->data << " is served." << endl;
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    // Remove the last customer from the line (rear leaves due to frustration)
    void pop_back() {
        if (!tail) {
            cout << "Line is empty." << endl;
            return;
        }
        Node* temp = tail;
        cout << temp->data << " (at the rear) left the line." << endl;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete temp;
    }

    // Print the current state of the line
    void print() {
        Node* current = head;
        if (!current) {
            cout << "Line is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // A customer decides to leave the line from a random position
    void remove_random_customer() {
        if (!head) return;
        
        // Single customer case, pop them from the front
        if (!head->next) {
            cout << head->data << " left the line." << endl;
            pop_front();
            return;
        }

        // Select a random position to remove
        Node* temp = head;
        int pos = rand() % 10 + 1;  // Random position
        for (int i = 1; i < pos && temp->next; ++i) {
            temp = temp->next;
        }
        cout << temp->data << " left the line." << endl;
        
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        if (temp == head) head = temp->next;
        if (temp == tail) tail = temp->prev;

        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    // Seed random number generator
    srand(time(0));

    DoublyLinkedList coffeeLine;
    
    // List of names provided
    string names[] = {"Zane", "Zara"};
    int numNames = 2;

    // Store opens, add 5 customers initially
    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; ++i) {
        string customer = names[rand() % numNames];
        coffeeLine.push_back(customer);
        cout << customer << " joins the line." << endl;
    }
    
    // Print initial line
    cout << "Resulting line: ";
    coffeeLine.print();
    
    // Simulation for 20 time steps (minutes)
    for (int t = 2; t <= 20; ++t) {
        cout << "Time step #" << t << ":" << endl;
        
        // 40% chance a customer is served
        if (rand() % 100 < 40) {
            if (rand() % 100 < 10) {
                coffeeLine.remove_random_customer();  // Random customer leaves with 10% probability
            } else {
                coffeeLine.pop_front();  // Serve the first customer
            }
        }
        
        // 60% chance a customer joins the line
        if (rand() % 100 < 60) {
            string customer = names[rand() % numNames];
            coffeeLine.push_back(customer);
            cout << customer << " joins the line." << endl;
        }

        // 10% chance VIP skips the line
        if (rand() % 100 < 10) {
            string vipCustomer = names[rand() % numNames];
            coffeeLine.push_front(vipCustomer);
            cout << vipCustomer << " (VIP) joins the front of the line." << endl;
        }

        // 20% chance the last customer gets frustrated and leaves
        if (rand() % 100 < 20) {
            coffeeLine.pop_back();
        }

        // Print resulting line
        cout << "Resulting line: ";
        coffeeLine.print();
    }

    return 0;
}
