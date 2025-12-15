// part1
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>
#include <map>
#include <tuple>

struct DSU
{
    std::map<std::tuple<int, int, int>, std::tuple<int, int, int>> parent;

    std::tuple<int, int, int> find(const std::tuple<int, int, int> &x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    void unite(const std::tuple<int, int, int> &a,
               const std::tuple<int, int, int> &b)
    {
        auto pa = find(a);
        auto pb = find(b);
        if (pa != pb)
            parent[pb] = pa;
    }
};

double straightLineDistance(int x1, int y1, int z1, int x2, int y2, int z2)
{
    double tmp = std::pow((double)x1 - x2, 2.0) + std::pow((double)y1 - y2, 2.0) + std::pow((double)z1 - z2, 2.0);
    return sqrt(tmp);
}

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
    int COLS = 3;
    std::vector<std::vector<int>> positions(ROWS);

    int col_idx = 0;
    for (int i = 0; i < size; i++)
    {
        std::istringstream tokenStream(arr[i]);
        std::string token;
        while (std::getline(tokenStream, token, ','))
        {
            positions[i].push_back(std::stoi(token));
        }
    }

    // create a pair consisting of value and 2 positions that make the value, sort it based on straight line distance (first one) and go one by one from there
    std::vector<std::pair<double, std::pair<std::tuple<int, int, int>, std::tuple<int, int, int>>>> values;

    for (int i = 0; i < ROWS; i++)
    {

        int x = positions[i][0];
        int y = positions[i][1];
        int z = positions[i][2];

        // go through all positions except itself
        for (int j = i + 1; j < ROWS; j++)
        {
            if (i == j)
                continue;
            values.push_back({straightLineDistance(x, y, z, positions[j][0], positions[j][1], positions[j][2]),
                              {std::make_tuple(x, y, z),
                               std::make_tuple(positions[j][0], positions[j][1], positions[j][2])}});
        }
    }

    std::sort(values.begin(), values.end());

    // mid way realised this requires union find and that it's about connected graphs...

    DSU dsu;
    int tracker = 0;

    for (const auto &i : values)
    {
        if (tracker++ >= 1000)
            break;

        auto a = i.second.first;
        auto b = i.second.second;

        if (!dsu.parent.count(a))
            dsu.parent[a] = a;
        if (!dsu.parent.count(b))
            dsu.parent[b] = b;

        dsu.unite(a, b);
    }

    std::map<
        std::tuple<int, int, int>,
        std::vector<std::tuple<int, int, int>>>
        junctionBoxes;

    for (const auto &[node, _] : dsu.parent)
    {
        junctionBoxes[dsu.find(node)].push_back(node);
    }

    int p = 1;
    std::vector<int> sizes;
    sizes.reserve(junctionBoxes.size());

    for (const auto &[leader, vec] : junctionBoxes)
        sizes.push_back((int)vec.size());

    std::sort(sizes.begin(), sizes.end(), std::greater<int>());

    long long ans = 1;
    for (int i = 0; i < 3 && i < (int)sizes.size(); i++)
        ans *= sizes[i];

    std::cout << ans << "\n";
}