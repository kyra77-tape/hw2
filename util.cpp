#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> words;
    std::string cur;
    for (size_t i = 0; i <= rawWords.size(); i++) {
        bool isWordChar = false;
        if (i < rawWords.size()) {
            unsigned char c = (unsigned char)rawWords[i];
            isWordChar = !std::ispunct(c) && !std::isspace(c);
        }
        if (isWordChar) {
            cur += rawWords[i];
        } else {
            if (cur.size() >= 2) {
                words.insert(convToLower(cur));
            }
            cur = "";
        }
    }
    return words;
}

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
        std::find_if(s.begin(),
             s.end(),
             std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
        std::find_if(s.rbegin(),
             s.rend(),
             std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
        s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}