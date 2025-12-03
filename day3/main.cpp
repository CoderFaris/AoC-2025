// part1
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{

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

    int idx = 0;
    std::string arr[size];
    std::istringstream iss(file_contents);
    std::string token;

    while (std::getline(iss, token, '\n'))
    {
        arr[idx++] = token;
    }

    long long int s = 0;

    for (int i = 0; i < size; i++)
    {
        long long maxJoltage = 0;
        int num[arr[i].length()];
        for (int j = 0; j < arr[i].length(); j++)
        {
            for (int k = j + 1; k < arr[i].length(); k++)
            {
                long long joltage = (arr[i][j] - '0') * 10 + (arr[i][k] - '0');
                maxJoltage = std::max(maxJoltage, joltage);
            }
        }
        s += maxJoltage;
    }

    file.close();

    std::cout << s;
}