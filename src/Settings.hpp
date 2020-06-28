#pragma once

#include <typeinfo>
#include <nlohmann/json.hpp>
#include "Log.hpp"

class Settings {
private:
    static nlohmann::json data;
public:
    static bool has_id(const std::string property_id) {
        return data.count(property_id);
    }

    template <class TYPE>
    static TYPE get(const std::string property_id) {
        return static_cast<TYPE>(data[property_id]);
    }

    template <class TYPE>
    static TYPE get(const std::string property_id1, const std::string property_id2) {
        return static_cast<TYPE>(data[property_id1].at(property_id2));
    }

    template <class TYPE>
    static TYPE get(const std::string property_id1, const std::string property_id2, const std::string property_id3) {
        return static_cast<TYPE>(data[property_id1].at(property_id2).at(property_id3));
    }

    template <class TYPE>
    static void set(const std::string property_id, TYPE value) {
        data[property_id] = value;
    }

    template<class TYPE>
    static void add(const std::string property_id, TYPE value) {
        data[property_id] = value;
    }

    static void load();
    static void save();
};