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

    dataFile << data.dump(4);
    
    dataFile.close();
    Log::log(Log::INFO, "[DONE] Saving settings.\n");
}