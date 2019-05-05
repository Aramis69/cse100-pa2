#include "DictionaryTrie.hpp"
#include "util.hpp"

#include <cstdlib>

using namespace std;

int main(){
    DictionaryTrie* D = new DictionaryTrie();
    bool cont = true;    
    vector<string> vec;
    string pre;
    string str;
    unsigned int completion;
    string option;

    ifstream myFile;
    myFile.open("freq_dict.txt");    
    
    Utils::load_dict(*D,myFile);
    
    while(cont){
        cout << "Enter a pattern with a underscore plz:" << endl;
        getline(cin,pre);

        cout<< "Enter a number of completions UwU:" << endl;
        getline(cin,str);
        //getting a segfault here
        completion = stoi(str);
              
        vec = D->predictUnderscore(pre,completion);
        
        for(unsigned int i=0;i<vec.size();i++){
            cout << vec[i] << endl;
        }        
        cout << "Continue? UwU" << endl;
        getline(cin, option);
        if(option.compare("y") == 0){
            cont = true;
        }
        else{
            cont = false;
        }
    }
    
    delete D;
}
