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

string extractData(const string str) {
    stringstream iss(str);
    string line;
    while(getline(iss, line)) {
        if (line.find("AvgTopLvlPtsSize") == 0) {
            // cout << line << endl;
            return line;
        }
    }
    return line;
}

int main(int argc, char *argv[])
{
    string cmd1 = argv[1];
    string cmd2 = argv[2];
    string folder = argv[3];

    auto result = exec_command(("./" + cmd1 + " " +  folder).c_str());
    auto result2 = exec_command(("./" + cmd2 + " " +  folder).c_str());
    auto data1 = extractData(result);
    auto data2 = extractData(result2);
    cout << data1.compare(data2) << endl;
}