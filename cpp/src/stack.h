#ifndef STACK
#define STACK

struct Elem {
    int data {0};
    Elem* next {nullptr};

    Elem(int d) : data(d), next(nullptr) {}
};

class Stack {
    Elem* top {nullptr};

    void clear(Elem*);

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        clear(top);
    }

    void push(int);
    void pop();
    void print();
};

#endif 