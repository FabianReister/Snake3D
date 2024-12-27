#include <snake3d/fruits.h>
#include <snake3d/snake.h>

#include <gtest/gtest.h>

namespace snake3d
{

    constexpr std::size_t CUBE_SIZE = 8;

    TEST(FruitsTest, PositiveNos)
    {
        Fruits fruits;
        Snake snake(std::experimental::make_observer(&fruits), 3, CUBE_SIZE);
        fruits.snake(std::experimental::make_observer(&snake));
        // no fruit should be created
        ASSERT_EQ(0, fruits.fruits().size());
        fruits.generateFruit();
        // there should be one fruit
        ASSERT_EQ(1, fruits.fruits().size());
        // get the fruit
        const Led* led = &fruits.fruits().front();
        // create a led that is different and compare
        Led otherLed = *led;
        Direction dir = {1, 1, 1};
        otherLed += dir;
        ASSERT_EQ(fruits.isFruit(*led), true);
        ASSERT_EQ(fruits.isFruit(otherLed), false);
        // now remove led and check
        fruits.remove(*led);
        ASSERT_EQ(fruits.fruits().size(), 0);
    }

    TEST(SnakeTest, PositiveNos)
    {
        Fruits fruits;
        Snake snake(std::experimental::make_observer(&fruits), 3, CUBE_SIZE);
        Snake snake2(std::experimental::make_observer(&fruits), 5, CUBE_SIZE);
        // check constructor
        ASSERT_EQ(snake.snake()->size(), 3);
        ASSERT_EQ(snake2.snake()->size(), 5);
        // check step
        Led head = *(snake.snake()->begin());
        Direction dir = {1, 0, 0};
        snake.step(dir);
        printf("%f, %f, %f",
               static_cast<float>(head.x()),
               static_cast<float>(head.y()),
               static_cast<float>(head.z()));
        ASSERT_EQ(*(snake.snake()->begin()), head + dir);
        // finally check length
        ASSERT_EQ(snake.snake()->size(), snake.length());
    }

} // namespace snake3d

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
