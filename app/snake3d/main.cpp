
#include <snake3d/configparser.h>
#include <snake3d/game.h>

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

        game.run();

        game.printResult();

        return 0;
    }

} // namespace snake3d

int
main()
{
    return snake3d::main();
}
