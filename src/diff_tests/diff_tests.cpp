#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>
#include <map>

std::string exec_command(const char* cmd) 
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) 
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
    {
        result += buffer.data();
    }
    return result;
}

std::string extractData(const std::string str, std::string type) 
{
    std::stringstream iss(str);
    std::string line;
    std::stringstream output;
    std::string marker;
    std::vector<std::string> search;
    std::map<int,std::string> data;
    bool found = false;

    if(type == "read_write_svfg")
    {
        marker = "****SVFG Statistics****";
        search.push_back("AvgTopLvlPtsSize");
        search.push_back("TotalNode");
        search.push_back("TotalEdge");
        search.push_back("AvgIndOutDeg");
        search.push_back("AvgIndInDeg");
        search.push_back("AvgOutDegree");
        search.push_back("AvgInDegree");
        search.push_back("AvgWeight");
    } 
    else 
    {
        marker = "*********Andersen Pointer Analysis Stats***************";
        search.push_back("AvgTopLvlPtsSize");
    }
    // extract data from command output into a map
    while(getline(iss, line)) 
    {
        if (data.size() >= search.size())
            break;
        if (line.find(marker) != std::string::npos)
            found = true;
        if (found) {
            for (int i = 0; i < search.size(); i++) 
            {   
                if (line.find(search[i]) != std::string::npos) 
                {
                    data.insert(std::make_pair(i, line));
                }
            }
        }
    } 
    std::map<int, std::string>::iterator it;
    for (it = data.begin(); it != data.end(); it++)
    {
        output << it->second << "\n";
    }
    std::cout << output.str();
    return output.str();
}

int main(int argc, char *argv[])
{

    std::string cmd1 = argv[1];
    std::string cmd2 = argv[2];
    std::string folder = argv[3];
    std::string result, result2;
    result = exec_command(("./" + cmd1 + " " +  folder).c_str());
    if (argc == 5)
    {
        std::string folder2 = argv[4];
        result2 = exec_command(("./" + cmd2 + " " +  folder2).c_str());
    }
    else 
    {
        result2 = exec_command(("./" + cmd2 + " " +  folder).c_str());
    }

    std::string data1;
    std::string data2; 

    std::size_t read_write_svfg = cmd1.find("write-svfg");
    if (read_write_svfg!=std::string::npos)
    {
        std::cout << "write\n";
        data1 = extractData(result, "read_write_svfg");
        std::cout << "read\n";
        data2 = extractData(result2, "read_write_svfg");
    } 
    else 
    { 
        data1 = extractData(result, "ander_nander,read_write_ander");
        data2 = extractData(result2, "ander_nander,read_write_ander");
    }

    std::cout << data1.compare(data2) << std::endl;
}
