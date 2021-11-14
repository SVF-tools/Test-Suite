#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>

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
    std::vector<std::string> search;

    if(type == "read_write_svfg")
    {
        search = {"AvgTopLvlPtsSize", "TotalNode", "TotalEdge", "AvgIndOutDeg", "AvgIndInDeg", "AvgOutDegree", "AvgInDegree", "AvgWeight"};
    } 
    else 
    { 
        search = {"AvgTopLvlPtsSize"};
    }
    while(getline(iss, line)) 
    {
        for (std::vector<std::string>::iterator i = search.begin(); i != search.end(); ++i) 
        {   
            if (line.find(*i) != std::string::npos) 
            {
                output << line << ","; 
            }
        }
    }
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
        data1 = extractData(result, "read_write_svfg");
        data2 = extractData(result2, "read_write_svfg");
    } 
    else 
    { 
        data1 = extractData(result, "ander_nander,read_write_ander");
        data2 = extractData(result2, "ander_nander,read_write_ander");
    }

    std::cout << data1.compare(data2) << std::endl;
}
