#pragma once
#include <iostream>
#include <string>

class Log {
private:
    template <typename T>
    static std::string to_string(const T &x) {
        return std::to_string(x);
    }
    
    static std::string to_string(const char *x) {
        return x;
    }

    static std::string to_string(const std::string &x) {
        return x;
    }
    
    static std::string format(const char* form) {
        return form;
    }

    template <typename T, typename... Args>
    static std::string format(const char* form, const T &x, const Args &... args) {
        std::string r;
        while(*form != '{') r += *form++;
        r += to_string(x); form++;
        r += format(++form, args...);
        return r;
    }

    inline static int level;
public:
    enum {
        INFO, WARNING, ERROR
    };
    
    static void set_level(int lvl) {
        Log::level = lvl;
    }

    template <typename... Args>
    static void log(int lvl, const char* form, const Args &... args) {
        if(lvl >= Log::level) {
            std::cerr << format(form, args...);
        }
    }
};