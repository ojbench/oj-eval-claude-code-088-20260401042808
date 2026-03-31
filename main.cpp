#include <iostream>
#include <cmath>

using namespace std;

// Node structure for linked list
struct Node {
    long long value;
    Node* next;

    Node(long long val) : value(val), next(nullptr) {}
};

// Circular linked list for Subtask 1
class CircularLinkedList {
private:
    Node* head;
    long long size;

public:
    CircularLinkedList() : head(nullptr), size(0) {}

    ~CircularLinkedList() {
        if (!head) return;

        Node* current = head;
        Node* next_node;

        // Break the circular link
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        tail->next = nullptr;

        // Delete all nodes
        while (current) {
            next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    void initialize(long long n) {
        size = n;
        head = new Node(1);
        Node* current = head;

        for (long long i = 2; i <= n; i++) {
            current->next = new Node(i);
            current = current->next;
        }

        // Make it circular
        current->next = head;
    }

    long long getTop() {
        return head ? head->value : 0;
    }

    void performRound() {
        if (!head || head->next == head) return;

        // Step 1: Move first card to end
        head = head->next;

        // Step 2: Discard the (new) first card
        Node* to_delete = head;

        // Find the node before head
        Node* prev = head;
        while (prev->next != head) {
            prev = prev->next;
        }

        // Update links
        prev->next = head->next;
        head = head->next;

        delete to_delete;
        size--;
    }

    long long getSize() {
        return size;
    }
};

// Josephus problem solution for Subtask 2
long long josephus(long long n) {
    // Find the highest power of 2 less than or equal to n
    long long m = 0;
    long long power_of_2 = 1;

    while (power_of_2 * 2 <= n) {
        power_of_2 *= 2;
        m++;
    }

    // n = 2^m + l
    long long l = n - power_of_2;

    // Answer is 2*l + 1
    return 2 * l + 1;
}

void subtask1(long long n) {
    CircularLinkedList list;
    list.initialize(n);

    for (long long i = 0; i < n - 1; i++) {
        list.performRound();
        cout << list.getTop() << "\n";
    }
}

void subtask2(long long n) {
    cout << josephus(n) << "\n";
}

int main() {
    long long id, n;
    cin >> id >> n;

    if (id == 1) {
        subtask1(n);
    } else if (id == 2) {
        subtask2(n);
    }

    return 0;
}
