
#include <snake3d/configparser.h>
#include <snake3d/fruits.h>
#include <snake3d/game.h>
#include <snake3d/i2c.h>
#include <snake3d/ledcube.h>
#include <snake3d/nunchuck.h>
#include <snake3d/snake.h>
#include <snake3d/ticker.h>

#include <cstdio>


namespace snake3d
{

   

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
