// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here    
    dictionary=new SymbolTable();
}

Dict::~Dict(){
    // Implement your function here  
    delete dictionary;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    int i=0;
    string s="";
    while(i<sentence.size()){
        if(  sentence[i] ==  ' ' ||sentence[i] ==  '.' || sentence[i] ==  ',' ||  sentence[i] ==  '-' || sentence[i] ==  ':' || sentence[i] ==  '!' || sentence[i] ==  '"'  || int(sentence[i]) == 39  ||   sentence[i] == '(' || sentence[i] == ')' || sentence[i] == '?'||  sentence[i] == '[' ||  sentence[i] == ']' ||  sentence[i] == ';' ||  sentence[i] =='@'  ){
            if(s==""){
                i++;
                continue;
            }else{
                lower_case_conversion(s);
                dictionary->insert(s);
                s="";
            }
        }else {
            s+=sentence[i];
        }i++;
    }
    if(s==""){
       
    }else{
        lower_case_conversion(s);
        dictionary->insert(s);
        s="";
    }
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here
    return dictionary->get_count(word);
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
        ofstream outfile(filename,ios::app);
    vector<SymNode*> stack;
    SymNode* root=dictionary->get_root();
    if(root==NULL) return;
    stack.push_back(root);
    while(stack.size()!=0) {
        SymNode* itr=stack[stack.size()-1];
        stack.pop_back();
        outfile<<itr->key<<", "<<itr->occurence<<endl;
        if(itr->right){
            stack.push_back(itr->right);
        }
        if (itr->left){
            stack.push_back(itr->left);
        }
    }
    return;
}
