#include "header/exCOM_func.h"
using namespace std;
int main(void){
    string whole_script;
    whole_script=read_file("test.ex");
    cout << compile(whole_script);
    return 0;
}