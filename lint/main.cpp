#include <iostream>
#include <memory>

struct object
{
    int data;
    std::shared_ptr<object> next;
};

using shared_obj_ptr = std::shared_ptr<object>;
using std::cin;
using std::cout;
using std::endl;
using std::make_shared;

void push_back(shared_obj_ptr &head, shared_obj_ptr &tail, int data)
{
    shared_obj_ptr obj = make_shared<object>();
    obj->data = data;
    if (head == nullptr)
        head = obj;
    if (tail != nullptr)
        tail->next = obj;
    tail = obj;
}

void pop_front(shared_obj_ptr &head, shared_obj_ptr &tail)
{
    if (head == nullptr)
        return;
    if (head == tail)
    {
        head.reset();
        tail.reset();
        return;
    }

    shared_obj_ptr obj{head};
    head.reset(obj->next.get());
    obj.reset();
}

void show(const shared_obj_ptr &head)
{
    shared_obj_ptr cur = head;
    while (cur != nullptr)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

int main(void)
{
    // здесь продолжайте функцию main
    shared_obj_ptr head = nullptr, tail = nullptr;
    push_back(head, tail, 1);
    push_back(head, tail, 2);
    push_back(head, tail, 3);
    push_back(head, tail, 4);

    show(head);

    return 0;
}