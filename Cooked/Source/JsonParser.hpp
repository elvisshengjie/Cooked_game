/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file JsonParser.cpp
@author Norman Chan (chan.f)

*/
#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

class JSONObject {
public:
    std::map<std::string, JSONObject> children;
    std::map<std::string, std::string> values; // All raw values stored as strings
    std::vector<JSONObject> array;

    // Methods for easy access
    bool contains(const std::string& key) const;

    // Get raw value
    const std::string& getString(const std::string& key) const;

    // Explicit conversions
    double getDouble(const std::string& key, double defaultValue = 0.0) const;
    float getFloat(const std::string& key, float defaultValue = 0.0f) const;
    int getInt(const std::string& key, int defaultValue = 0) const;
    bool getBool(const std::string& key, bool defaultValue = false) const;

    // Nested object access
    JSONObject& operator[](const std::string& key);
    const JSONObject& operator[](const std::string& key) const;

    // Array access
    std::vector<JSONObject>& getArray();
    const std::vector<JSONObject>& getArray() const;
};

class JSONParser {
public:
    bool parseFile(const std::string& filename, JSONObject& root);

private:
    std::ifstream file;

    void skipWhitespace();
    std::string parseString();
    std::string parseRawValue();
    void parseObject(JSONObject& obj);
    void parseArray(std::vector<JSONObject>& array);

    char peek();
    char get();
};
