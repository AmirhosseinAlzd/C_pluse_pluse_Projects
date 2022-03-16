// Amir hossein alizadeh
#include<iostream>
#include<stdlib.h>
#include<string>
#include <thread>
#include <chrono>
using namespace std;
//////////////////////////////
struct node
{
    int data;
    struct node* left;
    struct node* right;
    int for_balance;
};
/////////////////////////////
int func_for_balance(struct node* N)
{
    if (N == NULL)
        return 0;
    return N->for_balance;
}

/////////////////////////////
struct node* min(struct node* r)
{
    struct node* p = r;

    while (p->left != NULL)
        p = p->left;

    return p;
}
//////////////////////////////////////////////////////////////// 

struct node* maxi(struct node* r)
{
    struct node* p = r;

    while (p->right != NULL)
        p = p->right;

    return p;
}
//**************************************************************************************

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
//**************************************************************************************

struct node* create(int data_node)
{
    struct node* n;

    n = new(struct node);
    n->data = data_node;
    n->left = NULL;
    n->right = NULL;
    n->for_balance = 1;
    return(n);
}
//**************************************************************************************
struct node* LL_Rotate(struct node* A)
{

    struct node* B, * C;

    B = A->left;
    C = B->right;

    B->right = A;
    A->left = C;

    A->for_balance = max(func_for_balance(A->left), func_for_balance(A->right)) + 1;
    B->for_balance = max(func_for_balance(B->left), func_for_balance(B->right)) + 1;

    return B;
}
//**************************************************************************************
struct node* RR_Rotate(struct node* A)
{

    struct node* B, * C;

    B = A->right;
    C = B->left;

    B->left = A;
    A->right = C;

    A->for_balance = 1 + max(func_for_balance(A->left), func_for_balance(A->right));
    B->for_balance = 1 + max(func_for_balance(B->left), func_for_balance(B->right));

    return B;
}
//************************************************************************************** 
int Balance(struct node* r)
{
    if (r == NULL)
        return 0;
    return func_for_balance(r->left) - func_for_balance(r->right);
}

//**************************************************************************************

void preorder(struct node* r)
{
    if (r != NULL)
    {
        cout << r->data << "  ";
        preorder(r->left);
        preorder(r->right);
    }
}
void inorder(struct node* r)
{
    if (r != NULL)
    {
        inorder(r->left);
        cout << r->data << "  ";
        inorder(r->right);
    }
}
//**************************************************************************************
struct node* add(struct node* r, int key)
{

    if (r == NULL)
        return(create(key));

    if (key < r->data)
        r->left = add(r->left, key);
    else if (key > r->data)
        r->right = add(r->right, key);
    else { // same data node
        cout << "Error same datas : " << key << " delete\n";
        return r;
    }

    r->for_balance = 1 + max(func_for_balance(r->left), func_for_balance(r->right));

    int b = Balance(r);

    // Left Left 
    if (b > 1 && key < r->left->data) {
        
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        chrono::seconds time(2); //2 second
        this_thread::sleep_for(time);
        cout << "\t     ษออฏ\n\tออ>> บLLบ rotation done !\n\t     ศออผ\n";
        /////////
        chrono::seconds time1(1); //1 second
        this_thread::sleep_for(time);
        
        return LL_Rotate(r);
      
    }
    // Right Right 
    if (b < -1 && key > r->right->data) {
        
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        chrono::seconds time(2); //2 second
        this_thread::sleep_for(time);
        cout << "\t     ฎออป\n\tออ>> บRRบ rotation done !\n\t     ศออผ\n";
        ////////
        chrono::seconds time1(1); //1 second
        this_thread::sleep_for(time);
        
        return RR_Rotate(r);
    }
    // Left Right 
    if (b > 1 && key > r->left->data)
    {
        
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        chrono::seconds time(2); //2 second
        this_thread::sleep_for(time);
        cout << "\t     ษออป\n\tออ>> บLRบ rotation done !\n\t     ศออผ\n";
        ////////
        chrono::seconds time1(1); //1 second
        this_thread::sleep_for(time);
        r->left = RR_Rotate(r->left);
       
        return LL_Rotate(r);
    }

    // Right Left 
    if (b < -1 && key < r->right->data)
    {
        
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        chrono::seconds time(2); //2 second
        this_thread::sleep_for(time);
        
        cout << "\t     ษออป\n\tออ>> บRLบ rotation done !\n\t     ศออผ\n";
        
        chrono::seconds time1(1); //1 second
        this_thread::sleep_for(time);
        r->right = LL_Rotate(r->right);
        
        return RR_Rotate(r);
    }

    return r;
}


struct node* remove(struct node* r, int key)
{
    struct node* t;
    if (r == NULL)
        return r;
    if (key < r->data)
        r->left = remove(r->left, key);
    else if (key > r->data)
        r->right = remove(r->right, key);
    else
    {
        if ((r->left == NULL) || (r->right == NULL))
        {
            t = r->left ? r->left : r->right;
            if (t == NULL)
            {
                t = r;
                r = NULL;
            }
            else
                *r = *t;
            free(t);
        }
        else
        {
            char child;
            cout << "\n which child do you want to replace with root ? the biggest child of the left subtree (L) or another (R) ?  plz Specify by word of L or R !! \n ";
            cin >> child;
            switch (child) {
            case 'L':
                t = maxi(r->left);
                r->data = t->data;
                r->left = remove(r->left, t->data);
                break;
            case 'R':
                t = min(r->right);
                r->data = t->data;
                r->right = remove(r->right, t->data);
                break;
            }

        }
    }
    if (r == NULL)
        return r;

    r->for_balance = 1 + max(func_for_balance(r->left), func_for_balance(r->right));

    int b = Balance(r);
    // left left
    if (b > 1 && Balance(r->left) >= 0) {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ษออฏ\n\tออ>> บLLบ rotation done !\n\t     ศออผ\n";
        return LL_Rotate(r);
    }
    //right right
    if (b > 1 && Balance(r->left) < 0)
    {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ฎออป\n\tออ>> บRRบ rotation done !\n\t     ศออผ\n";
        r->left = RR_Rotate(r->left);
        return LL_Rotate(r);
    }
    //left right
    if (b < -1 && Balance(r->right) <= 0) {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ฎออป\n\tออ>> บLRบ rotation done !\n\t     ศออผ\n";
        return RR_Rotate(r);
    }
    //right left
    if (b < -1 && Balance(r->right) > 0)
    {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ฎออป\n\tออ>> บLRบ rotation done !\n\t     ศออผ\n";
        r->right = LL_Rotate(r->right);
        return RR_Rotate(r);
    }

    return r;
}

///////////////////////////////////////////////////////////////

bool search(struct node* r, int key)
{
    while (r != NULL)
    {
        if (key > r->data)
            r = r->right;

        else if (key < r->data)
            r = r->left;
        else
            return true;
    }
    return false;
}


//////////////////////////////////////////////////////////////////////
int main()
{
    struct node* r = NULL;
    
    //menu
    
    string key;
    int select = 0;
    char select_delete = '0';
    while (select != 4) {

        system("cls");
        cout << "  ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ\n  ณ Developed by -*AmirHosseinAliZadeh*- ณ\n  ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู\n";
        
        cout << "\n\nฑฑฑฑ Menu :\n          ษออออออออออออออออออออออออออออออออออออป\n          บ please choose one of this cases :  บ\n          บ                                    บ\n          บ    1- Add                          บ\n          บ    2- Search                       บ\n          บ    3- Delete                       บ\n          บ    4- Exit                         บ\n          ศออออออออออออออออออออออออออออออออออออผ\n";
        cin >> select;
        switch (select) {
        case 1:
            system("cls");
            cout << "\nฑฑฑฑ Add\n\n";
            //cout << "ฤฤฤฤฤฤฤฤฤฤplease add your data_node one by one : \n";
            cout << "๐๐๐๐๐๐๐๐ please Enter your key (example : 98440140 ): \n";
            cin >> key;
            cout << "\n Plz wait ... \n\n";
            for (int i = 0; i < key.size(); i++) {
                chrono::seconds time(2); //2 second
                this_thread::sleep_for(time);
                cout <<" "<<key[i] << "   added"<< endl;
                r = add(r, key[i] - '0');
                cout << "\n     ษอออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Inorder  Traversal is : "; inorder(r);
                cout << "\nอออฏ บ Preorder Traversal is : "; preorder(r);
                cout << "\n     ศอออออออออออออออออออออออออออออออออออออออผ\n\n";
            }
            cout << "\n\nฑฑฑ Final result :\n\n";
            cout << "\n     ษอออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Inorder Traversal is : "; inorder(r);
            cout << "บ\n     ศอออออออออออออออออออออออออออออออออออออออผ\n\n";
            if (key == "98440140") {
                cout << "                           " << r->data << "\n                          / \\\n                         " << r->left->data << "   " << r->right->data << "\n                        / \\\n                       " << r->left->left->data << "   " << r->left->right->data << endl;
            }
            cout << "\n     ษออออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Preorder Traversal is : "; preorder(r);
            cout << "บ\n     ศออออออออออออออออออออออออออออออออออออออออผ\n";
            cout << "\n the Add_progrom finished . click on any button(except POWER :) )  and go back to menu ...";
            system("pause>n");
            break;

        case 2:
            system("cls");
            int number_search;
            cout << "\nฑฑฑ Search\n plz search your number : \n";
            cin>>number_search;
            if (search(r, number_search))
                cout << "Yes";
            else
                cout << "Not found !";
            cout << "\n the search_progrom finished . click on any button(except POWER :) )  and go back to menu ...";
            system("pause>n");
            break;
        case 3:
            system("cls");

            cout << "\nฑฑฑ Delete\n";

            cout << "๐๐๐๐๐๐๐๐ My tree is : \n";

            cout << "\n     ษอออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Inorder Traversal is : "; inorder(r);
            cout << "\n     ศอออออออออออออออออออออออออออออออออออออออผ\n\n";
            if (key == "98440140") {
                cout << "                           " << r->data << "\n                          / \\\n                         " << r->left->data << "   " << r->right->data << "\n                        / \\\n                       " << r->left->left->data << "   " << r->left->right->data << endl;
            }
            cout << "\n     ษออออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Preorder Traversal is : "; preorder(r);
            cout << "\n     ศออออออออออออออออออออออออออออออออออออออออผ\n";
            //cout << "๐๐๐๐๐๐๐๐ Plz delete every node do you want ? \n";
            
            while (select_delete != '*') {
                cout << "๐๐๐๐๐๐๐๐ Plz delete every node do you want ? for finish click '*' \n";
                cin >> select_delete;
                r = remove(r, select_delete - '0');
                if (select_delete != '*') {
                    cout << "\n     ษอออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Inorder Traversal is : "; inorder(r);
                    cout << "\n     ศอออออออออออออออออออออออออออออออออออออออผ\n\n";
                    /*if (key == "98440140") {
                        cout << "                           " << r->data << "\n                          / \\\n                         " << r->left->data << "   " << r->right->data << "\n                        / \\\n                       " << r->left->left->data << "   " << r->left->right->data << endl;
                    }*/
                    cout << "\n     ษออออออออออออออออออออออออออออออออออออออออป\nอออฏ บ Preorder Traversal is : "; preorder(r);
                    cout << "\n     ศออออออออออออออออออออออออออออออออออออออออผ\n";
                }
                else
                    cout << "\n the delete progrom finished . click on any button except POWER :) and go back to menu ...";
            }
            //preorder(r);
            system("pause>n");
            break;
        case 4:
            exit(0);
            break;
        }
    }

    system("pause>n");

}