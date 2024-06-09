// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    // Implement your function here
    storage=new storage_node();
}

SearchEngine::~SearchEngine(){
    // Implement your function here
    delete storage;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    storage->book_code.push_back(book_code);
    storage->page.push_back(page);
    storage->paragraph.push_back(paragraph);
    storage->sentence_no.push_back(sentence_no);
    lower_case__conversion(sentence);
    storage->sentence.push_back(sentence);

    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here  
    n_matches=0;
    Node* root=NULL;
    Node* end=new Node(0,0,0,0,0);
    unsigned int storage_size,substraction_factor,hash_value_of_pattern;
    storage_size=storage->sentence.size();
    lower_case__conversion(pattern);
    hash_value_of_pattern=hash_function(pattern);
    substraction_factor=1;
    for(int i=0;i<pattern.size()-1;i++){
        substraction_factor=substraction_factor*127;
    }
    for(int i=0;i<storage_size;i++){
        // int sz1 = storage->sentence[i].size();
        // int sz2 = pattern.size();
        // if( sz1 -sz2 < 0){
        //     continue;
        // }
        unsigned int hash_value_current=hash_function(storage->sentence[i].substr(0,pattern.size()));
        int itr=0;
        while(itr<(storage->sentence[i].size()-pattern.size()+1)){
            if(hash_value_current==hash_value_of_pattern){
                bool value=true;
                for(int j=pattern.size()-1;j>=0;j--){
                    if(pattern[j]!=storage->sentence[i][itr+j]){
                        value=false;
                        break;
                    }
                }
                if(value==true){
                    if(root==NULL){
                        root=new Node(storage->book_code[i],storage->page[i],storage->paragraph[i],storage->sentence_no[i],itr);
                        end->left=root;
                        n_matches++;
                    } else{
                        end->left->right=new Node(storage->book_code[i],storage->page[i],storage->paragraph[i],storage->sentence_no[i],itr);
                        end->left->right->left=end->left;
                        end->left=end->left->right;
                        n_matches++;
                    }
                }
                    hash_code_renew(&storage->sentence[i][0], hash_value_current, itr, itr+pattern.size(), substraction_factor);
                    itr++;
            }else {
                    hash_code_renew(&storage->sentence[i][0], hash_value_current, itr, itr+pattern.size(), substraction_factor);
                    itr++;
            }
        }
    }
    end->left=NULL;
    delete end;
    if(root==NULL){
        return nullptr;
    }
    return root;
}
