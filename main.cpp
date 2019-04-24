/****************************

  Matrix calculator (beta 1)

         Created by
      Bohdan Zelinskyi

 ****************************/

#include "Matrix.h"
#include <iostream>
#include <exception>

using namespace std;

void help(){
    cout<<"-add -- adds two matrices and print the result"<<endl;
    cout<<"-multiply -- multiplies matrix by scalar\\vector\\matrix and print the result"<<endl;
    cout<<"-canonical -- leads matrix to canonical form and print the result"<<endl;
    cout<<"-transpose -- transpose matrix and print the result"<<endl;
    cout<<"-stop -- to end the program"<<endl;
}

void add(){
    int i=0, j=0;
    cout<<"Please enter dimensions for added matrices : ";
    cin>>i>>j;
    if( cin.fail() || i<1 || j<1 ) throw invalid_argument("Incorrect sizes");
    Matrix a(i,j), b(i,j);
    cout<<"Please fill first matrix..."<<endl;
    a.fill();
    cout<<"Please fill second matrix..."<<endl;
    b.fill();
    cout<<"Doing calculation ..... ";
    a += b;
    cout<<"done"<<endl<<"Result : "<<endl;
    a.print();
}

void multiply_by_matrix(){
    int i=0, j=0;
    cout<<"Please enter dimensions for multiplied matrices : ";
    cin>>i>>j;
    if( cin.fail() || i<1 || j<1 ) throw invalid_argument("Incorrect sizes");
    Matrix a(i,j), b(j,i);
    cout<<"Please fill first matrix..."<<endl;
    a.fill();
    cout<<"Please fill second matrix..."<<endl;
    b.fill();
    cout<<"Doing calculation ..... ";
    a = a * b;
    cout<<"done"<<endl<<"Result : "<<endl;
    a.print();
}
void multiply_by_vector(){
    int i=0, j=0;
    cout<<"Please enter dimensions for multiplied matrix : ";
    cin>>i>>j;
    if( cin.fail() || i<1 || j<1 ) throw invalid_argument("Incorrect sizes");
    Matrix a(i,j);
    cout<<"Please fill matrix..."<<endl;
    a.fill();
    vector<Rational> vec = vector<Rational>(j);
    string input;
    cout<<"Please enter vector : ";
    for(auto k = 0; k<j; k++) {
        cin>>input;
        if( cin.fail() ) throw invalid_argument("cin.fail");
        vec[k].set( get_p(input), get_q(input));
    }
    cout<<"Doing calculation ..... ";
    a = multiply_vector(a, vec);
    cout<<"done"<<endl<<"Result : "<<endl;
    a.print();
}
void multiply_by_scalar(){
    cout<<"Please enter scalar : ";
    Rational k;
    string scalar;
    cin>>scalar;
    if( cin.fail() ) throw invalid_argument("cin.fail");
    k.set( get_p(scalar), get_q(scalar) );
    int i=0, j=0;
    cout<<"Please enter dimensions for multiplied matrix : ";
    cin>>i>>j;
    if( cin.fail() || i<1 || j<1 ) throw invalid_argument("Incorrect sizes");
    Matrix a(i,j);
    cout<<"Please fill matrix..."<<endl;
    a.fill();
    cout<<"Doing calculation ..... ";
    a = multiply_scalar(a,k);
    cout<<"done"<<endl<<"Result : "<<endl;
    a.print();
}
void multiply(){
    cout<<"On what do you want to multiply the matrix (scalar\\vector\\matrix) : ";
    string input;
    while (cin>>input && input != "scalar" && input != "vector" && input != "matrix")
        cout<<"Sorry, unknown command. Try again"<<endl;
    if(input == "matrix")
        multiply_by_matrix();
    else if(input == "vector")
        multiply_by_vector();
    else if(input == "scalar")
        multiply_by_scalar();
    else return;
}

void transpose(){
    int i=0, j=0;
    cout<<"Please enter dimensions for matrix that being transposed : ";
    cin>>i>>j;
    if( cin.fail() || i<1 || j<1 ) throw invalid_argument("Incorrect sizes");
    Matrix a(i,j);
    cout<<"Please fill matrix..."<<endl;
    a.fill();
    cout<<"Doing calculation ..... ";
    a = transpose(a);
    cout<<"done"<<endl<<"Result : "<<endl;
    a.print();
}

void canonical(){
    int i=0, j=0;
    cout<<"Please enter dimensions for matrix that being leaded to canonical form : ";
    cin>>i>>j;
    if( cin.fail() || i<1 || j<1 ) throw invalid_argument("Incorrect sizes");
    Matrix a(i,j);
    cout<<"Please fill matrix..."<<endl;
    a.fill();
    cout<<"Doing calculation ..... ";
    a = to_canonical(a);
    cout<<endl<<"Result : "<<endl;
    a.print();
}

void copyright(){
    cout<<"****************************\n\n";
    cout<<"  Matrix calculator (beta 1)  \n";
    cout<<"\t\tCreated by\n\tBohdan Zelinskyi\n\n";
    cout<<"****************************\n\n";
    cout<<"Please enter the command (enter -help to see the command list)\n";
}

int main() {
    copyright();
    string input_command;
    while (cin>>input_command && input_command != "-stop") {
        try {
            if(input_command == "-help" || input_command == "help") help();
            else if(input_command == "-add" || input_command == "add") add();
            else if(input_command == "-multiply" || input_command == "multiply") multiply();
            else if(input_command == "-canonical" || input_command == "canonical") canonical();
            else if(input_command == "-transpose" || input_command == "transpose") transpose();
            else cout<<"Sorry, unknown command. Try again"<<endl;
        }
        catch (invalid_argument &ex) { cout << "Invalid argument : " << ex.what() << endl; }
        catch (out_of_range &ex) { cout << "Out of range : " << ex.what() << endl; }
        catch (...) { cout << "Smth bad happend..." << endl; }
        cout<<"Waiting for command..."<<endl;
    }
    return 0;
}