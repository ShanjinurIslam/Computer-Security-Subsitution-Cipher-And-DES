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

vector<pair<char,int> > getIndexes(vector<char> chars,string word){
    int i = 0 ;
    vector<pair<char,int> > maps ;
    while(i<chars.size()){

        pair<char,int> apair ;
        apair.first = chars[i] ;
        apair.second = 0 ;
        for(int j=0;j<word.length();j++){
            if(chars[i]==word[j]){
                apair.first = chars[i] ;
                apair.second++ ;
            }
        }
        maps.push_back(apair) ;
        i++ ;
    }

    return maps ;
}

string getReplaced(string input,char a,char b){
    for(int i=0;i<input.size();i++){
        if(input[i]==a && a>='A' && a<='Z'){
            input[i] = b ;
        }
    }
    return input ;
}

string plainTociper(string s,char map[]){
    int i = 0 ;
    string m ;
    while(i<s.size()){
        if(map[s[i]-'a']!=0 && (s[i]>='a' && s[i]<='z')) m+= map[s[i]-'a'] ;
        else m+= s[i] ;
        i++ ;
    }
    return m ;
}

int main()
{
    freopen("output.txt","w",stdout) ;
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
    vector<string> word_out = getWords(exst_words,exst_words.length()) ;

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

    for(int i=0;i<word_out.size();i++){
        vector<pair<char,int> > indexes = getIndexes(char_out,word_out[i]) ; //correct

        for(int j=0;j<=plaintext.size()-word_out[i].size();j++){
            string tem = plaintext.substr(j,word_out[i].size()) ;
            bool flag = true ;
            for(int k=0;k<indexes.size();k++){
                int count = 0 ;
                int count2 = 0 ;
                for(int m=0;m<tem.size();m++){
                    if(tem[m]==indexes[k].first && tem[m]==word_out[i].at(m)){
                        count++ ;
                    }
                    if(tem[m]==indexes[k].first){
                        count2++ ;
                    }
                }
                if(count!=indexes[k].second || count2!=count) flag = false ;
                if(flag==false) break ;
            }

            bool flag2 = true ;
            for(int f=0;f<tem.size();f++){
                if(tem[f]>='a' && tem[f]<='z'){
                }
                else flag2 = false ;
            }

            if(flag2){
                if(tem!=word_out[i]) continue ;
            }
            
            if(flag && !flag2){
                for(int n=0;n<tem.size();n++){
                    if(final_map[word_out[i].at(n)-'a']==0) final_map[word_out[i].at(n)-'a'] = tem[n] ;
                    plaintext = getReplaced(plaintext,tem[n],word_out[i].at(n)) ;
                }
            }
        }
    }

    //guessing after the initial output
    final_map['w'-'a'] = 'W' ;
    plaintext = getReplaced(plaintext,'W','w') ;
    final_map['f'-'a'] = 'J' ;
    plaintext = getReplaced(plaintext,'J','f') ;
    final_map['j'-'a'] = 'V' ;
    plaintext = getReplaced(plaintext,'V','j') ;

    cout<<"Cipertext to Plaintext:\n"<<endl ;
    cout<<plaintext<<endl ;
    cout<<endl ;

    cout<<"Alphabet Mapping:\n"<<endl ;

    for(int i=0;i<26;i++){
        cout<<((char)('a'+i))<<"\t" ;
    }
    cout<<endl ;
    for(int i=0;i<26;i++){
        cout<<final_map[i]<<"\t" ;
    }
    cout<<endl<<endl ;

    cout<<"Plaintext to Ciphertext:\n"<<endl ;
    string m = plainTociper(plaintext,final_map) ;
    cout<<m<<endl<<endl ;

    cout<<"Accuracy:\n" ;
    float acc  = (100.0*(ciphertext.length()-strcmp(ciphertext.c_str(),m.c_str())))/(1.0*ciphertext.length()) ;
    cout<<acc<<"%"<<endl ;
    return 0;
}