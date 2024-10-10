
#include <string>

#include "test_header.h"

TEST(MapTest, Insert) {
  s21::map<int, std::string> my_map;
  my_map.insert(3, "333");
  my_map.insert(1, "111");
  my_map.insert(std::pair<int, std::string>(2, "222"));
  my_map.insert(std::pair<int, std::string>(5, "555"));
  my_map.insert(std::pair<int, std::string>(4, "444"));

  std::map<int, std::string> original_map;
  original_map.insert(std::pair<int, std::string>(3, "333"));
  original_map.insert(std::pair<int, std::string>(1, "111"));
  original_map.insert(std::pair<int, std::string>(2, "222"));
  original_map.insert(std::pair<int, std::string>(5, "555"));
  original_map.insert(std::pair<int, std::string>(4, "444"));

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(my_it.second(), original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, std::string> my_map;
  my_map.insert(std::pair<int, std::string>(3, "333"));
  my_map.insert(std::pair<int, std::string>(1, "111"));
  my_map.insert(std::pair<int, std::string>(2, "222"));
  my_map.insert(std::pair<int, std::string>(5, "555"));
  my_map.insert(std::pair<int, std::string>(4, "444"));

  std::map<int, std::string> original_map;
  original_map.insert(std::pair<int, std::string>(3, "333"));
  original_map.insert(std::pair<int, std::string>(1, "111"));
  original_map.insert(std::pair<int, std::string>(2, "222"));
  original_map.insert(std::pair<int, std::string>(5, "555"));
  original_map.insert(std::pair<int, std::string>(4, "444"));

  auto my_pair = my_map.insert_or_assign(10, "101010");
  auto original_pair = original_map.insert_or_assign(10, "101010");
  EXPECT_EQ(my_pair.second, original_pair.second);

  my_pair = my_map.insert_or_assign(4, "!!!");
  original_pair = original_map.insert_or_assign(4, "!!!");
  EXPECT_EQ(my_pair.second, original_pair.second);

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  for (int i = 0; i < 6; i++) {
    EXPECT_EQ(my_it.second(), original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, ListConstructor) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map({p3, p1, p2, p5, p4});

  std::map<int, std::string> original_map({p3, p1, p2, p5, p4});

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(*my_it, original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, AccessingMissingItem) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map({p3, p1, p2, p5, p4});

  bool my_error = false;

  auto my_it = my_map.begin();

  --my_it;

  try {
    std::string str = *my_it;
  } catch (const std::exception& e) {
    my_error = true;
  }

  EXPECT_TRUE(my_error);
}

TEST(MapTest, End) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map({p3, p1, p2, p5, p4});
  std::map<int, std::string> original_map({p3, p1, p2, p5, p4});

  bool my_error = false;
  bool original_error = false;

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  --my_it;
  --original_it;

  if (my_it != my_map.end()) {
    my_error = true;
  }

  if (original_it != original_map.end()) {
    original_error = true;
  }

  EXPECT_EQ(my_error, original_error);
}

TEST(MapTest, Copying) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map_A({p3, p1, p2, p5, p4});
  std::map<int, std::string> original_map_A({p3, p1, p2, p5, p4});

  s21::map<int, std::string> my_map_B(my_map_A);
  std::map<int, std::string> original_map_B(original_map_A);

  EXPECT_EQ(my_map_A.empty(), original_map_A.empty());

  auto my_it = my_map_B.begin();
  auto original_it = original_map_B.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(my_it.second(), original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, Move) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map_A({p3, p1, p2, p5, p4});
  std::map<int, std::string> original_map_A({p3, p1, p2, p5, p4});

  s21::map<int, std::string> my_map_B(std::move(my_map_A));
  std::map<int, std::string> original_map_B(std::move(original_map_A));

  EXPECT_EQ(my_map_A.empty(), original_map_A.empty());

  auto my_it = my_map_B.begin();
  auto original_it = original_map_B.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(my_it.second(), original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, Clear) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map({p3, p1, p2, p5, p4});
  EXPECT_FALSE(my_map.empty());

  my_map.clear();
  EXPECT_TRUE(my_map.empty());
}

TEST(MapTest, Size) {
  s21::map<int, std::string> my_map;

  int i = 0;
  for (; i < 5; i++) {
    my_map.insert(i, "0");
  }

  EXPECT_EQ(i, my_map.size());
}

TEST(MapTest, EraseNoChildren) {
  std::pair<int, std::string> p3(3, "333");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p4(4, "444");

  s21::map<int, std::string> my_map({p3, p1, p2, p5, p4});
  std::map<int, std::string> original_map({p3, p1, p2, p5, p4});

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  ++my_it;
  ++original_it;

  my_map.erase(my_it);
  original_map.erase(original_it);

  my_it = my_map.begin();
  original_it = original_map.begin();

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(my_it.second(), original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, EraseOneChildren) {
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p3(3, "333");

  s21::map<int, std::string> my_map({p5, p1, p2, p3});
  std::map<int, std::string> original_map({p5, p1, p2, p3});

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  ++my_it;
  ++original_it;

  my_map.erase(my_it);
  original_map.erase(original_it);

  my_it = my_map.begin();
  original_it = original_map.begin();

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(my_it.second(), original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, EraseTwoChildrens) {
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p4(4, "444");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p3(3, "333");

  s21::map<int, std::string> my_map({p2, p1, p4, p5, p3});
  std::map<int, std::string> original_map({p2, p1, p4, p5, p3});

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  ++my_it;
  ++original_it;

  my_map.erase(my_it);
  original_map.erase(original_it);

  my_it = my_map.begin();
  original_it = original_map.begin();

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(*my_it, original_it->second);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, Swap) {
  std::pair<int, std::string> pA3(3, "333");
  std::pair<int, std::string> pA1(1, "111");
  std::pair<int, std::string> pA2(2, "222");
  std::pair<int, std::string> pA5(5, "555");
  std::pair<int, std::string> pA4(4, "444");

  s21::map<int, std::string> my_map_A({pA3, pA1, pA2, pA5, pA4});
  std::map<int, std::string> original_map_A({pA3, pA1, pA2, pA5, pA4});

  std::pair<int, std::string> pB3(3, "303030");
  std::pair<int, std::string> pB1(1, "101010");
  std::pair<int, std::string> pB2(2, "202020");
  std::pair<int, std::string> pB5(5, "505050");
  std::pair<int, std::string> pB4(4, "404040");

  s21::map<int, std::string> my_map_B({pB3, pB1, pB2, pB5, pB4});
  std::map<int, std::string> original_map_B({pB3, pB1, pB2, pB5, pB4});

  my_map_A.swap(my_map_B);
  original_map_A.swap(original_map_B);

  auto my_it_A = my_map_A.begin();
  auto my_it_B = my_map_B.begin();
  auto original_it_A = original_map_A.begin();
  auto original_it_B = original_map_B.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(*my_it_A, original_it_A->second);
    EXPECT_EQ(*my_it_B, original_it_B->second);
    EXPECT_EQ(my_it_A.first(), original_it_A->first);
    EXPECT_EQ(my_it_B.first(), original_it_B->first);

    ++my_it_A;
    ++my_it_B;
    ++original_it_A;
    ++original_it_B;
  }
}

TEST(MapTest, Merge) {
  std::pair<int, std::string> pA3(3, "333");
  std::pair<int, std::string> pA1(1, "111");
  std::pair<int, std::string> pA2(2, "222");
  std::pair<int, std::string> pA5(5, "555");
  std::pair<int, std::string> pA4(4, "444");

  s21::map<int, std::string> my_map_A({pA3, pA1, pA2, pA5, pA4});
  std::map<int, std::string> original_map_A({pA3, pA1, pA2, pA5, pA4});

  std::pair<int, std::string> pB3(-3, "303030");
  std::pair<int, std::string> pB1(10, "101010");
  std::pair<int, std::string> pB2(-2, "202020");
  std::pair<int, std::string> pB5(-50, "505050");
  std::pair<int, std::string> pB4(4, "404040");

  s21::map<int, std::string> my_map_B({pB3, pB1, pB2, pB5, pB4});
  std::map<int, std::string> original_map_B({pB3, pB1, pB2, pB5, pB4});

  my_map_A.merge(my_map_B);
  original_map_A.merge(original_map_B);

  auto my_it_A = my_map_A.begin();
  auto original_it_A = original_map_A.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(*my_it_A, original_it_A->second);
    EXPECT_EQ(my_it_A.first(), original_it_A->first);

    ++my_it_A;
    ++original_it_A;
  }
}

TEST(MapTest, At) {
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p4(4, "444");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p3(3, "333");

  s21::map<int, std::string> my_map({p2, p1, p4, p5, p3});
  std::map<int, std::string> original_map({p2, p1, p4, p5, p3});

  EXPECT_EQ(my_map.at(4), original_map.at(4));
  EXPECT_EQ(my_map.at(1), original_map.at(1));
  EXPECT_EQ(my_map.at(3), original_map.at(3));
  EXPECT_EQ(my_map[5], original_map[5]);
  EXPECT_EQ(my_map[2], original_map[2]);

  my_map[5] = "5050";
  original_map[5] = "5050";
  my_map[2] = "2020";
  original_map[2] = "2020";

  auto my_it = my_map.begin();
  auto original_it = original_map.begin();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(*my_it, original_it->second);
    EXPECT_EQ(my_it.first(), original_it->first);

    ++my_it;
    ++original_it;
  }
}

TEST(MapTest, Contains) {
  std::pair<int, std::string> p2(2, "222");
  std::pair<int, std::string> p1(1, "111");
  std::pair<int, std::string> p4(4, "444");
  std::pair<int, std::string> p5(5, "555");
  std::pair<int, std::string> p3(3, "333");

  s21::map<int, std::string> my_map({p2, p1, p4, p5, p3});

  EXPECT_FALSE(my_map.contains(-10));
  EXPECT_FALSE(my_map.contains(6));
  EXPECT_TRUE(my_map.contains(2));
  EXPECT_TRUE(my_map.contains(4));
}