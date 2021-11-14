#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <array>

using namespace std;

string exec_command(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

string extractData(const string str, string type) {

    stringstream iss(str);
    string line;
    std::stringstream read_write_svfg_ss;
    while(getline(iss, line)) {
        string temp = line; 
        if(type == "read_write_svfg"){
            if (temp.find("AvgTopLvlPtsSize") != std::string::npos || temp.find("TotalNode") != std::string::npos || temp.find("TotalEdge") != std::string::npos) {
            read_write_svfg_ss << temp << ","; 
            }
        } else { 
            if (temp.find("AvgTopLvlPtsSize") == 0) {
            return temp;
            }
        }
    }

    return type == "read_write_svfg" ? read_write_svfg_ss.str() : line;
}

int main(int argc, char *argv[])
{

    string cmd1 = argv[1];
    string cmd2 = argv[2];
    string folder = argv[3];
    string result, result2;
    result = exec_command(("./" + cmd1 + " " +  folder).c_str());
    if (argc == 5)
    {
        string folder2 = argv[4];
        result2 = exec_command(("./" + cmd2 + " " +  folder2).c_str());
    }
    else {
        result2 = exec_command(("./" + cmd2 + " " +  folder).c_str());
    }

    string data1;
    string data2; 

    std::size_t read_write_svfg = cmd1.find("write-svfg");
    if (read_write_svfg!=std::string::npos){
        data1 = extractData(result, "read_write_svfg");
        data2 = extractData(result2, "read_write_svfg");
    } else { 
        data1 = extractData(result, "ander_nander,read_write_ander");
        data2 = extractData(result2, "ander_nander,read_write_ander");
    }

    std::cout << data1.compare(data2) << endl;
}
