#include <gtest/gtest.h>
#include "../src/stack.h"

TEST(StackTest, PushAndPrint) {
    Stack s;
    s.push(10);
    
    testing::internal::CaptureStdout();
    s.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10 ");
    
    s.push(20);
    testing::internal::CaptureStdout();
    s.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "20 10 ");
}

TEST(StackTest, Pop) {
    Stack s;
    s.push(10);
    s.push(20);
    
    s.pop();
    testing::internal::CaptureStdout();
    s.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10 ");
    
    s.pop();
    testing::internal::CaptureStdout();
    s.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nПустой стeк\n");
}

TEST(StackTest, PopEmpty) {
    Stack s;
    testing::internal::CaptureStdout();
    s.pop();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nОшибка удаления. Пустой стек\n");
}

TEST(StackTest, PrintEmpty) {
    Stack s;
    testing::internal::CaptureStdout();
    s.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nПустой стeк\n");
}