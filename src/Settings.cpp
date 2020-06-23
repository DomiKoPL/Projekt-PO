#include "Settings.hpp"
#include <fstream>
#include <iostream>
#include "Log.hpp"

using json = nlohmann::json;

json Settings::data;

void Settings::load() {
    Log::log(Log::INFO, "[****] Loading settings.\n");
    std::ifstream dataFile("data/settings.json");
    
    dataFile >> data;
    
    dataFile.close();
    Log::log(Log::INFO, "[DONE] Loading settings.\n");
}

void Settings::save() {
    Log::log(Log::INFO, "[****] Saving settings.\n");
    std::ofstream dataFile("data/settings.json");
    dataFile.clear();
    
    std::string res = data.dump(4);
    int array = 0;
    for(int i = 0; i < (int)res.size(); i++) {
        if(res[i] == '[') array++;
        if(res[i] == ']') array--;
        if(array > 0 and ((res[i] == '\n' or res[i] == '\t') or (res[i] == ' ' and res[i - 1] == ' '))) {
            res.erase(i, 1);
            i--;
        }
    }
    dataFile << res;
    
    dataFile.close();
    Log::log(Log::INFO, "[DONE] Saving settings.\n");
}