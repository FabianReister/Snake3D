// tests.cpp
//#include "whattotest.cpp"
#include "gtest/gtest.h"
#include "snake3d/fruits.h"

TEST(FruitsTest, PositiveNos) {
    Fruits fruits;
    Snake snake(&fruits,3,8);
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
    ASSERT_EQ(fruits.isFruit(led), true);
    ASSERT_EQ(fruits.isFruit(&otherLed), false);
    // now remove led and check
    fruits.remove(led);
    ASSERT_EQ(fruits.fruits()->size(),0);
}

TEST(SnakeTest, PositiveNos) {
    Fruits fruits;
    Snake snake(&fruits,3,8);
    Snake snake2(&fruits,5,8);
    // check constructor
    ASSERT_EQ(snake.snake()->size(),3);
    ASSERT_EQ(snake2.snake()->size(),5);
    // check step
    Led head = *(snake.snake()->begin());
    Direction dir = {1,0,0};
    snake.step(dir);
    printf("%f, %f, %f", float(head.x()), float(head.y()),float(head.z()));
    ASSERT_EQ( *(snake.snake()->begin()), head+dir);
    //finally check length
    ASSERT_EQ(snake.snake()->size(), snake.length());

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
