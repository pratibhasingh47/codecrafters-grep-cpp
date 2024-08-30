#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
bool match_digits(const std::string &inputs, const std::string &pattern)
{
    for (auto input : inputs)
    {
        if (isdigit(input))
        {
            return true;
        }
    }
    return false;
}
bool match_alphanum(const std::string &inputs, const std::string &pattern)
{
    for (auto c : inputs)
    {
        if (isalnum(c))
        {
            return true;
        }
    }
    return false;
}
bool match_group(const string &input_line, const string &pattern)
{
    return input_line.find_first_of(pattern) != string::npos;
    // returns the position of the first occurrence of any character that is present in the argument string
}
bool match_pattern(const std::string &input_line, const std::string &pattern)
{

    if (pattern.size() == 0)
        return 1;
    if (input_line.size() == 0)
        return 0;

    // if (pattern.length() == 1) {
    //     return input_line.find(pattern) != std::string::npos;
    // }
    if (pattern.substr(0, 2) == "\\d")
    {
        if (isdigit(input_line[0]))
        {
            return match_pattern(input_line.substr(1), pattern.substr(2));
        }
        return match_pattern(input_line.substr(1), pattern);
    }
    else if (pattern.substr(0, 2) == "\\w")
    {
        if (isalnum(input_line[0]))
        {
            return match_pattern(input_line.substr(1), pattern.substr(2));
        }
        return match_pattern(input_line.substr(1), pattern);
    }
    else if (pattern[0] == '[')
    {
        auto first = pattern.find(']');
        bool neg = pattern[1] == '^';
        if (neg)
        {
            if (!match_group(input_line, pattern.substr(2, first - 1)))
            {
                return match_pattern(input_line.substr(1), pattern.substr(first + 1));
            }
            return 0;
        }
        if (match_group(input_line, pattern.substr(1, first - 1)))
        {
            return match_pattern(input_line.substr(1), pattern.substr(first + 1));
        }
        else
            return 0;
    }
    if (pattern[0] == input_line[0])
    {
        // throw std::runtime_error("Unhandled pattern " + pattern);
        return match_pattern(input_line.substr(1), pattern.substr(1));
    }
    return match_pattern(input_line.substr(1), pattern);
}
bool match_patterns(string input_line, string pattern)
{
    int idx = 0;
    do
    {
        if (match_pattern(input_line, pattern))
        {
            return 1;
        }
        input_line = input_line.substr(1); // move 1 step further
    } while (input_line != "");
    return 0;
}
int main(int argc, char *argv[])
{
    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here" << std::endl;
    if (argc != 3)
    {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }
    std::string flag = argv[1];
    std::string pattern = argv[2];
    if (flag != "-E")
    {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }
    // Uncomment this block to pass the first stage

    std::string input_line;
    std::getline(std::cin, input_line);

    try
    {
        if (match_patterns(input_line, pattern))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}