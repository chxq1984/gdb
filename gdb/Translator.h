#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Translator
{
public:
    void split(const string& s, vector<string>& tokens, const char& delim = ' ');
    void split(const string& s, vector<string>& tokens, string split);//���ַ����ָ�
    
    static Translator* getTranslator();
    string removeBacBlank(string data);//ȥ���ַ��������\0
    
    
   
private:
    Translator() {};
    static Translator* instance;
};

