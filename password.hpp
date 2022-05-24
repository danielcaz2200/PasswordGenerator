#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <exception>

class PasswordGenerator
{
public:
    PasswordGenerator(void);
    PasswordGenerator(int length);

    // accessors and modifiers
    std::string get_password(void);

    void write_password(const std::string &filename = "");

    void gen_password(void);

    void change_length(int length);

private:
    std::array<char, 62> _alphanumeric;
    std::string _password;
    std::size_t _length;
    int _rNum;
};

PasswordGenerator::PasswordGenerator(void) : PasswordGenerator(8) {}

PasswordGenerator::PasswordGenerator(int length) : _length(static_cast<std::size_t>(length))
{
    // seed random number generator
    std::srand(std::time(0));

    std::string alpha_str = "abcdefghijklmnopqrstuvwxyz";
    std::string num_str = "0123456789";

    // initialize array
    std::size_t count = 0;

    for (auto a : alpha_str)
    {
        _alphanumeric[count] = a;
        ++count;
    }
    for (auto A : alpha_str)
    {
        _alphanumeric[count] = std::toupper(A);
        ++count;
    }
    for (auto num : num_str)
    {
        _alphanumeric[count] = num;
        ++count;
    }
}

void PasswordGenerator::write_password(const std::string &filename)
{
    if (_password.empty())
        throw(std::logic_error("Password has not been generated yet.\n"));

    // create output file
    std::ofstream output;

    // open file based on given input or not
    // write to requested output file
    if (filename.empty())
        output.open("password.txt", std::ios::app);
    else
        output.open(filename, std::ios::app);

    // check if file was opened, if not exit immediately
    if (output.is_open())
    {
        output << _password << "\n";
        output.close();
    }
    else
        throw(std::runtime_error("File not opened.\n"));

    return;
}

std::string PasswordGenerator::get_password(void)
{
    return _password;
}

void PasswordGenerator::gen_password(void)
{
    _password = "";
    for (std::size_t i = 0; i < _length; ++i)
    {
        _rNum = std::rand() % 62;
        _password += _alphanumeric[_rNum];
    }

    return;
}

void PasswordGenerator::change_length(int length)
{
    _length = static_cast<std::size_t>(length);

    return;
}
