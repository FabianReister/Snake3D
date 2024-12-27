#pragma once

#include <snake3d/fruits.h>

#include <memory>
#include <mutex>

namespace snake3d
{
    class I2C;
    class Snake;
    class LedCube;
    class Ticker;

    namespace nunchuck
    {
        class Nunchuck;
    }

    namespace config
    {
        class ConfigParser;
    }

    enum class GameStatus
    {
        INIT,
        STARTED, // started but not running
        RUNNING,
        FINISHED,
        ERROR
    };

    class Game
    {
    public:
        Game();
        ~Game();

        bool init(const config::ConfigParser& parser);

        void run();

        void printResult();


    protected:
        //!
        //! \brief idle_loop updates what you can see (snake movement, ...)
        //!
        bool slow_loop();

        //!
        //! \brief fast_loop is used for persistance of vision ,
        //!
        void fast_loop();

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


} // namespace snake3d
