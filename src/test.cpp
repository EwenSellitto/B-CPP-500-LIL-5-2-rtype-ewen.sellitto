#include <iostream>
#include <memory>
#include <ostream>

struct Position {
        float x;
        float y;
};

struct Hello : public Position {
};

int main(void)
{
    std::cout << typeid(Position).hash_code() << std::endl;
    std::cout << typeid(Hello).hash_code() << std::endl;
}
