#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{

    std::ifstream file("example.txt");
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

    char map[size][size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < arr[i].length(); j++)
        {
            map[i][j] = arr[i][j];
        }
    }

    // for (int rows = 0; rows < size; rows++)
    // {
    //     for (int cols = 0; cols < size; cols++)
    //     {
    //         std::cout << map[rows][cols];
    //     }
    //     std::cout << '\n';
    // }

    int cnt = 0;

    for (int rows = 0; rows < size; rows++)
    {
        for (int cols = 0; cols < size; cols++)
        {
            int rollpapercount = 0;

            if (map[rows][cols] == '@')
            {
                // bottom
                if (rows + 1 < size && map[rows + 1][cols] == '@')
                    rollpapercount++;

                // bottom left
                if (rows + 1 < size && cols - 1 >= 0 && map[rows + 1][cols - 1] == '@')
                    rollpapercount++;

                // left
                if (cols - 1 >= 0 && map[rows][cols - 1] == '@')
                    rollpapercount++;

                // top left
                if (rows - 1 >= 0 && cols - 1 >= 0 && map[rows - 1][cols - 1] == '@')
                    rollpapercount++;

                // top
                if (rows - 1 >= 0 && map[rows - 1][cols] == '@')
                    rollpapercount++;

                // top right
                if (rows - 1 >= 0 && cols + 1 < size && map[rows - 1][cols + 1] == '@')
                    rollpapercount++;

                // right
                if (cols + 1 < size && map[rows][cols + 1] == '@')
                    rollpapercount++;

                // bottom right
                if (rows + 1 < size && cols + 1 < size && map[rows + 1][cols + 1] == '@')
                    rollpapercount++;

                if (rollpapercount < 4)
                {
                    cnt++;
                }
            }
        }
    }

    std::cout << cnt;

    file.close();
}