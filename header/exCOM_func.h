#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <map>
#include "../setting/set_tokens.h"

std::string read_file(std::string file_locate){
    std::ifstream t;
    t.open(file_locate);
    std::string str((std::istreambuf_iterator<char>(t)),
    std::istreambuf_iterator<char>());
    return str;
}
std::string char_to_string(char one_char){
    std::string chartostring="";
    chartostring.push_back(one_char);
    return chartostring;
}
std::vector<std::string> split(std::string str,char split_char){
    std::vector<std::string> splited_str;
    std::string str2="";
    for (int i = 0; i < str.length(); i++)
    {
        if(str.at(i)==split_char){
            splited_str.push_back(str2);
            str2="";
        }else
            str2.append(char_to_string(str.at(i)));
    }
    splited_str.push_back(str2);
    return splited_str;
}
#include "exCOM_set.h"
std::vector<Token> analyze_row(std::vector<std::string> script,int i){
    bool continued=false;
    std::vector<Token> tokens;
    for (int j = 0; j < script[i].length(); j++)
    {
        Token token;
        std::string str2="";
        char nowChar=script[i].at(j);


        //띄어쓰기 제거
        if(nowChar==' ' && !continued){
            continue;
        }
        continued=true;
        //제거 완료
        if(nowChar=='['){
            //문자열
            for(j;script[i].at(j)!=']';j++){
                str2.append(char_to_string(script[i].at(j)));
            }
            str2=str2.substr(1,str2.length()-1);
            //set
            token={str2,STRING,0};
        }
        else if(std::find(nums,nums+10,nowChar)!=nums+10){
            //숫자
            bool is_notmaly_ended=true;
            for(j;std::find(nums,nums+10,script[i].at(j))!=nums+10;j++){
                str2.append(char_to_string(script[i].at(j)));
                if(j+1==script[i].length()){
                    is_notmaly_ended=false;
                    break;
                }
            }
            if(is_notmaly_ended)
                j--;
            str2=str2.substr(0,str2.length());
            token={"",NUMBER,std::stoi(str2)};
        }
        else if(std::find(sign,sign+100,nowChar)!=sign+100){
            //기호
            
            str2.append(char_to_string(nowChar));
            token={str2,SPECIAL_CHAR,0};
        }else{
            
        }
        tokens.push_back(token);
    }
    return tokens;
}
void print_Tokens(std::vector<std::vector<Token>> tokens){
    int maxSize=0;
    for(int i=0;i<tokens.size();i++){
        for (int j = 0; j < tokens[i].size(); j++)
        {
            Token token=tokens[i][j];
            if(token.str.size()>maxSize)
                maxSize=token.str.size();
        }
    }
    maxSize+=2;
    for(int i=0;i<tokens.size();i++){
        for (int j = 0; j < tokens[i].size(); j++)
        {
            Token token=tokens[i][j];
            std::string space_bar="";
            for(int k=0;k<maxSize-token.str.size();k++){
                space_bar.append(" ");
            }
            std::cout << token.type << "    \"" << token.str << "\"" << space_bar << token.val << std::endl;
        }
        std::cout << std::endl;
    }
}
std::string compile(std::string whole_script){
    //load settings
    std::map<std::string,std::vector<std::string>> defind = defind_analyze();
    //ended loading settings
    std::string compiled_cpp_script="";
    //compiling

    //analyze code
    std::vector<std::string> script=split(whole_script,'\n');
    std::vector<std::vector<Token>> tokens;
    for (int i = 0; i < script.size(); i++)
    {
        tokens.push_back(analyze_row(script,i));
    }
    //end analyzing code
    //debug
    print_Tokens(tokens);
    //end
    return compiled_cpp_script;
}