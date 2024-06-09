// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/*node  for avl tree syntax */
class SymNode {
public:
    string key;
    int height;
    int occurence;
    void update_height(SymNode* sym)
    {
        int hl,hr;
        hl=(sym->left)?sym->left->height:-1;
        hr=(sym->right)?sym->right->height:-1;
        sym->height=(hl>hr)?hl+1:hr+1;
        return;
        
    }
    
    SymNode* par = NULL;
    SymNode* left = NULL;
    SymNode* right = NULL;
    
    SymNode(string k){
        key=k;
        height=0;
        occurence=1;
    }

    SymNode* LeftLeftRotation(){  //right right imbalance
        if(par==NULL)
        {
            right->par=par;
        }
        else if(par->left==this)
        {
            right->par=par;
            par->left=right;
        }
        else
        {
            right->par=par;
            par->right=right;
        }
        par=right;
        right=right->left;
        if(right!=NULL){
            right->par=this;
        }
        par->left=this;
        update_height(this);
        update_height(this->par);
        return par;
    }
    SymNode* RightRightRotation(){   //left left imbalance
        if(par==NULL) {
            left->par=par;
        } else if(par->left==this) {
            left->par=par;
            par->left=left;
        } else {
            left->par=par;
            par->right=left;
        }
        par=left;
        left=left->right;
        if(left!=NULL){
            left->par=this;
        }
        par->right=this;
        update_height(this);
        update_height(this->par);
        return par;
    }
    SymNode* LeftRightRotation(){     //right left imbalance
        right->RightRightRotation();
        this->LeftLeftRotation();
        return par;
    }
    SymNode* RightLeftRotation(){   //left right imbalance
        left->LeftLeftRotation();
        this->RightRightRotation();
        return par;
    }

    ~SymNode(){
        delete left;
        delete right;
    }
    
};

/*node  for avl tree syntax */

/*tree  of avl tree syntax */

class SymbolTable {
private:
    int size = 0;
    SymNode* root = NULL;

public:
    int BalanceFactor(SymNode *p) {
        int hl;
        int hr;
        hl = (p && p->left) ? p->left->height : -1;
        hr = (p && p->right) ? p->right->height : -1;
        return hl - hr;
    }
    SymbolTable(){
        size=0;
        root=NULL;
    }
    ~SymbolTable(){
        delete root;
    }

    // Insert a key in the symbol table, there is no value now
    void insert(string k){
        if (root==NULL) {
            root=new SymNode(k);
            size++;
            return;
        }
    SymNode* t=root;
    SymNode* u=root;
    while(t!=NULL)
    {
        if(t->key==k) {
            t->occurence++;
            return;
        } else if(t->key>k) {
            u=t;
            t=t->left;
        } else {
            u=t;
            t=t->right;
        }
    }
    if(u->key>k) {
        u->left=new SymNode(k);
        u->left->par=u;
    } else {
        u->right=new SymNode(k);
        u->right->par=u;
    }
    size++;
        t=u;
        int bf;
        while(t!=NULL)
        {
            bf=BalanceFactor(t);
            // Balance Factor and Rotation
            if(bf==0||bf==1||bf==-1) {
                u=t;
                int hl,hr;
                hl = (t->left) ? t->left->height : -1;
                hr = (t->right) ? t->right->height : -1;
                t->height=(hl>hr?hl+1:hr+1);   // in other 4 cases height is itself assigned correctly by rotation fn implied in symnode.cpp
            } else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == -1) {
                   u=t->LeftLeftRotation();
            } else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == 1) {
                   u=t->RightRightRotation();
            } else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == 1) {
                   u=t->LeftRightRotation();
            } else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == -1) {
                   u=t->RightLeftRotation();
            }
            if(t==root) {
                root=u;
                t=u;
            } else {
                t=u;
            }
            t=t->par;
        }
    return;
    }

    int get_size(){
        return size;
    }

    SymNode* get_root(){
        return root;
    }

    int get_count(string k){
        SymNode* t=root;
            while(t!=NULL)
            {
                if(t->key==k) {
                    return t->occurence;
                } else if(t->key>k) {
                    t=t->left;
                } else {
                    t=t->right;
                }
            }
            return 0;
    }

};

class Dict {
private:
    // You can add attributes/helper functions here
    SymbolTable* dictionary;

    void lower_case_conversion(string & s){
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
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
