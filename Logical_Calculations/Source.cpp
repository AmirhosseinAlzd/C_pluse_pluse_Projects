#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<stack>
#include<boost/dynamic_bitset.hpp>
#include<Bits.h>
#include<fstream>
#include<iomanip>
#include<math.h>
using namespace std;


struct myfuncations {
    string name_func; 
    string func;
    boost::dynamic_bitset<> func_bitcet;
};
struct Operators {
    char And;
    char Or;
    char Not;
    char Xor;
}Ope;




int isOperand(char ch)
{
    return  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int isdegit(char ch)
{
    return (ch >= '0' && ch <= '9');
}
///////////////////////////////////////////////////////
int Prec(char ch)
{
    if (Ope.Xor == ch)
        return 1;
    else if (Ope.Or == ch)
        return 2;
    else if (Ope.And == ch)
        return 3;
    else if (Ope.Not == ch)
        return 4;
    
    return -1;
}

///////////////////////////////////////////////////////
string inToPost(string e)
{
    int i, k;
    string p, temp;
    //struct Stack* s;
    //s = create(strlen(e));
    stack<char>s;
    for (i = 0, k = -1; e[i]; ++i)
    {
        if (isOperand(e[i])) {
            //e[++k] = e[i];
            temp = e[i];
            while (isdegit(e[i + 1])) {
                temp += e[i + 1];
                i++;
            }
            p += temp;
        }
        else if (e[i] == '(') {
            s.push(e[i]);
        }
        else if (e[i] == ')')
        {
            while (!s.empty() && s.top() != '(') {
                p+=s.top();
                s.pop();
            }
            if (!s.empty() && s.top() != '(')
                return NULL;
            else {
                s.pop();
            }
        }
        else // operator
        {
            while (!s.empty() && Prec(e[i]) <= Prec(s.top())) {
                p+=s.top();
                s.pop();

            }
            s.push(e[i]);
        }
    }
    // pop all the operators 
    while (!s.empty()) {
        //e[++k] = s.top();
        p+= s.top();
        s.pop();
    }
    p.push_back(NULL);
    return p;
}
/////////////////////////////////////////////////////////////

boost::dynamic_bitset<> evalution(string e , vector<boost::dynamic_bitset<>> mybitset , vector<string> primary_input , Operators Ope , vector<myfuncations> o)
{
    boost::dynamic_bitset<> num1;
    boost::dynamic_bitset<> num2;
    boost::dynamic_bitset<> naghiz;
    int i;
    stack<boost::dynamic_bitset<>>s;
    string temp;
    
    for (i = 0; e[i]; ++i)
    {
        if (isOperand(e[i])) {
            temp = e[i];
            while (isdegit(e[i + 1])) {
                temp += e[i + 1];
                i++;
            }
            for (int k1 = 0; k1 <primary_input.size()-1; k1++) {
                if (temp == primary_input[k1]) {
                    s.push(mybitset[k1]);
                }
            }
            for (int k2 = 0; k2 <o.size() ; k2++) {
                 if (temp == o[k2].name_func) {
                    s.push(o[k2].func_bitcet);
                 }
            }
        }   
        else if (e[i] == Ope.Not) {
            naghiz = s.top();
            s.push(~naghiz);
        }
        else
        {

            num1 = s.top();
            s.pop();
            
            num2 = s.top();
            s.pop();

            if (e[i] == Ope.Or) {
                s.push(num1 | num2);
            }
            else if (e[i] == Ope.And) {
                s.push(num1 & num2);
            }
            else if (e[i] == Ope.Xor) {
                s.push(num1 ^ num2);
            }
            
        }
    }
        
    return s.top();
    s.pop();
}



int main()
{
    //C:/Users/amirh/Desktop/fun.txt
    string addres_location_file;
    cout << "pleas enter the addres lucation of file : .....\n";
    cin >> addres_location_file;
    ifstream fin;
    fin.open(addres_location_file);
    while (!fin) {
        cout << "file not found ! plz enter again ....\n";
        cin >> addres_location_file;
        fin.open(addres_location_file);
    }
    cout << "open file succesfully ...\n";
    string temp1, temp2, temp3;


    ///////////////////////////////////////////take operator from file//////////////////////////////
    fin >> temp1;

    vector<string>str_operator;

    for (int m = 0; m < 8; m++) {
        str_operator.emplace_back();
        fin >> str_operator[m];
        if (str_operator[m] == "AND" || str_operator[m] == "and") {
            Ope.And = str_operator[m - 1][0];
        }
        else if (str_operator[m] == "OR" || str_operator[m] == "or") {
            Ope.Or = str_operator[m - 1][0];
        }
        else if (str_operator[m] == "NOT" || str_operator[m] == "not") {
            Ope.Not = str_operator[m - 1][0];
        }
        else if (str_operator[m] == "XOR" || str_operator[m] == "Xor") {
            Ope.Xor = str_operator[m - 1][0];
        }
    }
   
   ///////////////////////////////////////////take operator from file//////////////////////////////
   

    ///////////////////////////////////////////take primary_input from file//////////////////////// 
    fin >> temp2;
    vector<string>primary_input;
    int number_primary_input=0;
    while (1) {
        primary_input.emplace_back();
        fin >> primary_input[number_primary_input];
        if (primary_input[number_primary_input] == "!")
            break;
        number_primary_input++;
    }
    if (number_primary_input > 10) {
        cout << "the number of primary input is bigger than 10 . please edit your file and run agian ....";
        string test ;
        cin >> test;
    }

    ///////////////////////////////////////////take primary_input from file////////////////////////

        /////////////////////////////////////////my bitset//////////////////////////////////
    short int buffer = 0;
    short int size = pow(2, number_primary_input);

    vector<boost::dynamic_bitset<>> mybitset;

    for (size_t i = 0; i < number_primary_input; i++)
    {
        mybitset.emplace_back();

        mybitset[i].resize(pow(2, number_primary_input));
    }

    buffer = size;

    for (size_t i = 0; i < number_primary_input; i++)
    {
        for (size_t j = 0; j < size;)
        {

            for (size_t k = 0; k < buffer / 2; j++, k++)
            {
                mybitset[i].set(j);
            }
            j += buffer / 2;
        }
        buffer /= 2;
    }

    //////////////////////////////////////////////mybitset///////////////////////////////////




    ////////////////////////////////////////take funcation from file///////////////////////////////////
    vector<struct myfuncations>o;
    int number_func = 0;
    int c = 0;
   
    fin >> temp3;

    while (1) {
        o.emplace_back();
        fin >> o[c].name_func;
        fin >> temp3;
        fin >> o[c].func;
        if (o[c].name_func == "!")
            break;
        c++;
    }
    number_func = c;


    fin.close();
    ////////////////////////////////////////take funcation from file///////////////////////////////////

    /*cout << "\n";
    cout << inToPost(o[0].func) << "\n";
    cout << inToPost(o[1].func) << "\n";
    cout << inToPost(o[2].func) << "\n";
    cout << inToPost(o[3].func) << "\n";*/
   

    for (int w = 0; w < number_func; w++) {
        o[w].func_bitcet = evalution(inToPost(o[w].func), mybitset, primary_input, Ope, o);

    }

    //////////////////////////////////////////////to_string////////////////////////////////////////
    vector<string>str_mybiset;
    for (int i = 0; i < number_primary_input; i++) {
        str_mybiset.emplace_back();
        to_string(mybitset[i], str_mybiset[i]);
    }
    vector<string>o_str;
    for (int j = 0; j < number_func; j++) {
        o_str.emplace_back();
        to_string(o[j].func_bitcet, o_str[j]);
    }

    //////////////////////////////////////////////to_string////////////////////////////////////////

    //C:/Users/amirh/Desktop/fout.txt
    /////////////////////////////////////////////print in File/////////////////////////////////////
    
    string print_file;
    cout << "\nplease enter the address location   TXT FILE   that you want write it .... ";
    cin >> print_file;
    ofstream fout;
    fout.open(print_file);
    if(!fout) {
        cerr << "file not found ! plz enter again ....\n";
        //cin >> print_file;
        //fout.open(print_file);
        exit(0);
    }
    else {
        cout << "agar name file eshtebah bashad chap nemishavad !!!!!\n";
    }
    //cout << "open succesfully ..." << "\n";
    fout << " your primary inputs is :\n\n";
    fout << "{ ";
    for (int g1 = 0; g1 < number_primary_input - 1; g1++) {
        fout << primary_input[g1] << " , ";
    }
    fout << primary_input[number_primary_input - 1] << " }\n\n";

    fout << " your functions is :\n\n";
    for (int g2 = 0; g2 < number_func; g2++) {
        fout << " ===>  " << o[g2].name_func << " = " << o[g2].func << "\n=================================================\n";
    }
    fout << "\n";


    for (int g3 = 0; g3 < number_func; g3++) {
        fout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n";
        fout << "Truth table for :  " << " [" << o[g3].name_func << " = " << o[g3].func << "]  is : \n\n";
        for (int u1 = 0; u1 < number_primary_input; u1++) {
            fout << primary_input[u1] << "\t";
        }
        fout << o[g3].name_func << "\t";
        fout << "\n";
        for (int u3 = 0; u3 < 8 * (number_primary_input + 1); u3++) {
            fout << "=";
        }
        fout << "\n";
        for (int t1 = 0; t1 < pow(2, number_primary_input); t1++) {
            for (int t2 = 0; t2 < number_primary_input; t2++) {
                fout << str_mybiset[t2][t1] << "\t";
            }
            fout << o_str[g3][t1] << "\t";
            fout << "\n";
        }
    }
    fout.close();
    //////////////////////////////////////print in File/////////////////////////////////////
//C:/Users/amirh/Desktop/fout1.csv


    ///////////////////////////////////////////EXCEL////////////////////////////////////

    ofstream fout1;
    string write_file;
    cout << "please enter the address location   Excel   that you want write it .... ";
    cin >> write_file;
    fout1.open(write_file);
    if (!fout1) {
        cout << "file not found ! plz enter again ....";
        /*cin >> write_file;
        fout1.open(write_file);*/
        exit(0);
    }
    else {
        cout << "agar name file eshtebah bashad chap nemishavad !!!!!\n";
    }
    //cout << "open succesfully ..."<<"\n";
    for (int g3 = 0; g3 < number_func; g3++) {
        fout1 << "\n";
        fout1 << o[g3].name_func << o[g3].func << "\n";
        for (int u1 = 0; u1 < number_primary_input; u1++) {
            fout1 << primary_input[u1] << ",";
        }
        fout1 << o[g3].name_func << ",";
        fout1 << "\n";
        fout1 << "\n";
        for (int t1 = 0; t1 < pow(2, number_primary_input); t1++) {
            for (int t2 = 0; t2 < number_primary_input; t2++) {
                fout1 << str_mybiset[t2][t1] << ",";
            }
            fout1 << o_str[g3][t1] << ",";
            fout1 << "\n";
        }
    }
    fout1.close();

    ///////////////////////////////////////////EXCEL////////////////////////////////////


    /////////////////////////////////////////////graphic/////////////////////////////////////
    cout << "\n\n\n\n";
    ///---------
    cout << " your primary inputs is :\n\n";
    cout << "{ ";
    for (int g1 = 0; g1 < number_primary_input-1; g1++) {
        cout << primary_input[g1] <<" , ";
    }
    cout << primary_input[number_primary_input - 1]<< " }\n\n";
    /////-----------------

    cout<< " your functions is :\n\n";
    for (int g2 = 0; g2 < number_func; g2++) {
        cout <<  " ===>  " << o[g2].name_func << " = " << o[g2].func << "\n컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n";
    }
    string name_function_test; 
    cout << "please choose one of the functions for show Truth Table : ( example : O1 ) .... \n\n";
    cin >> name_function_test;
    cout << "\n";
    for (int g3 = 0; g3 < number_func; g3++) {
        if (name_function_test == o[g3].name_func) {
            for (int u1 = 0; u1 < number_primary_input; u1++) {
                cout << primary_input[u1] << "\t";
            }
            cout << o[g3].name_func << "\t";
            cout << "\n";
            for (int u3 = 0; u3 < 8 * (number_primary_input + 1); u3++) {
                cout << "�";
            }
            cout << "\n";
            for (int t1 = 0; t1 < pow(2, number_primary_input); t1++) {
                for (int t2 = 0; t2 < number_primary_input; t2++) {
                    cout << str_mybiset[t2][t1] << "\t";
                }
                cout << o_str[g3][t1] << "\t";
                cout << "\n";
            }

        }
    }
    /////////////////////////////////////////////graphic/////////////////////////////////////

    
    system("pause>n");
    return 0;
}



