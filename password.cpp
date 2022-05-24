#include "password.hpp"

int main()
{
    PasswordGenerator generator;

    for (std::size_t i = 0; i < 100; ++i)
    {
        generator.gen_password();
        generator.write_password("passwordlog.txt");
    }

    return 0;
}