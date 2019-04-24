//
// Created by Bohdan Zelinskyi on 27.03.2019.
//

#ifndef MATRIX_BY_TEMPLATES_MATRIX_H
#define MATRIX_BY_TEMPLATES_MATRIX_H

#pragma once

#include "Rational.h"
#include <vector>

using r_vec = std::vector<Rational>;
using v_vec = std::vector<r_vec>;

class Matrix{
public:
    explicit Matrix(int n=1, int m=1);

    void set_zero() noexcept;
    void print() const noexcept;

    // throw std::invalid_argument if cin.fail or if convertation string - long can't be performed
    // throw std::out_of_range if the converted value goes outside the range of the type values
    void fill();

    // basic matrix operations
    Matrix& operator +=(const Matrix&); // throw std::invalid_argument if the sizes of added matrices are not equal
    Matrix& operator *=(const Matrix&); // throw std::invalid_argument if the sizes of multiplying matrices aren't suitable

    friend Matrix& operator +(const Matrix&, const Matrix&); // throw std::invalid_argument if the sizes of added matrices are not equal
    friend Matrix& operator *(const Matrix&, const Matrix&); // throw std::invalid_argument if the sizes of multiplying matrices aren't suitable
    friend Matrix& multiply_vector(Matrix&, const std::vector<Rational>&);
    friend Matrix& multiply_scalar(Matrix&, const Rational) noexcept;
    friend Matrix& transpose(const Matrix&) noexcept;
    friend Matrix to_canonical(Matrix) noexcept;


    // functions for the correct work of to_canonical
    friend int not_zero(int i, int j, const Matrix&) noexcept;
    friend void row_division(int i, int j, Matrix&) noexcept;
    friend void row_substraction(int i, int j, Matrix&) noexcept;

protected:
    unsigned int n_;
    unsigned int m_;
    v_vec arr_;

    // throw std::invalid_argument if at least one parameter of Matrix < 1
    void create(int n, int m);
};

// throw std::invalid_argument if convertation string - long can't be performed
// throw std::out_of_range if the converted value goes outside the range of the type values
long get_p(const std::string& );
long get_q(const std::string& );

#endif //MATRIX_BY_TEMPLATES_MATRIX_H
