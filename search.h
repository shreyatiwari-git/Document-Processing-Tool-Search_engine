// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class storage_node{
public:
    vector<int> book_code;
    vector<int> page;
    vector<int> paragraph;
    vector<int> sentence_no;
    vector<string> sentence;
};

class SearchEngine {
private:
    // You can add attributes/helper functions here
    storage_node* storage;
    unsigned int  hash_function(string s){
     unsigned int hash_code=0;
     for(int i=0;i<s.size();i++){
         hash_code=hash_code*127+s[i];
     }
     return hash_code;
    }
    void hash_code_renew(char* s, unsigned int  &hash_code, int start,int end , unsigned int substraction_factor){
        hash_code = ( hash_code -  *(s+start) * substraction_factor ) * 127 + *(s+end);
    }
    void lower_case__conversion(string & s){
        for(int i=0;i<s.size();i++){
            if(s[i]>=65 && s[i]<=90){
                s[i]+=32;
            }
        }
    }
public:
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};
