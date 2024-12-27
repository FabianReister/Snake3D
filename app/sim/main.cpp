#include "snake3d/fruits.h"
#include "snake3d/snake.h"
#include "snake3d/vector.h"

#include <iostream>

#include <netinet/in.h>
#include <ostream>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <sstream>

int main(int argc, char *argv[]) {

  std::cout << "started!" << std::endl;
  printf("starting...");

  snake3d::Fruits fruits;
  snake3d::Snake snake(std::experimental::make_observer(&fruits), 3, 8);

  snake3d::Direction dir = {1, 0, 0};

  int sockfd;
  int newsockfd;
  int portno = 10001;

  socklen_t clilen;

  sockaddr_in serv_addr;
  sockaddr_in cli_addr;

  int n;

  std::cout << "Opening socket ... " << std::endl;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("ERROR opening socket");
  }
  bzero(reinterpret_cast<char *>(&serv_addr), sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  std::cout << "Binding to port " << portno << std::endl;
  if (bind(sockfd, reinterpret_cast<sockaddr *>(&serv_addr),
           sizeof(serv_addr)) < 0) {
    printf("ERROR on binding");
  }

  std::cout << "Listening ..." << std::endl;

  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, reinterpret_cast<sockaddr *>(&cli_addr), &clilen);
  if (newsockfd < 0) {
    printf("ERROR on accept");
  }

  std::cout << "You can now press any key." << std::endl;

  n = 1;

  while (n > 0) {

    char dir_c;

    std::cin >> dir_c;
    switch (dir_c) {
    case 'i': // y+
      dir = {0, 1, 0};
      break;
    case 'j': // x-
      dir = {-1, 0, 0};
      break;
    case 'k': // y-
      dir = {0, -1, 0};
      break;
    case 'l': // x+
      dir = {1, 0, 0};
      break;
    case 'u': // z+
      dir = {0, 0, 1};
      break;
    case 'o': // z-
      dir = {0, 0, -1};
      break;
    }

    snake.step(dir);
    std::stringstream ss;
    ss << "[";

    // fill
    bool start = true;
    for (const snake3d::Led &led : *(snake.snake())) {
      if (!start) {
        ss << ",";
      }
      ss << "[" << static_cast<float>(led.x()) << ","
         << static_cast<float>(led.y()) << "," << static_cast<float>(led.z())
         << "]";
      start = false;
    }

    // finalize
    ss << "]\n";
    std::string data = ss.str();

    printf("Snake is moving %s ", data.c_str());
    std::cout.flush();

    n = write(newsockfd, data.c_str(), data.length());

    sleep(1);
  }

  close(newsockfd);
  close(sockfd);

  return 0;
}
