// part 1
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>

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

    int ROWS = size;
    int COLS = arr[0].length();

    char map[ROWS][COLS];
    std::set<int> x_set;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (arr[i][j] == 'S')
            {
                x_set.insert(j);
            }
            map[i][j] = arr[i][j];
        }
    }

    int total = 0;

    for (int i = 0; i < ROWS; i++)
    {
        std::set<int> new_x_set;

        for (int x : x_set)
        {
            if (map[i][x] != '^')
            {
                new_x_set.insert(x);
            }
            else
            {
                new_x_set.insert(x - 1);
                new_x_set.insert(x + 1);
                total++;
            }
        }

        x_set = new_x_set;
    }

    std::cout << total;
}