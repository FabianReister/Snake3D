// tests.cpp
//#include "whattotest.cpp"
#include "gtest/gtest.h"
#include "../src/fruits.h"

TEST(FruitsTest, PositiveNos) {
    Fruits fruits;
    Snake snake(&fruits);
    fruits.snake(&snake);
    fruits.generateFruit();
    // there should be one fruit
    ASSERT_EQ(1, fruits.fruits()->size());
    // get the fruit
    const Led* led = &fruits.fruits()->at(0);
    // create a led that is different and compare
    Led otherLed = *led;
    Direction dir = {1,1,1};
    otherLed += dir;
    ASSERT_EQ(true, fruits.isFruit(led));
    ASSERT_EQ(false, fruits.isFruit(&otherLed));

    // now remove led and check
    fruits.remove(led);
    ASSERT_EQ(0, fruits.fruits()->size());
}

TEST(SnakeTest, PositiveNos) {
    Fruits fruits;
    Snake snake(&fruits);
    fruits.snake(&snake);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
