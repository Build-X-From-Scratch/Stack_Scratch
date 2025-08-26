#include <gtest/gtest.h>
#include "../src/stack.cpp"    

TEST(Stack, IntialValue){
    Stack stack1(100);
    EXPECT_EQ(stack1.get_capacity(),100);
}

TEST(Stack,push){
    Stack Stack1(100);
    Stack1.push(1);
    EXPECT_EQ(Stack1.get_size(),1);
    EXPECT_EQ(Stack1.get_capacity(),100);
    EXPECT_EQ(Stack1.top(),1);
}   
TEST(Stack,multiple_element){
    Stack Stack1(100);
    Stack1.push(1);
    Stack1.push(2);
    Stack1.push(3);
    EXPECT_EQ(Stack1.get_size(),3);
    EXPECT_EQ(Stack1.get_capacity(),100);
    EXPECT_EQ(Stack1.top(),3);
}