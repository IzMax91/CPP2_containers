#include "test_header.h"

TEST(ConstructorMethod, MovePopFrontBackTest1) {
  s21::queue<int> qu0({90, 7, 49, 82});
  s21::queue<int> qu1({90, 7, 49, 82});
  s21::queue<int> qu2(std::move(qu1));
  s21::queue<int> qu3 = std::move(qu2);
  ASSERT_EQ(qu3.back(), qu0.back());
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(qu3.front(), qu0.front());
    qu0.pop();
    qu3.pop();
  }
}

TEST(ConstructorMethod, MovePopFrontBackTest2) {
  s21::queue<char> qu0({'h', 'q', '7', 'm'});
  s21::queue<char> qu1({'h', 'q', '7', 'm'});
  s21::queue<char> qu2(std::move(qu1));
  s21::queue<char> qu3 = std::move(qu2);
  ASSERT_EQ(qu3.back(), qu0.back());
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(qu3.front(), qu0.front());
    qu0.pop();
    qu3.pop();
  }
}

TEST(ConstructorMethod, SwapPushSizeEmptyTest) {
  s21::queue<int> qu1;
  s21::queue<int> qu2;
  ASSERT_EQ(qu1.size(), 0);
  ASSERT_EQ(qu2.size(), 0);
  ASSERT_EQ(qu1.empty(), 1);
  ASSERT_EQ(qu2.empty(), 1);
  qu1.push(90);
  qu2.push(13);
  ASSERT_EQ(qu1.size(), 1);
  ASSERT_EQ(qu2.size(), 1);
  ASSERT_EQ(qu1.empty(), 0);
  ASSERT_EQ(qu2.empty(), 0);
  qu1.push(3412);
  qu2.push(4901);
  ASSERT_EQ(qu1.size(), 2);
  ASSERT_EQ(qu2.size(), 2);
  ASSERT_EQ(qu1.empty(), 0);
  ASSERT_EQ(qu2.empty(), 0);
  qu1.push(-1325);
  qu2.push(-4512);
  ASSERT_EQ(qu1.size(), 3);
  ASSERT_EQ(qu2.size(), 3);
}

TEST(ConstructorMethod, SwapPushSizeEmptyTest2) {
  s21::queue<char> qu1;
  qu1.push(5);
  ASSERT_EQ(qu1.front(), 5);
}