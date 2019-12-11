#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <tuple>
#include <string>
#include <algorithm>
#include <sstream>

bool iscomma(char c)
{
    return (c == ',');
}

bool notcomma(char c)
{
    return (c != ',');
}

std::vector<std::string> splitTwo(const std::string& line)
{
    std::vector<std::string> separated;
    typedef std::string::const_iterator line_iterator;

    line_iterator i = line.begin();
    i = std::find_if(i, line.end(), iscomma);
    if(i == line.end())
    {
        separated.push_back(line);
    }
    else
    {
        separated.push_back(std::string(line.begin(), i));
        separated.push_back(std::string(++i, line.end()));
    }
    return separated;
}


std::vector<std::string> split(const std::string& line)
{
    std::vector<std::string> separated;
    typedef std::string::const_iterator line_iterator;

    line_iterator i = line.begin();
    while(i != line.end())
    {
        line_iterator j = std::find_if(i, line.end(), iscomma);
        if(i == line.begin() && j == line.end())
        {
            separated.push_back(line);
            return separated;
        }
        else if(j != line.end())
        {
            separated.push_back(std::string(i, j));
            line_iterator temp = line.end();
            i = ++j;
        }
        else
        {
            separated.push_back(std::string(i, line.end()));
            i = j;
        }
        
    }
    return separated;
}

void stringVector2intVector(std::vector<std::vector<std::string>>& mapStr ,std::vector<std::vector<int>>& mapInt)
{
    for(int i = 0; i < mapStr.size(); ++i)
    {
        for(int j = 0; j < mapStr[i].size(); ++j)
        {
            int temp = std::stoi(mapStr[i][j]);
            mapInt[i][j] = temp;
        }
    }
}

void readMapParams(const std::string& filename,
                   std::array<int,2>& mapSize,
                   int& collisionThresh,
                   std::array<int,2>& robotPos,
                   std::vector<std::array<int,2>>& objectTraj,
                   std::vector<std::vector<int>>& mapInt)
{
    std::ifstream stream(filename);
    if(stream)
    {
        std::string line;
        std::vector<std::string> separated;
        int mapRow, mapCol;
        int robotX, robotY, objectX, objectY;


        // read map size
        std::getline(stream, line);
        if(split(line)[0] == "N")
        {
            std::getline(stream, line);
            separated = split(line);
            mapRow = std::stoi(separated[0]);
            mapCol = std::stoi(separated[1]);
            mapSize =  {mapRow, mapCol};
        }
        std::getline(stream, line);
        if(split(line)[0] == "C")
        {
            std::getline(stream, line);
            separated = split(line);
            collisionThresh = std::stoi(separated[0]);
        }
        std::getline(stream, line);
        if(split(line)[0] == "R")
        {
            std::getline(stream, line);
            separated = split(line);
            robotX = std::stoi(separated[0]);
            robotY = std::stoi(separated[1]);
            robotPos = {robotX, robotY};
        }
        std::getline(stream, line);
        if(split(line)[0] == "T")
        {
            std::getline(stream, line);
            separated = split(line);
            while(separated[0] != "M")
            {
                objectX = std::stoi(separated[0]);
                objectY = std::stoi(separated[1]);
                objectTraj.push_back({objectX, objectY});
                std::getline(stream, line);
                separated = split(line);
            }
        }
        std::vector<std::vector<std::string>> map;
        if(separated[0] == "M")
        {
            std::getline(stream, line);
            separated = split(line);
            while(separated[0] != "E")
            {
                map.push_back(separated);
                std::getline(stream, line);
                separated = split(line);
            }
            mapInt.resize(mapRow , std::vector<int>(mapCol));
            stringVector2intVector(map, mapInt);
        }

    }
    else
    {
        throw std::runtime_error("Could not find file");
    }
    
    stream.close();
}

int main()
{
    std::array<int,2> mapSize;
    int collisionThresh;
    std::array<int,2> robotPos;
    std::vector<std::array<int,2>> objectTraj;
    std::vector<std::vector<int>> map;
    const std::string filename = "/home/oyku/Documents/Oyku/Github/Opencv_tutorials/16782_HW1_fall19_v2/code/sample.txt";

    readMapParams(filename, mapSize, collisionThresh, robotPos, objectTraj, map);

    return 0;
}