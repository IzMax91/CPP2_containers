#include "test_header.h"

TEST(Constructor, MoveTest1) {
  s21::stack<int> st0({90, 7, 49, 82});
  s21::stack<int> st1({90, 7, 49, 82});
  s21::stack<int> st2(std::move(st1));
  s21::stack<int> st3 = std::move(st2);
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st3.top(), st0.top());
    st3.pop();
    st0.pop();
  }
}

TEST(Constructor, MoveTest2) {
  s21::stack<char> st0({'g', 'q', 'H', '6'});
  s21::stack<char> st1({'g', 'q', 'H', '6'});
  s21::stack<char> st2(std::move(st1));
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st2.top(), st0.top());
    st2.pop();
    st0.pop();
  }
}

TEST(Constructor, MoveTest3) {
  s21::stack<float> st0({
      1.7f,
      9.5f,
      55.1f,
      -13.4f,
  });
  s21::stack<float> st1({
      1.7f,
      9.5f,
      55.1f,
      -13.4f,
  });
  s21::stack<float> st2(std::move(st1));
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st2.top(), st0.top());
    st2.pop();
    st0.pop();
  }
}

TEST(Constructor, MoveTest4) {
  s21::stack<int> st1;
  s21::stack<int> st2(std::move(st1));

  st2.push(60);
  ASSERT_EQ(st2.top(), 60);
}

TEST(Constructor, CopyTest1) {
  s21::stack<int> st0({90, 7, 49, 82});
  s21::stack<int> st1({90, 7, 49, 82});
  s21::stack<int> st2(st1);
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st2.top(), st0.top());
    st2.pop();
    st0.pop();
  }
}

TEST(Constructor, CopyTest2) {
  s21::stack<char> st0({'g', 'q', 'H', '6'});
  s21::stack<char> st1({'g', 'q', 'H', '6'});
  s21::stack<char> st2(st1);
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st2.top(), st0.top());
    st2.pop();
    st0.pop();
  }
}

TEST(Constructor, CopyTest3) {
  s21::stack<float> st0({
      1.7f,
      9.5f,
      55.1f,
      -13.4f,
  });
  s21::stack<float> st1({
      1.7f,
      9.5f,
      55.1f,
      -13.4f,
  });
  s21::stack<float> st2(st1);
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st2.top(), st0.top());
    st2.pop();
    st0.pop();
  }
}

TEST(Constructor, CopyTest4) {
  s21::stack<int> st1({67});
  s21::stack<int> st2(st1);
  st1.push(109);
  ASSERT_TRUE(st2.top() < st1.top());
}

TEST(Method, PushPopEmptyTest) {
  s21::stack<int> st1;
  st1.push(4);
  ASSERT_EQ(st1.top(), 4);
  ASSERT_EQ(st1.empty(), 0);
  st1.pop();
  ASSERT_EQ(st1.empty(), 1);
}

TEST(Method, PushSizeTest) {
  s21::stack<char> st1;
  st1.push('k');
  ASSERT_EQ(st1.top(), 'k');
  st1.push('a');
  ASSERT_EQ(st1.top(), 'a');
  st1.push('s');
  ASSERT_EQ(st1.top(), 's');
  ASSERT_EQ(st1.size(), 3);
}

TEST(Method, SwapTest) {
  s21::stack<int> st1({8, 14, 663, 87});
  s21::stack<int> st2({412, 70, 22, 31});
  s21::stack<int> st3(st1);
  s21::stack<int> st4(st2);
  st1.swap(st2);
  for (int i = 4; i > 0; i--) {
    ASSERT_EQ(st1.top(), st4.top());
    ASSERT_EQ(st2.top(), st3.top());
    st1.pop();
    st2.pop();
    st3.pop();
    st4.pop();
  }
}