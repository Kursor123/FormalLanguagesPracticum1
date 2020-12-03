#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>
#include <fstream>

using Substrings = std::set<std::pair<size_t, size_t>>;

bool IsCorrect(const std::string& language) {
    std::vector<Substrings> temp;
    for (size_t i = 0; i < language.size(); ++i) {
        if (language[i] == 'a' || language[i] == 'b' || language[i] == 'c' || language[i] == '1') {
            temp.emplace_back();
        }
        else if (language[i] == '.' || language[i] == '+') {
            if (temp.size() <= 1) {
                return false;
            }
            temp.pop_back();
        }
        else if (language[i] == '*') {
            if (temp.size() == 0) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    return (temp.size() == 1);
}

Substrings Add(const Substrings& s1, const Substrings& s2) {
    Substrings res = s1;
    for (auto sbstr : s2) {
        res.insert(sbstr);
    }
    return res;
}

Substrings Multiply(const Substrings& s1, const Substrings& s2) {
    Substrings res;
    std::pair<size_t, size_t> eps = {0, 0};
    for (auto& sbstr1 : s1) {
        if (sbstr1 == eps) {
            res = Add(res, s2);
            continue;
        }
        for (auto& sbstr2 : s2) {
            if (sbstr2 == eps) {
                res.insert(sbstr1);
            }
            if (sbstr1.second == sbstr2.first) {
                res.insert({sbstr1.first, sbstr2.second});
            }
            if (sbstr1.first == sbstr1.second) {
                res.insert({sbstr2.first, sbstr2. second});
            }
            if (sbstr2.first == sbstr2.second) {
                res.insert({sbstr1.first, sbstr1.second});
            }
        }
    }
    return res;
}

Substrings Iterate(const Substrings& s, size_t sizeOfString) {
    Substrings res = s;
    res.insert({0, 0});
    res = Add(res, s);
    for (size_t i = 0; i < sizeOfString; ++i) {
        size_t prevSize = res.size();
        res = Add(res, Multiply(res, s));
        if (res.size() == prevSize) {
            break;
        }
    }
    return res;
}

void FindLongestSubstring(std::ostream& out, const std::string& language, const std::string& text) {
    if (!IsCorrect(language)) {
        out << "ERROR";
        return;
    }
    for (auto c : text) {
        if (c != 'a' && c != 'b' && c != 'c') {
            out << "ERROR";
            return;
        }
    }

    Substrings aCoordinates, bCoordinates, cCoordinates;

    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == 'a') {
            aCoordinates.insert({i, i + 1});
        }
        if (text[i] == 'b') {
            bCoordinates.insert({i, i + 1});
        }
        if (text[i] == 'c') {
            cCoordinates.insert({i, i + 1});
        }
    }

    Substrings epsLang;
    epsLang.insert({0, 0});

    std::vector<Substrings> temp;
    for (size_t i = 0; i < language.size(); ++i) {
        if (language[i] == 'a') {
            temp.push_back(aCoordinates);
        }
        if (language[i] == 'b') {
            temp.push_back(bCoordinates);
        }
        if (language[i] == 'c') {
            temp.push_back(cCoordinates);
        }
        if (language[i] == '1') {
            temp.push_back(epsLang);
        }
        if (language[i] == '.') {
            Substrings mult = Multiply(temp[temp.size() - 2], temp.back());
            temp.pop_back();
            temp.pop_back();
            temp.push_back(mult);
        }
        if (language[i] == '+') {
            Substrings summ = Add(temp[temp.size() - 2], temp.back());
            temp.pop_back();
            temp.pop_back();
            temp.push_back(summ);
        }
        if (language[i] == '*') {
            Substrings iter = Iterate(temp.back(), text.size());
            temp.pop_back();
            temp.push_back(iter);
        }
    }
    size_t maxLength = 0;
    for (auto sbstr : temp[0]) {
        if (sbstr.second - sbstr.first > maxLength) {
            maxLength = sbstr.second - sbstr.first;
        }
    }
    out << maxLength;
}

void Test() {
    for (char i = '1'; i <= '9'; ++i) {
        std::string p1 = "input_test_";
        std::string p2 = ".txt";
        std::string p3 = "output_test_";
        std::ifstream f(p1 + i + p2);
        std::string language, text;
        f >> language >> text;
        f.close();
        std::ofstream tmp("tmp.txt");
        FindLongestSubstring(tmp, language, text);
        tmp.close();
        std::string res1, res2;
        std::ifstream tmpIn("tmp.txt");
        std::ifstream right(p3 + i + p2);
        tmpIn >> res1;
        right >> res2;
        tmpIn.close();
        right.close();
        if (res1 == res2) {
            std::cout << "Test " << i << " is OK." << '\n';
        }
        else {
            std::cout << "Test " << i << " is failed." << '\n';
        }
    }
}

int main(int argc, char** argv) {
    std::string language;
    std::string text;
    if (argc == 1) {
        std::cin >> language >> text;
        FindLongestSubstring(std::cout, language, text);
    }
    else {
        Test();
    }
    return 0;
}
