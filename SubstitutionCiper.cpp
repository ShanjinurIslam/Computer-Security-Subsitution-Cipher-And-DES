#define SIZE 1024 
#include <iostream>
#include <string>
#include <vector>

using namespace std ;


vector<char> getChars(const char s[],int n){
    vector<char> out ;

    for(int i=0;i<n;i++){
        if(s[i]>='a'&& s[i]<='z'){
            out.push_back(s[i]) ;
        }
    }
    return out;
}

int main(){
    string ciphertext ;
    string exst_words;
    string fre_chars ;
    getline(cin,ciphertext) ;
    getline(cin,fre_chars) ;
    getline(cin,exst_words) ;

    vector<char> out = getChars(fre_chars.c_str(),(int)fre_chars.length()) ;
    for(int i=0;i<out.size();i++){
        cout<<out[i]<<endl ;
    }
    return 0 ;
}