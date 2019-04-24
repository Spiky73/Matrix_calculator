//
// Created by T.Karnaukh
// Changes made by B.Zelinskyi
//

#ifndef RATIONAL_MATRIX_CALC_RATIONAL_H
#define RATIONAL_MATRIX_CALC_RATIONAL_H

#pragma once
#include <string>

class Rational{
public:
    explicit Rational(long p0=0,long q0=1);

    bool isNumber() const; //validness
    bool isZero() const;
    bool isInteger() const;

    void write()const;
    void set(long p0 = 0, long q0 = 1);

    explicit operator std::string() const;

    bool operator ==(const Rational&) const;// both NaNs or both valid and equal
    bool operator !=(const Rational&) const;// not ==
    bool operator <(const Rational&) const;//both numbers and <
    bool operator <=(const Rational&) const;//both numbers and <=
    bool operator >(const Rational&) const;//both numbers and >
    bool operator >=(const Rational&) const;//both numbers and >=

    Rational& operator -(); // inverse the value
    Rational operator +(const Rational&) const;// if some arg is NaN the result is NaN
    //friend Rational operator +(const Rational& ,const Rational&);
    Rational operator -(const Rational&) const;
    Rational operator *(const Rational&) const;
    Rational operator /(const Rational&) const;// result is NaN in case division by 0
    Rational& operator +=(const Rational&);
    Rational& operator /=(const Rational&);
    Rational& operator *=(const Rational&);

    friend std::ostream& operator<<(std::ostream& os, const Rational& other);

    explicit operator bool() const;// true iff number and not zero
    explicit operator long() const; // zero for NaN
    explicit operator double() const;// quiet_NaN if NaN

    static Rational getNaN();

private:
    long p, q; //for valid rational q>0; for zero q=1; for NaN p=q=0
    void normalize();

    double compare(const Rational& other) const;//for numbers; negative if <, positive if >
    bool computable(const Rational& other)const;// true iff arithmetic operations is computable
};
//Rational operator +(const Rational& ,const Rational&);

//long GCD(long,long); //0 if both is zero; GCD of absolute values; result >=0

#endif //RATIONAL_MATRIX_CALC_RATIONAL_H
