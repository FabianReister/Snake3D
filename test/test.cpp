// tests.cpp
//#include "whattotest.cpp"
#include "gtest/gtest.h"
#include "../src/fruits.h"

TEST(FruitsTest, PositiveNos) {
    Fruits fruits;
    Snake snake(&fruits);
    fruits.snake(&snake);
    // no fruit should be created
    ASSERT_EQ(0, fruits.fruits()->size());
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
    Snake snake2(&fruits,5);
    // check constructor
    ASSERT_EQ(snake.snake()->size(),3);
    ASSERT_EQ(snake2.snake()->size(),5);
    // check step
    Led head = *(snake.snake()->begin());
    Direction dir = {1,0,0};
    snake.step(dir);
    ASSERT_EQ( *(snake.snake()->begin()), head+dir);
    //finally check length
    ASSERT_EQ(snake.snake()->size(), snake.length());

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
