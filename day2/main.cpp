#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
int main()
{
    std::ifstream file("input.txt");
    std::string str;
    std::string file_contents;

    while (std::getline(file, str))
    {
        file_contents += str;
    }

    std::istringstream iss(file_contents);
    std::string token;

    int idx = 0;
    std::vector<std::string> arr;
    while (std::getline(iss, token, ','))
    {
        arr.push_back(token);
    }

    long long int s = 0;
    std::regex pattern("^(\\d+)\\1+$");

    for (int i = 0; i < arr.size(); i++)
    {
        // find dash
        for (int j = 0; j < arr[i].length(); j++)
        {
            if (arr[i][j] == '-')
            {
                std::string r1 = arr[i].substr(0, j);
                std::string r2 = arr[i].substr(j + 1);

                long long int n1 = std::stoll(r1);
                long long int n2 = std::stoll(r2);

                for (long long int k = n1; k <= n2; k++)
                {
                    std::string num = std::to_string(k);

                    // std::string firstHalf = num.substr(0, num.length() / 2);
                    // std::string secondHalf = num.substr(num.length() / 2);
                    // if (firstHalf == secondHalf)
                    // {
                    //     s += stoll(num);
                    // }

                    if (std::regex_match(num, pattern))
                    {
                        s += stoll(num);
                    }
                }
            }
        }
    }

    std::cout << s;
}