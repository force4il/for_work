#ifndef QUEUE
#define QUEUE

struct Item {
    int data {0};
    Item* next {nullptr};

    Item(int d) : data(d), next(nullptr) {}
};

class Queue {
    Item* head {nullptr};
    Item* tail {nullptr};

    void clear(Item*);
            
public:
    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        clear(head);
    }

    void push(int);
    void pop();
    void print();
};

#endif