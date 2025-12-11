// part1
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

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

    std::vector<std::vector<int>> numbers;
    int numbers_idx = 0;
    std::vector<char> operators;
    for (int i = 0; i < size; i++)
    {
        std::string tmp = "";
        numbers_idx = 0;

        for (int j = 0; j < arr[i].length(); j++)
        {

            if (i == size - 1)
            {
                if (arr[i][j] == '*' || arr[i][j] == '+')
                {
                    operators.push_back(arr[i][j]);
                }
            }
            else
            {
                if (arr[i][j] == ' ')
                {

                    tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
                    if (tmp.empty())
                        continue;

                    if (i >= numbers.size())
                        numbers.resize(i + 1);

                    numbers[i].insert(numbers[i].begin() + numbers_idx, std::stoi(tmp));
                    numbers_idx++;
                    tmp = "";
                }
                else
                {
                    tmp += arr[i][j];
                }
            }
        }

        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
        if (!tmp.empty())
        {
            if (i >= numbers.size())
                numbers.resize(i + 1);

            numbers[i].push_back(std::stoi(tmp));
        }
    }

    int ROWS = numbers.size();
    int COLS = numbers[0].size();

    // transposed matrix
    std::vector<std::vector<int>> transposed(COLS, std::vector<int>(ROWS));

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            transposed[j][i] = numbers[i][j];
        }
    }

    long long int totals = 0;

    for (int i = 0; i < COLS; i++)
    {
        long long int s = 0;
        long long int p = 1;
        for (int j = 0; j < ROWS; j++)
        {
            if (operators[i] == '+')
            {
                s += transposed[i][j];
            }
            else if (operators[i] == '*')
            {
                p *= transposed[i][j];
            }
        }

        operators[i] == '+' ? totals += s : totals += p;
    }

    std::cout << totals;

    file.close();
}