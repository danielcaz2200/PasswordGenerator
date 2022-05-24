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
    // default constructor
    PasswordGenerator(void);

    // parameterized constructor with argument of password length
    PasswordGenerator(int length);

    // retrieve password as std::string
    std::string get_password(void);

    // write password to <filename> or default file of password.txt
    void write_password(const std::string &filename = "");

    // generate random password
    void gen_password(void);

    // change password length, for use before generation
    void change_length(int length);

private:
    std::array<char, 62> _alphanumeric;
    std::string _password;
    std::size_t _length;
    int _rNum;
};

PasswordGenerator::PasswordGenerator(void) : PasswordGenerator(8)
{
    // default constructor, initializes length to 8
}

PasswordGenerator::PasswordGenerator(int length) : _length(static_cast<std::size_t>(length))
{
    // paramaterized constructor which takes password length from user

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
    // writes password to output file or defaults to password.txt if none given

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
    // returns password

    return _password;
}

void PasswordGenerator::gen_password(void)
{
    // generates new password per function call

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
    // modifies length of password string for later generation

    _length = static_cast<std::size_t>(length);

    return;
}
