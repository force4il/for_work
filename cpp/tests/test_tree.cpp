#include <gtest/gtest.h>
#include "../src/tree.h"

static void to_str_tree(Node* node, std::string& out) {
    if (!node) return;
    
    to_str_tree(node->left, out);
    out += std::to_string(node->data) + " ";
    to_str_tree(node->right, out);
}

TEST(TreeTest, PushRootAndChildren) {
    BinaryTree t;
    t.push(10);
    EXPECT_NE(t.get_root(), nullptr);
    EXPECT_EQ(t.get_root()->data, 10);
    
    t.push(5);
    t.push(15);
    EXPECT_EQ(t.get_root()->left->data, 5);
    EXPECT_EQ(t.get_root()->right->data, 15);
}

TEST(TreeTest, PushDuplicate) {
    BinaryTree t;
    t.push(10);
    t.push(10);
    
    EXPECT_EQ(t.get_root()->left, nullptr);
    EXPECT_EQ(t.get_root()->right, nullptr);
}

TEST(TreeTest, PopLeaf) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    t.push(15);
    
    t.pop(5);
    EXPECT_EQ(t.get_root()->left, nullptr);
    
    t.pop(15);
    EXPECT_EQ(t.get_root()->right, nullptr);
}

TEST(TreeTest, PopNodeWithOneChild) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    t.push(3); 
    
    t.pop(5);
    EXPECT_EQ(t.get_root()->left->data, 3);
}

TEST(TreeTest, PopNodeWithTwoChildren) {
    BinaryTree t;
    t.push(20);
    t.push(10);
    t.push(30);
    t.push(25);
    t.push(35);
    
    t.pop(30); 
    EXPECT_NE(t.get_root()->right, nullptr);
}

TEST(TreeTest, PopRoot) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    
    t.pop(10); 
    EXPECT_EQ(t.get_root()->data, 5);
}

TEST(TreeTest, PopNonExistent) {
    BinaryTree t;
    t.push(10);
    
    testing::internal::CaptureStdout();
    t.pop(999);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\nЗначение для удаления не найдено\n");
}

TEST(TreeTest, PopEmptyTree) {
    BinaryTree t;
    
    testing::internal::CaptureStdout();
    t.pop(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\nОшибка удаления. Пустое дерево\n");
}

TEST(TreeTest, Print) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    t.push(15);
    t.push(3);
    t.push(7);
    
    std::string result;
    to_str_tree(t.get_root(), result);
    EXPECT_EQ(result, "3 5 7 10 15 ");
}