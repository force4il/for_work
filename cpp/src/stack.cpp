#include <iostream>
#include "stack.h"

using std::cout;
using std::endl;

void Stack::push(int value) {
    Elem* new_elem = new Elem(value);

    if (!top) {
        top = new_elem;
        return;
    }

    new_elem->next = top;
    top = new_elem;
}

void Stack::pop() {
    if (!top) {
        cout << "\nОшибка удаления. Пустой стек" << endl;
        return;
    }

    if (top->next == nullptr) {
        delete top;
        top = nullptr;
        return;
    }

    Elem* elem = top->next;
    delete top;
    top = elem;
}

void Stack::print() {
    if (!top) {
        cout << "\nПустой стeк" << endl;
        return;
    }

    Elem* cur = top;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

void Stack::clear(Elem* elem) {
    if (!elem) return;

    clear(elem->next);
    delete elem;
}