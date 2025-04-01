/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file JsonParser.cpp
@author Norman Chan (chan.f)

*/
#include "JSONParser.hpp"

bool JSONObject::contains(const std::string& key) const {
    return values.count(key) || children.count(key);
}

const std::string& JSONObject::getString(const std::string& key) const {
    return values.at(key);
}

double JSONObject::getDouble(const std::string& key, double defaultValue) const {
    auto it = values.find(key);
    if (it != values.end()) {
        return std::stod(it->second);
    }
    return defaultValue;
}
float JSONObject::getFloat(const std::string& key, float defaultValue) const {
    auto it = values.find(key);
    if (it != values.end()) {
        return std::stof(it->second);
    }
    return defaultValue;
}

int JSONObject::getInt(const std::string& key, int defaultValue) const {
    auto it = values.find(key);
    if (it != values.end()) {
        return std::stoi(it->second);
    }
    return defaultValue;
}

bool JSONObject::getBool(const std::string& key, bool defaultValue) const {
    auto it = values.find(key);
    if (it != values.end()) {
        return (it->second == "true");
    }
    return defaultValue;
}

JSONObject& JSONObject::operator[](const std::string& key) {
    return children[key];
}

const JSONObject& JSONObject::operator[](const std::string& key) const {
    return children.at(key);
}

std::vector<JSONObject>& JSONObject::getArray() {
    return array;
}

const std::vector<JSONObject>& JSONObject::getArray() const {
    return array;
}

bool JSONParser::parseFile(const std::string& filename, JSONObject& root) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << '\n';
        return false;
    }

    parseObject(root);
    file.close();
    return true;
}

void JSONParser::skipWhitespace() {
    while (std::isspace(peek())) get();
}

char JSONParser::peek() {
    return static_cast<char>(file.peek());
}

char JSONParser::get() {
    return static_cast<char>(file.get());
}

std::string JSONParser::parseString() {
    skipWhitespace();
    std::string result;
    if (get() != '"') return "";

    char c;
    while (file.get(c) && c != '"') {
        result += c;
    }
    return result;
}

std::string JSONParser::parseRawValue() {
    skipWhitespace();
    std::string result;
    char c = peek();
    while (isalnum(c) || c == '.' || c == '-' || c == '+') {
        result += get();
        c = peek();
    }
    return result;
}

void JSONParser::parseObject(JSONObject& obj) {
    skipWhitespace();
    if (get() != '{') return;

    skipWhitespace();
    while (peek() != '}') {
        std::string key = parseString();
        skipWhitespace();
        if (get() != ':') return;

        skipWhitespace();
        if (peek() == '{') {
            parseObject(obj.children[key]);
        }
        else if (peek() == '[') {
            parseArray(obj.children[key].array);
        }
        else if (peek() == '"') {
            obj.values[key] = parseString();
        }
        else {
            obj.values[key] = parseRawValue();
        }

        skipWhitespace();
        if (peek() == ',') get(); // Consume comma
        skipWhitespace();
    }
    get(); // Consume closing brace '}'
}

void JSONParser::parseArray(std::vector<JSONObject>& array) {
    skipWhitespace();
    if (get() != '[') return;

    skipWhitespace();
    while (peek() != ']') {
        JSONObject element;
        skipWhitespace();
        if (peek() == '{') {
            parseObject(element);
        }
        else if (peek() == '"') {
            element.values["value"] = parseString();
        }
        else {
            element.values["value"] = parseRawValue();
        }
        array.push_back(element);

        skipWhitespace();
        if (peek() == ',') get();
        skipWhitespace();
    }
    get(); // Consume closing bracket ']'
}
