// Amir hossein alizadeh
#include<iostream>
#include<stdlib.h>
#include<string>
#include <thread>
#include <chrono>
using namespace std;
// Definition of the binary search tree node
struct node
{
    int data; // The value of the node
    struct node* left; // Pointer to the left child
    struct node* right; // Pointer to the right child
    int for_balance; // Keeps track of balance factor for AVL tree
};
// Function to get the balance factor of a node
int func_for_balance(struct node* N)
{
    if (N == NULL)
        return 0;
    return N->for_balance;
}

// Function to find the minimum value node in the tree
struct node* min(struct node* r)
{
    struct node* p = r;

    while (p->left != NULL)
        p = p->left;

    return p;
}
// Function to find the maximum value node in the tree

struct node* maxi(struct node* r)
{
    struct node* p = r;

    while (p->right != NULL)
        p = p->right;

    return p;
}
// Function to calculate the maximum of two integers
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
// Function to create a new node with given data

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
// Function to perform Left-Left Rotation

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
// Function to perform Right-Right Rotation

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
// Function to calculate the balance factor of a node
int Balance(struct node* r)
{
    if (r == NULL)
        return 0;
    return func_for_balance(r->left) - func_for_balance(r->right);
}

// Function to perform a preorder traversal of the tree

void preorder(struct node* r)
{
    if (r != NULL)
    {
        cout << r->data << "  ";
        preorder(r->left);
        preorder(r->right);
    }
}

// Function to perform an inorder traversal of the tree

void inorder(struct node* r)
{
    if (r != NULL)
    {
        inorder(r->left);
        cout << r->data << "  ";
        inorder(r->right);
    }
}

// Function to add a new node with the given key to the tree
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
        // Perform Left-Left rotation
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        chrono::seconds time(2); //2 second
        this_thread::sleep_for(time);
        cout << "\t     ��ͯ\n\t��>> �LL� rotation done !\n\t     ��ͼ\n";
        /////////
        chrono::seconds time1(1); //1 second
        this_thread::sleep_for(time);
        
        return LL_Rotate(r);
      
    }
    // Right Right 
    if (b < -1 && key > r->right->data) {
        // Perform Right-Right rotation
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        chrono::seconds time(2); //2 second
        this_thread::sleep_for(time);
        cout << "\t     ��ͻ\n\t��>> �RR� rotation done !\n\t     ��ͼ\n";
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
        cout << "\t     ��ͻ\n\t��>> �LR� rotation done !\n\t     ��ͼ\n";
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
        
        cout << "\t     ��ͻ\n\t��>> �RL� rotation done !\n\t     ��ͼ\n";
        
        chrono::seconds time1(1); //1 second
        this_thread::sleep_for(time);
        r->right = LL_Rotate(r->right);
        
        return RR_Rotate(r);
    }

    return r;
}

// Function to remove a node with the given key from the tree

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
        cout << "\t     ��ͯ\n\t��>> �LL� rotation done !\n\t     ��ͼ\n";
        return LL_Rotate(r);
    }
    //right right
    if (b > 1 && Balance(r->left) < 0)
    {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ��ͻ\n\t��>> �RR� rotation done !\n\t     ��ͼ\n";
        r->left = RR_Rotate(r->left);
        return LL_Rotate(r);
    }
    //left right
    if (b < -1 && Balance(r->right) <= 0) {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ��ͻ\n\t��>> �LR� rotation done !\n\t     ��ͼ\n";
        return RR_Rotate(r);
    }
    //right left
    if (b < -1 && Balance(r->right) > 0)
    {
        cout << "\t !! my AVL binary tree need rotation now!    wait ...  \n";
        cout << "\t     ��ͻ\n\t��>> �LR� rotation done !\n\t     ��ͼ\n";
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
        cout << "  ��������������������������������������Ŀ\n  � Developed by -*AmirHosseinAliZadeh*- �\n  ����������������������������������������\n";
        
        cout << "\n\n���� Menu :\n          ������������������������������������ͻ\n          � please choose one of this cases :  �\n          �                                    �\n          �    1- Add                          �\n          �    2- Search                       �\n          �    3- Delete                       �\n          �    4- Exit                         �\n          ������������������������������������ͼ\n";
        cin >> select;
        switch (select) {
        case 1:
            system("cls");
            cout << "\n���� Add\n\n";
            //cout << "����������please add your data_node one by one : \n";
            cout << "�������� please Enter your key (example : 98440140 ): \n";
            cin >> key;
            cout << "\n Plz wait ... \n\n";
            for (int i = 0; i < key.size(); i++) {
                chrono::seconds time(2); //2 second
                this_thread::sleep_for(time);
                cout <<" "<<key[i] << "   added"<< endl;
                r = add(r, key[i] - '0');
                cout << "\n     ���������������������������������������ͻ\n��ͯ � Inorder  Traversal is : "; inorder(r);
                cout << "\n��ͯ � Preorder Traversal is : "; preorder(r);
                cout << "\n     ���������������������������������������ͼ\n\n";
            }
            cout << "\n\n��� Final result :\n\n";
            cout << "\n     ���������������������������������������ͻ\n��ͯ � Inorder Traversal is : "; inorder(r);
            cout << "�\n     ���������������������������������������ͼ\n\n";
            if (key == "98440140") {
                cout << "                           " << r->data << "\n                          / \\\n                         " << r->left->data << "   " << r->right->data << "\n                        / \\\n                       " << r->left->left->data << "   " << r->left->right->data << endl;
            }
            cout << "\n     ����������������������������������������ͻ\n��ͯ � Preorder Traversal is : "; preorder(r);
            cout << "�\n     ����������������������������������������ͼ\n";
            cout << "\n the Add_progrom finished . click on any button(except POWER :) )  and go back to menu ...";
            system("pause>n");
            break;

        case 2:
            system("cls");
            int number_search;
            cout << "\n��� Search\n plz search your number : \n";
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

            cout << "\n��� Delete\n";

            cout << "�������� My tree is : \n";

            cout << "\n     ���������������������������������������ͻ\n��ͯ � Inorder Traversal is : "; inorder(r);
            cout << "\n     ���������������������������������������ͼ\n\n";
            if (key == "98440140") {
                cout << "                           " << r->data << "\n                          / \\\n                         " << r->left->data << "   " << r->right->data << "\n                        / \\\n                       " << r->left->left->data << "   " << r->left->right->data << endl;
            }
            cout << "\n     ����������������������������������������ͻ\n��ͯ � Preorder Traversal is : "; preorder(r);
            cout << "\n     ����������������������������������������ͼ\n";
            //cout << "�������� Plz delete every node do you want ? \n";
            
            while (select_delete != '*') {
                cout << "�������� Plz delete every node do you want ? for finish click '*' \n";
                cin >> select_delete;
                r = remove(r, select_delete - '0');
                if (select_delete != '*') {
                    cout << "\n     ���������������������������������������ͻ\n��ͯ � Inorder Traversal is : "; inorder(r);
                    cout << "\n     ���������������������������������������ͼ\n\n";
                    /*if (key == "98440140") {
                        cout << "                           " << r->data << "\n                          / \\\n                         " << r->left->data << "   " << r->right->data << "\n                        / \\\n                       " << r->left->left->data << "   " << r->left->right->data << endl;
                    }*/
                    cout << "\n     ����������������������������������������ͻ\n��ͯ � Preorder Traversal is : "; preorder(r);
                    cout << "\n     ����������������������������������������ͼ\n";
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