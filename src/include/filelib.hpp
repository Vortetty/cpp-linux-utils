#include <sstream>
#include <fstream>
#include <codecvt>
#include <vector>

std::wstring tokenize(const std::wstring& s, int n) {
    if (!s.size()) {
        return s;
    }
    std::wstringstream ss;
    ss << s[0];
    for (int i = 1; i < s.size(); i+=n) {
        ss << ' ' << s[i];
    }
    return ss.str();
}

static std::vector<char> ReadAllBytes(char const* filename)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

std::string readFilehex(const char* filename)
{
    std::ifstream fin(filename, std::ios::binary);
    std::stringstream wss;
    wss << std::hex << fin.rdbuf();
    //out = tokenize(out, 8);
    return wss.str();
}

std::wstring readFile8(const char* filename)
{
    std::wifstream wif(filename);
    wif.imbue(std::locale(std::locale(""), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

std::wstring readFile16(const char* filename)
{
    std::wifstream wif(filename);
    wif.imbue(std::locale(std::locale(""), new std::codecvt_utf16<wchar_t>));
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}