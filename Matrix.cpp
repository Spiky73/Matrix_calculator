//
// Created by Bohdan Zekinskyi on 27.03.2019.
//

#include "Matrix.h"
#include <iostream>

using namespace std;

long get_p(const string& line){
    if(line.empty()) throw invalid_argument("Empty element");
    size_t pos=0;
    pos = line.find("/");
    if(pos < string::npos)
        return stol(line.substr(0, pos+1));
    return stol(line);
}
long get_q(const string& line){
    size_t pos = 0;
    pos = line.find("/");
    if(pos < string::npos)
        return stol(line.substr(pos+1));
    return 1;
}

Matrix::Matrix(int n, int m){ create(n, m);}

void Matrix::create(int n, int m) {
    if(n < 1 || m < 1) throw invalid_argument("Invalid parameters of matrix");
    n_ = n; m_ = m;
    arr_ = v_vec (n_, r_vec(m_));
    //cout<<"Matrix::creator"<<endl;
}
void Matrix::set_zero() noexcept{
    if(n_ < 1 || m_ < 1) return;
    for(auto i = 0; i < n_; i++)
        for(auto j = 0; j < m_; j++)
            arr_[i][j].set(0,0);
}
void Matrix::print() const noexcept{
    for(auto vec : arr_) {
        for(auto x : vec)
            cout << x << " ";
        cout << endl;
    }
}
void Matrix::fill() {
    cout<<"Enter matrix "<<n_<<"x"<<m_<<endl;
    string rational;
    for(auto i = 0; i < n_; i++)
        for(auto j = 0; j < m_; j++) {
            cin >> rational;
            if( cin.fail() ) throw invalid_argument("cin.fail : invalid input data");
            arr_[i][j].set(get_p(rational), get_q(rational));
        }
}

Matrix& Matrix::operator +=(const Matrix& other) {
    if( (n_ != other.n_) || (m_ != other.m_) ) throw invalid_argument("Wrong matrix sizes");
    for(int i=0; i<n_; ++i)
        for(int j=0; j<m_; ++j)
            arr_[i][j] += other.arr_[i][j];
    return *this;
}
Matrix& Matrix::operator *=(const Matrix& other) {
    if( (n_ != other.m_) || (m_ != other.n_) ) throw invalid_argument("Wrong matrix sizes");
    auto* res = new Matrix(n_, other.m_);
    for(int i=0; i<n_; ++i)
        for(int j=0; j<other.m_; ++j)
            for(int k=0; k<m_; ++k)
                res -> arr_[i][j] += (arr_[i][k] * other.arr_[k][j]);
    return *res;
} // don't works

Matrix& operator +(const Matrix& a, const Matrix& b){
    if( (a.n_ != b.n_) || (a.m_ != b.m_) ) throw invalid_argument("Wrong matrix sizes");
    auto* res = new Matrix(a.n_, a.m_);
    for(int i=0; i<a.n_; ++i)
        for(int j=0; j<a.m_; ++j)
            res -> arr_[i][j] = a.arr_[i][j] + b.arr_[i][j];
    return *res;
}
Matrix& operator *(const Matrix& a, const Matrix& b){
    if( (a.n_ != b.m_) || (a.m_ != b.n_) ) throw invalid_argument("Wrong matrix sizes");
    auto* res = new Matrix(a.n_, b.m_);
    for(int i=0; i<a.n_; ++i)
        for(int j=0; j<b.m_; ++j)
            for(int k=0; k<a.m_; ++k)
                res -> arr_[i][j] += (a.arr_[i][k] * b.arr_[k][j]);
    return *res;
}
Matrix& multiply_vector(Matrix& a, const vector<Rational>& vec){
    if( a.m_ != vec.size() ) throw invalid_argument("Wrong matrix sizes");
    auto* res = new Matrix(1, a.m_);
    for(int i = 0; i < a.n_; i++)
        for(int j = 0; j < a.m_; ++j)
            res -> arr_[0][i] += (a.arr_[i][j] * vec[j]);
    return *res;
}
Matrix& multiply_scalar(Matrix& a, const Rational k) noexcept{
    for(int i=0; i<a.n_; i++)
        for(int j=0; j<a.m_; j++)
            a.arr_[i][j] *= k;
    return a;
}
Matrix& transpose(const Matrix& a) noexcept{
    auto* res = new Matrix(a.m_, a.n_);
    for(int i=0; i<a.n_; ++i)
        for(int j=0; j<a.m_; ++j)
            res -> arr_[j][i] = a.arr_[i][j];
    return *res;
}
Matrix to_canonical(Matrix a) noexcept{
    int row = 0, column = 0, row_to_swap = 0, step = 1;
    while( row < a.n_ && column < a.m_){
        if(not_zero(row, column, a) != -1){
            cout<<"\nStep "<<step++<<":\n";
            row_to_swap = not_zero(row, column, a);
            if(row_to_swap != row){
                swap(a.arr_[row_to_swap], a.arr_[row]);
                cout<<"Swap "<<"row["<<row_to_swap<<"] and row["<<row<<"]\n";
            }
            cout<<"Dividing row by pivot["<<row<<"]["<<column<<"]\n";
            row_division(row, column, a);
            cout<<"Substract from all rows pivot_row * coefficient\n";
            row_substraction(row, column, a);
            row++;
            a.print();
        }
        column++;
    }
    cout<<"\nDone!\n";
    return a;
}

int not_zero(int i0, int j0, const Matrix& a) noexcept{
    for(int i = i0; i < a.n_; i++)
        if( double(a.arr_[i][j0]) != 0) return i;
    return -1;
}
void row_division(int i0, int j0, Matrix& a) noexcept{
    for(int j = a.m_ - 1; j >= j0; j--)
        a.arr_[i0][j] = a.arr_[i0][j] / a.arr_[i0][j0]; // a.arr_[i0][j0] always non-zero
}
void row_substraction(int i0, int j0, Matrix& a) noexcept{
    Rational k(0);
    for(int i = 0; i < a.n_; i++){
        if(i == i0) i++;
        if(i < a.n_) {
            k = a.arr_[i][j0];
            for (int j = j0; j < a.m_; j++)
                a.arr_[i][j] += -(a.arr_[i0][j] * k);
        }
    }
}
