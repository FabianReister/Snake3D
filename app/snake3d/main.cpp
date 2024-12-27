
#include <snake3d/configparser.h>
#include <snake3d/fruits.h>
#include <snake3d/game.h>
#include <snake3d/i2c.h>
#include <snake3d/ledcube.h>
#include <snake3d/nunchuck.h>
#include <snake3d/snake.h>
#include <snake3d/ticker.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

namespace snake3d
{

    class Game
    {
    public:
        //------------------------------------------------------------------------------------

        //!
        //! \brief idle_loop updates what you can see (snake movement, ...)
        //!
        bool
        slow_loop()
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

                if (!snake->step(dir))
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

        //------------------------------------------------------------------------------------
        //!
        //! \brief fast_loop is used for persistance of vision ,
        //!
        void
        fast_loop()
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
        init(const config::ConfigParser& parser)
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
        printResult()
        {
            printf("Snake length: %i \n", static_cast<int>(snake->length()));
        }

        void
        run()
        {
            slow_ticker->run();

            //    std::thread fast_thread(fast_loop);

            // slow and fast ticker will run as long game is running, wait for threads
            // to stop
            //    fast_thread.join();

            slow_ticker->thread()->join();
        }

    private:
        std::mutex mutex_i2c;
        std::mutex mutex_game_status;
        std::mutex mutex_snake;
        std::mutex mutex_led_cube;

        GameStatus game_status = GameStatus::INIT;

        std::unique_ptr<I2C> i2c;
        Fruits fruits;
        std::unique_ptr<Snake> snake;
        std::unique_ptr<LedCube> ledCube;
        std::unique_ptr<nunchuck::Nunchuck> _nunchuck;

        std::unique_ptr<Ticker> slow_ticker;
    };

    int
    main()
    { // int argc, char* argv[]){

        config::ConfigParser parser;

        // TODO(fabian.reister): via cli
        parser.parse("snake3d.config");

        Game game;

        if (not game.init(parser))
        {
            printf("Could not init I2C bus");
            return 1;
        }

        game.printResult();

        return 0;
    }

} // namespace snake3d

int
main()
{
    return snake3d::main();
}
