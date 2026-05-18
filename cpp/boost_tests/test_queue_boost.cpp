#include "../src/queue.h"
#include "output.h"

BOOST_AUTO_TEST_SUITE(QueueBoostSuite)

BOOST_AUTO_TEST_CASE(PushAndPrint) {
    Queue q;
    q.push(10);
    
    {
        OutputCapture capture;
        q.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "10 ");
    }
    
    q.push(20);
    q.push(30);
    {
        OutputCapture capture;
        q.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "10 20 30 ");
    }
}

BOOST_AUTO_TEST_CASE(Pop) {
    Queue q;
    q.push(10);
    q.push(20);
    q.push(30);
    
    q.pop();
    {
        OutputCapture capture;
        q.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "20 30 ");
    }
    
    q.pop();
    q.pop();
    {
        OutputCapture capture;
        q.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "\nПустой список\n");
    }
}

BOOST_AUTO_TEST_CASE(PopEmpty) {
    Queue q;
    OutputCapture capture;
    q.pop();
    std::string output = capture.get_output();
    BOOST_TEST(output == "\nОшибка удаления. Пустой список\n");
}

BOOST_AUTO_TEST_CASE(PopSingleElement) {
    Queue q;
    q.push(42);
    q.pop();
    
    OutputCapture capture;
    q.print();
    std::string output = capture.get_output();
    BOOST_TEST(output == "\nПустой список\n");
}

BOOST_AUTO_TEST_CASE(BustTestManyOperations) {
    Queue q;
    for (int i = 0; i < 5000; i++) {
        q.push(i);
    }
    
    for (int i = 0; i < 2500; i++) {
        q.pop();
    }
    
    OutputCapture capture;
    q.print();
    std::string output = capture.get_output();
    BOOST_TEST(!output.empty());
}

BOOST_AUTO_TEST_SUITE_END()