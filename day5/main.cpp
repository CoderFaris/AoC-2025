// part1 and part2
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

    bool isSpace = false;
    std::vector<std::pair<long long int, long long int>> ranges;
    std::vector<long long int> ingredientIds;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == "")
            isSpace = true;

        if (!isSpace)
        {

            for (int j = 0; j < arr[i].length(); j++)
            {
                if (arr[i][j] == '-')
                {
                    std::string r1 = arr[i].substr(0, j);
                    std::string r2 = arr[i].substr(j + 1);

                    long long int n1 = std::stoll(r1);
                    long long int n2 = std::stoll(r2);

                    ranges.push_back({n1, n2});
                }
            }
        }

        if (isSpace && arr[i] != "")
        {
            ingredientIds.push_back(std::stoll(arr[i]));
        }
    }

    std::sort(ranges.begin(), ranges.end());

    long long int cnt = 0;

    long long tmp = ranges[0].first;
    long long currEnd = ranges[0].second;

    for (int i = 1; i < ranges.size(); i++)
    {

        if (ranges[i].first <= currEnd + 1)
        {
            currEnd = std::max(currEnd, ranges[i].second);
        }
        else
        {

            cnt += currEnd - tmp + 1;

            tmp = ranges[i].first;
            currEnd = ranges[i].second;
        }
    }

    cnt += currEnd - tmp + 1;

    std::cout << cnt;
}