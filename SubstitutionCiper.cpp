#define SIZE 1024
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

int map[26] ;
char final_map[26] ;
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
    memset(final_map,0,26) ;
    string ciphertext;
    string plaintext ;
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

    //frequency mapping
    int size = ciphertext.size() ;
    for(int i=0;i<size;i++){
        map[ciphertext[i]-'A']++ ;
    }

    //extraction of character
    
    vector<char> max_chars ;
    while(max_chars.size()<char_out.size()){
        int index = -1 ;
        int max = -1 ;
        for(int i=0;i<26;i++){
            if(map[i]>max){
                max = map[i] ;
                index = i ;
            }
        }
        max_chars.push_back(((char)('A'+index))) ;
        map[index] = -1 ;
    }

    for(int i=0;i<max_chars.size();i++){
        final_map[(int)(char_out[i]-'a')] = max_chars[i] ;
    }

    plaintext = ciphertext ;

    for(int i=0;i<plaintext.size();i++){
        for(int j=0;j<max_chars.size();j++){
            if(plaintext[i]==max_chars[j]){
                plaintext[i] = char_out[j] ;
            }
        }
    }

    

    /*cout<<plaintext<<endl ;

    for(int i=0;i<26;i++){
        cout<<((char)('a'+i))<<" "<<final_map[i]<<endl ;
    }*/

    return 0;
}