#define MAX_TEXT_IN_LINE 1000
std::map<std::string,std::vector<std::string>> defind_analyze(){
    std::map<std::string,std::vector<std::string>> df;
    std::string definds=read_file("setting/defind.txt"); 
    std::vector<std::string> splited_defind;
    splited_defind=split(definds,'\n');
    for (int i = 0; i < splited_defind.size(); i++)
    {
        std::string now_defind_text=splited_defind[i];
        std::string defind_str="";
        std::string value_str="";
        bool spaced=false;
        for (int j = 0; j < now_defind_text.length(); j++)
        {
            std::string now_string=char_to_string(now_defind_text.at(j));
            if(now_string==" ")
                spaced=true;
            else{
                if(spaced)
                    defind_str.append(now_string);
                else
                    value_str.append(now_string);
            }
        }
        //space로 구분 완료
        df.insert(std::pair<std::string,std::vector<std::string>>(defind_str,split(value_str,'|')));
    }
    return df;
}

char nums[]={'1','2','3','4','5','6','7','8','9','0'};
char sign[100]={'+','-','*','/','{','}','(',')','=',};

struct Token{
    std::string str;
    int type;
    int val;
};