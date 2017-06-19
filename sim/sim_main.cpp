#include "snake3d/fruits.h"
#include "snake3d/snake.h"
#include "snake3d/vector.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#include <sstream>



int main(int argc, char* argv[]){


    std::cout << "started!";
    printf("starting...");

    Fruits fruits;
    Snake snake(&fruits,3,8);

    Direction dir = {1,0,0};

    int sockfd, newsockfd, portno = 10001;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        printf("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        printf("ERROR on binding");

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        printf("ERROR on accept");



    n = 1;

    while(n > 0){

        char dir_c;

        std::cin >> dir_c;
        switch (dir_c){
        case 'i': // y+
            dir = {0,1,0};
            break;
        case 'j': // x-
            dir = {-1,0,0};
            break;
        case 'k': // y-
            dir = {0,-1,0};
            break;
        case 'l': // x+
            dir = {1,0,0};
            break;
        case 'u': // z+
            dir = {0,0,1};
            break;
        case 'o': // z-
            dir = {0,0,-1};
            break;
        }

        snake.step(dir);
        std::stringstream ss;
        ss << "[";

        // fill
        bool start = true;
        for (const Led& led : *(snake.snake())){
            if (!start){
                ss << ",";
            }
            ss << "[" << float(led.x()) << "," << float(led.y()) << "," << float(led.z()) << "]";
            start = false;
        }

        // finalize
        ss << "]\n";
        std::string data = ss.str();

        printf("Snake is moving %s ", data.c_str());
        std::cout.flush();

        n = write(newsockfd,data.c_str(),data.length());

        sleep(1);
    }


    close(newsockfd);
    close(sockfd);

    return 0;
}
