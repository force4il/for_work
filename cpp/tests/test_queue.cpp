#include <gtest/gtest.h>
#include "../src/queue.h"

TEST(QueueTest, PushAndPrint) {
    Queue q;
    q.push(10);
    
    testing::internal::CaptureStdout();
    q.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10 ");
    
    q.push(20);
    q.push(30);
    testing::internal::CaptureStdout();
    q.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10 20 30 ");
}

TEST(QueueTest, Pop) {
    Queue q;
    q.push(10);
    q.push(20);
    q.push(30);
    
    q.pop(); 
    testing::internal::CaptureStdout();
    q.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "20 30 ");
    
    q.pop();
    q.pop(); 
    testing::internal::CaptureStdout();
    q.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nПустой список\n");
}

TEST(QueueTest, PopEmpty) {
    Queue q;
    testing::internal::CaptureStdout();
    q.pop();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nОшибка удаления. Пустой список\n");
}

TEST(QueueTest, PopSingleElement) {
    Queue q;
    q.push(42);
    q.pop(); 
    
    testing::internal::CaptureStdout();
    q.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nПустой список\n");
}

TEST(QueueTest, PrintEmpty) {
    Queue q;
    testing::internal::CaptureStdout();
    q.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\nПустой список\n");
}