

#include "test_header.h"

TEST(SetTest, Insert) {
  s21::set<int> my_set;
  my_set.insert(3);
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(5);
  my_set.insert(4);

  std::set<int> original_set;
  original_set.insert(3);
  original_set.insert(1);
  original_set.insert(2);
  original_set.insert(5);
  original_set.insert(4);

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }
}

TEST(SetTest, EmptyAndSize) {
  s21::set<int> my_set;
  std::set<int> original_set;
  EXPECT_EQ(my_set.empty(), original_set.empty());

  my_set.insert(3);
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(5);
  my_set.insert(4);

  original_set.insert(3);
  original_set.insert(1);
  original_set.insert(2);
  original_set.insert(5);
  original_set.insert(4);

  EXPECT_EQ(my_set.empty(), original_set.empty());

  EXPECT_EQ(my_set.size(), original_set.size());
}

TEST(SetTest, AccessingMissingItem) {
  s21::set<std::string> my_set({"Bb", "Aa", "Cc"});
  std::set<std::string> original_set({"Bb", "Aa", "Cc"});

  bool my_error = false;
  bool original_error = false;

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  --my_it;
  --original_it;

  try {
    std::string str = *my_it;
  } catch (const std::exception& e) {
    my_error = true;
  }

  try {
    std::string str = *original_it;
  } catch (const std::exception& e) {
    original_error = true;
  }

  EXPECT_EQ(my_error, original_error);
}

TEST(SetTest, End) {
  s21::set<int> my_set({3, 1, 2, 5, 4});
  std::set<int> original_set({3, 1, 2, 5, 4});

  bool my_error = false;
  bool original_error = false;

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  --my_it;
  --original_it;

  if (my_it != my_set.end()) {
    my_error = true;
  }

  if (original_it != original_set.end()) {
    original_error = true;
  }

  EXPECT_EQ(my_error, original_error);
}

TEST(SetTest, Copying) {
  s21::set<int> my_set_A({3, 1, 2, 5, 4});
  std::set<int> original_set_A({3, 1, 2, 5, 4});

  s21::set<int> my_set_B(my_set_A);
  std::set<int> original_set_B(original_set_A);

  EXPECT_EQ(my_set_A.empty(), original_set_A.empty());

  auto my_it = my_set_B.begin();
  auto original_it = original_set_B.begin();

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }
}

TEST(SetTest, Move) {
  s21::set<int> my_set_A({3, 1, 2, 5, 4});
  std::set<int> original_set_A({3, 1, 2, 5, 4});

  s21::set<int> my_set_B(std::move(my_set_A));
  std::set<int> original_set_B(std::move(original_set_A));

  EXPECT_EQ(my_set_A.empty(), original_set_A.empty());

  auto my_it = my_set_B.begin();
  auto original_it = original_set_B.begin();

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }
}

TEST(SetTest, Clear) {
  s21::set<int> my_set({3, 1, 2, 5, 4});
  EXPECT_FALSE(my_set.empty());

  my_set.clear();
  EXPECT_TRUE(my_set.empty());
}

TEST(SetTest, Size) {
  s21::set<int> my_set;

  int i = 0;
  for (; i < 5; i++) {
    my_set.insert(i);
  }

  EXPECT_EQ(i, my_set.size());
}

TEST(SetTest, EraseNoChildren) {
  s21::set<int> my_set({3, 1, 2, 5, 4});
  std::set<int> original_set({3, 1, 2, 5, 4});

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  ++my_it;
  ++original_it;

  my_set.erase(my_it);
  original_set.erase(original_it);

  my_it = my_set.begin();
  original_it = original_set.begin();

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }
}

TEST(SetTest, EraseOneChildren) {
  s21::set<int> my_set({5, 1, 2, 3});
  std::set<int> original_set({5, 1, 2, 3});

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  ++my_it;
  ++original_it;

  my_set.erase(my_it);
  original_set.erase(original_it);

  my_it = my_set.begin();
  original_it = original_set.begin();

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }
}

TEST(SetTest, EraseTwoChildrens) {
  s21::set<int> my_set({2, 1, 4, 5, 3});
  std::set<int> original_set({2, 1, 4, 5, 3});

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  ++my_it;
  ++original_it;

  my_set.erase(my_it);
  original_set.erase(original_it);

  my_it = my_set.begin();
  original_it = original_set.begin();

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }
}

TEST(SetTest, FieldAndMinus) {
  s21::set<int> my_set({3, 1, 2, 5, 4});
  std::set<int> original_set({3, 1, 2, 5, 4});

  auto my_it = my_set.begin();
  auto original_it = original_set.begin();

  for (int i = 0; i < 4; i++) {
    printf("%d - %d\n", *my_it, *original_it);
    EXPECT_EQ(*my_it, *original_it);

    ++my_it;
    ++original_it;
  }

  for (int i = 0; i < 4; i++) {
    printf("%d - %d\n", *my_it, *original_it);
    EXPECT_EQ(*my_it, *original_it);

    --my_it;
    --original_it;
  }
}

TEST(SetTest, Swap) {
  s21::set<int> my_set_A({3, 1, 2, 5, 4});
  std::set<int> original_set_A({3, 1, 2, 5, 4});

  s21::set<int> my_set_B({30, 10, 20, 50, 40});
  std::set<int> original_set_B({30, 10, 20, 50, 40});

  my_set_A.swap(my_set_B);
  original_set_A.swap(original_set_B);

  auto my_it_A = my_set_A.begin();
  auto my_it_B = my_set_B.begin();
  auto original_it_A = original_set_A.begin();
  auto original_it_B = original_set_B.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(*my_it_A, *original_it_A);
    EXPECT_EQ(*my_it_B, *original_it_B);

    ++my_it_A;
    ++my_it_B;
    ++original_it_A;
    ++original_it_B;
  }
}

TEST(SetTest, Merge) {
  s21::set<int> my_set_A({3, 1, 2, 5, 4});
  std::set<int> original_set_A({3, 1, 2, 5, 4});

  s21::set<int> my_set_B({-30, 10, -20, 50, -40});
  std::set<int> original_set_B({-30, 10, -20, 50, -40});

  my_set_A.merge(my_set_B);
  original_set_A.merge(original_set_B);

  auto my_it_A = my_set_A.begin();
  auto original_it_A = original_set_A.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(*my_it_A, *original_it_A);

    ++my_it_A;
    ++original_it_A;
  }
}

TEST(SetTest, Find) {
  s21::set<int> my_set({3, 1, 2, 5, 4});
  std::set<int> original_set({3, 1, 2, 5, 4});

  EXPECT_EQ(*my_set.find(5), *original_set.find(5));
  EXPECT_EQ(*my_set.find(3), *original_set.find(3));
  EXPECT_EQ(*my_set.find(2), *original_set.find(2));

  bool my_end = false;
  bool original_end = false;

  if (my_set.find(10) == my_set.end()) {
    my_end = true;
  }

  if (original_set.find(10) == original_set.end()) {
    original_end = true;
  }

  EXPECT_EQ(my_end, original_end);
}

TEST(SetTest, Contains) {
  s21::set<int> my_set({3, 1, 2, 5, 4});

  EXPECT_TRUE(my_set.contains(5));
  EXPECT_TRUE(my_set.contains(3));
  EXPECT_TRUE(my_set.contains(2));

  EXPECT_FALSE(my_set.contains(50));
  EXPECT_FALSE(my_set.contains(-50));
  EXPECT_FALSE(my_set.contains(132));
}
