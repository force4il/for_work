#include <iostream>
#include "queue.h"

using std::cout;
using std::endl;

void Queue::clear(Item* item) {
    if (!item) return;

    clear(item->next);
    delete item;
}

void Queue::push(int value) {
    Item* item = new Item(value);   
    
    if (!head) {
        head = tail = item;
        return;
    }

    tail->next = item;
    tail = item;
}

void Queue::pop() {
    if (!head) {
        cout << "\nОшибка удаления. Пустой список" << endl;
        return;
    }

    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }

    Item* item = head;
    head = item->next;
    delete item;
}

void Queue::print() {
    if (!head) {
        cout << "\nПустой список" << endl;
        return;
    }

    Item* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}