#define SIZE 1024
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

int map[26] ;
using namespace std;

vector<char> getChars(const char s[], int n)
{
    vector<char> out;

    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            out.push_back(s[i]);
        }
    }
    return out;
}

vector<string> getWords(const string s, int n)
{
    vector<string> out;

    string temp = "";
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            temp.push_back(s[i]);
        }
        else if (s[i] == ',' && s[i + 1] == ' ')
        {
            out.push_back(temp);
            temp = "";
            i = i + 1;
        }
    }
    out.push_back(temp) ;
    return out;
}

int main()
{
    memset(map,0,26) ;
    string ciphertext;
    string exst_words;
    string fre_chars;
    string tem;
    getline(cin, ciphertext);
    getline(cin, tem);
    getline(cin, fre_chars);
    getline(cin, tem);
    getline(cin, exst_words);

    //extraction of chars
    vector<char> char_out = getChars(fre_chars.c_str(), (int)fre_chars.length());

    //extraction of words
    vector<string> string_out = getWords(exst_words,exst_words.length()) ;

    
    return 0;
}