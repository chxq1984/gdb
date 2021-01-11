#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Translator
{
public:
    void split(const string& s, vector<string>& tokens, const char& delim = ' ');
    void split(const string& s, vector<string>& tokens, string split);//按字符串分割
    
    static Translator* getTranslator();
    string removeBacBlank(string data);//去掉字符串后面的\0
    
    
   
private:
    Translator() {};
    static Translator* instance;
};

