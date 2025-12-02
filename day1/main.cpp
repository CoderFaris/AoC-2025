// part1
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

int main()
{
    int dialStart = 50;
    int zeroCount = 0;

    std::ifstream file("input.txt");
    std::string str;
    std::string file_contents;

    long long int size = 0;
    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
        size++;
    }

    std::string arr[size];
    std::istringstream iss(file_contents);
    std::string token;

    int idx = 0;

    while (std::getline(iss, token, '\n'))
    {
        arr[idx++] = token;
    }

    for (int i = 0; i < size; i++)
    {
        char rotation = arr[i][0];
        int len = arr[i].length();
        int number;
        // check whether it's 1, 2 or 3 digits
        // rotation + digits (e.g. 3 digits is 1 + 3 = 4)
        if (len == 4)
        {
            number = (arr[i][1] - '0') * 100 + (arr[i][2] - '0') * 10 + (arr[i][3] - '0');
        }
        else if (len == 3)
        {
            number = (arr[i][1] - '0') * 10 + (arr[i][2] - '0');
        }
        else if (len == 2)
        {
            number = arr[i][1] - '0';
        }

        if (rotation == 'L')
        {

            dialStart = (dialStart - number) % 100;
        }
        else
        {

            dialStart = (dialStart + number) % 100;
        }

        if (dialStart == 0)
        {
            zeroCount++;
        }
    }
    std::cout << zeroCount;
    return 0;
}