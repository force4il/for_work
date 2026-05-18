#include "../src/stack.h"
#include "output.h"

BOOST_AUTO_TEST_SUITE(StackBoostSuite)

BOOST_AUTO_TEST_CASE(PushAndPrint) {
    Stack s;
    s.push(10);
    
    {
        OutputCapture capture;
        s.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "10 ");
    }
    
    s.push(20);
    {
        OutputCapture capture;
        s.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "20 10 ");
    }
}

BOOST_AUTO_TEST_CASE(Pop) {
    Stack s;
    s.push(10);
    s.push(20);
    
    s.pop();
    {
        OutputCapture capture;
        s.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "10 ");
    }
    
    s.pop();
    {
        OutputCapture capture;
        s.print();
        std::string output = capture.get_output();
        BOOST_TEST(output == "\nПустой стeк\n");
    }
}

BOOST_AUTO_TEST_CASE(PopEmpty) {
    Stack s;
    OutputCapture capture;
    s.pop();
    std::string output = capture.get_output();
    BOOST_TEST(output == "\nОшибка удаления. Пустой стек\n");
}

BOOST_AUTO_TEST_CASE(PrintEmpty) {
    Stack s;
    OutputCapture capture;
    s.print();
    std::string output = capture.get_output();
    BOOST_TEST(output == "\nПустой стeк\n");
}

BOOST_AUTO_TEST_CASE(BustTestManyPushPop) {
    Stack s;
    for (int i = 0; i < 1000; i++) {
        s.push(i);
    }
    
    for (int i = 0; i < 500; i++) {
        s.pop();
    }
    
    OutputCapture capture;
    s.print();
    std::string output = capture.get_output();
    BOOST_TEST(!output.empty());
    BOOST_TEST(output != "\nПустой стeк\n");
}

BOOST_AUTO_TEST_SUITE_END()