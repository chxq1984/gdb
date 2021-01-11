#include "Translator.h"

Translator* Translator:: instance = nullptr;

void Translator:: split(const string& s, vector<string>& tokens, const char& delim) {
    tokens.clear();
    size_t lastPos = s.find_first_not_of(delim, 0);
    size_t pos = s.find(delim, lastPos);
    while (lastPos != string::npos) {
        tokens.emplace_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delim, pos);
        pos = s.find(delim, lastPos);
    }
}
void Translator::split(const string& s, vector<string>& tokens, string split)
{
    int splitLen = split.length();//分割字符串的长度
    int slen = s.length();
    vector<int>positions;//存放split的下标

    string temp = s;
    int position = temp.find(split);
    int cutLen = 0;//切去的长度
    while (position != temp.npos) {
        int relPosition = slen - temp.length() + position;
        positions.push_back(relPosition);
        temp = temp.substr(position + splitLen);
        position = temp.find(split);
        
    }
    int ptr = 0;
    for (int position : positions) {
        string content = s.substr(ptr, position - ptr);
        tokens.push_back(content);
        ptr = position + splitLen;
    }
    tokens.push_back(s.substr(ptr));

}
Translator* Translator::getTranslator()
{
    if (instance == nullptr)
        instance = new Translator;
    return instance;
}

string Translator::removeBacBlank(string data)
{
    int position = data.find('\0');
	return data.substr(0,position);
}
