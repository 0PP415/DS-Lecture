#include <iostream>

using namespace std;

template<typename T>
class SNode {
private:
    T item;
    SNode<T>* next;

    friend class SLL<T>;
};

template<typename T>
class SLL {
private:
    SNode<T>* head;

public:
    SLL(): head(nullptr) {}
    ~SLL() {
        while (!empty()) removeFront();
    }

    bool empty() const {
        return head == nullptr;
    }
    const T& front() const {
        return head->item;
    }
    void addFront(const T& e) {
        SNode<T>* n = new SNode<T>();
        n->item = e;
        
        n->next = head;
        head = n;
    }
    void removeFront() {
        SNode<T>* n = head;
        head = head->next;
        delete n;
    }


};

int main(void) {



    return EXIT_SUCCESS;
}