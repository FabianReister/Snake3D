#include "game.h"
#include "snake3d/configparser.h"
#include "snake3d/ledcube.h"
#include "snake3d/nunchuck.h"
#include "snake3d/snake.h"
#include "snake3d/ticker.h"

#include <iostream>


namespace snake3d
{

    bool
    Game::slow_loop()
    {
        mutex_game_status.lock();
        GameStatus status = game_status;
        mutex_game_status.unlock();

        if (status == GameStatus::RUNNING)
        {
            std::cout << "running idle loop " << std::endl;

            // get new data from nunchuck (threadsafe)
            mutex_i2c.lock();
            _nunchuck->update();
            mutex_i2c.unlock();

            // calculate snake movement direction from nunchuck data
            const nunchuck::Data* data = _nunchuck->data();
            nunchuck::Direction xJoystickDirection =
                _nunchuck->getJoystickDirection(data->joystick.x);
            nunchuck::Direction yJoystickDirection =
                _nunchuck->getJoystickDirection(data->joystick.y);

            Direction dir = {0, 0, 0};
            if (data->c_button == nunchuck::ButtonState::PRESSED)
            { // z minux
                dir.z = -1;
            }
            else if (data->z_button == nunchuck::ButtonState::PRESSED)
            {
                dir.z = 1;
            }
            else if (xJoystickDirection != nunchuck::Direction::NONE)
            {
                dir.x = static_cast<std::int8_t>(xJoystickDirection);
            }
            else if (yJoystickDirection != nunchuck::Direction::NONE)
            {
                dir.y = static_cast<std::int8_t>(yJoystickDirection);
            }

            printf("Direction x=%i, y=%i, z=%i \n", dir.x, dir.y, dir.z);

            // now update snake
            mutex_snake.lock();

            if (not snake->step(dir))
            {
                mutex_game_status.lock();
                //         game_status = FINISHED;
                mutex_game_status.unlock();
            }

            mutex_led_cube.lock();

            // "redraw" led cube
            ledCube->updateLedStates();

            mutex_led_cube.unlock();
            mutex_snake.unlock();

            return true;
        }

        return false;
    }

    void
    Game::fast_loop()
    {
        while (true)
        {
            mutex_game_status.lock();
            GameStatus status = game_status;
            mutex_game_status.unlock();

            if (status == GameStatus::RUNNING)
            {
                std::cout << "running fast loop " << std::endl;
                mutex_i2c.lock();
                mutex_led_cube.lock();

                ledCube->spinOnce();

                mutex_led_cube.unlock();
                mutex_i2c.unlock();
            }
            else
            {
                return;
            }
        }
    }

    bool
    Game::init(const config::ConfigParser& parser)
    {

        i2c = std::make_unique<I2C>(parser.section("i2c").field("device").as<const char*>());
        _nunchuck =
            std::make_unique<nunchuck::Nunchuck>(std::experimental::make_observer(i2c.get()));
        fruits = Fruits(); // reset
        snake = std::make_unique<Snake>(std::experimental::make_observer(&fruits),
                                        3,
                                        parser.section("general").field("cube-size").as<int>());
        ledCube = std::make_unique<LedCube>(
            std::experimental::make_observer(i2c.get()),
            std::experimental::make_observer(snake.get()),
            std::experimental::make_observer(&fruits),
            parser.section("io-expander").field("channel_count").as<int>(),
            parser.section("general").field("cube-size").as<int>());

        // init game structure
        fruits.snake(std::experimental::make_observer(snake.get()));

        // init bus devices
        if (not i2c->init())
        {
            printf("Could not init I2C bus");
            return false;
        }
        // nunchuck.isConnected();
        _nunchuck->init(parser.section("nunchuck").field("variant").as<nunchuck::Variant>());

        // build up
        ledCube->updateLedStates();

        //
        slow_ticker =
            std::make_unique<Ticker>(parser.section("timings").field("frequency").as<float>());
        slow_ticker->attach([this]() { return this->slow_loop(); });

        game_status = GameStatus::STARTED;

        return true;
    }

    void
    Game::run()
    {
        slow_ticker->run();

        //    std::thread fast_thread(fast_loop);

        // slow and fast ticker will run as long game is running, wait for threads
        // to stop
        //    fast_thread.join();

        slow_ticker->thread()->join();
    }

    void
    Game::printResult()
    {
        printf("Snake length: %i \n", static_cast<int>(snake->length()));
    }
} // namespace snake3d
