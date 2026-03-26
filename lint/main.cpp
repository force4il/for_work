// cppcheck --suppress=missingIncludeSystem main.cpp
// cppcheck -q --enable=all --inconclusive main.cpp
#include <iostream>
#include <memory>

struct object {
    int data;
    std::shared_ptr<object> next;
};

using shared_obj_ptr = std::shared_ptr<object>;
using std::cin;
using std::cout;
using std::endl;
using std::make_shared;

void push_back(shared_obj_ptr &head, shared_obj_ptr &tail, int data) {
    shared_obj_ptr obj = make_shared<object>();
    obj->data = data;
    if (head == nullptr) {
        head = obj;
    } else if (tail != nullptr) {
        tail->next = obj;
    }
    tail = obj;
}

void pop_front(shared_obj_ptr &head, shared_obj_ptr &tail) {
    if (head == nullptr) return;
    if (head == tail) {
        head.reset();
        tail.reset();
        return;
    }
    head = head->next; 
}

void show(const shared_obj_ptr &head) {
    shared_obj_ptr cur = head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

void insert(shared_obj_ptr &head, shared_obj_ptr &tail, const shared_obj_ptr &prev, int data) {
    shared_obj_ptr obj = make_shared<object>();
    obj->data = data;

    if (prev == nullptr) {
        obj->next = head;
        head = obj;
        if (tail == nullptr) {
            tail = obj;
        }
        return;
    }

    obj->next = prev->next;
    prev->next = obj;

    if (prev == tail) {
        tail = obj;
    }
}

int capacity(const shared_obj_ptr &head) {
    int cnt = 0;
    shared_obj_ptr cur = head;
    while (cur != nullptr) {
        cnt++;
        cur = cur->next;
    }

    return cnt;
}

int main() {
    shared_obj_ptr head = nullptr, tail = nullptr;
    push_back(head, tail, 1);
    push_back(head, tail, 2);
    push_back(head, tail, 3);
    push_back(head, tail, 4);
    pop_front(head, tail);

    cout << "Current size: " << capacity(head) << endl;

    shared_obj_ptr cur = head;
    while (cur != nullptr && cur->data != 2) {
        cur = cur->next;
    }

    if (cur != nullptr) {
        insert(head, tail, cur, 77);
    }

    show(head);
    cout << endl;

    return 0;
}