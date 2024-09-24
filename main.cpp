#include <iostream>

constexpr int EXPECTED_ARGUMENTS = 2;


int main(const int argc, char** argv)
{
    if (EXPECTED_ARGUMENTS != argc) {
        std::cout << "Usage: " << argv[0] << " [port]" << std::endl;
        return 1;
    }
    const int server_port = std::stoi(argv[1]);
    std::cout << "Port: " << server_port << std::endl;
    return 0;
}
