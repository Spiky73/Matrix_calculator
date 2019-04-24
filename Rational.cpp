//
// Created by T.Karnaukh
// Changes made by B.Zelinskyi
//

#include "Rational.h"
#include <iostream>
#include <limits>
#include <numeric>

using namespace std;

Rational::Rational(long p0,long q0):p(p0), q(q0){
    if (q==0) {p=0; return;}
    normalize();
}
void Rational::normalize(){
    if (p==0) {q = 1; return;}
    if (q<0) {q = -q; p = -p;}
    long gcdiv = gcd(p,q);
    p /= gcdiv;
    q /= gcdiv;
}
void Rational::write()const{
    cout<<operator string();
}
void Rational::set(long p0, long q0) {
    if(q==0) {p=0; return;}
    p = p0; q = q0;
    normalize();
}
bool Rational::isNumber() const{return q!=0;}
bool Rational::operator ==(const Rational& other) const{
    return p==other.p && q==other.q;
}
bool Rational::isZero() const {return isNumber() && p==0;}
bool Rational::isInteger() const{return isNumber() && q==1;}
bool Rational::computable(const Rational& other)const{ return isNumber() && other.isNumber();}

double Rational::compare(const Rational& other) const{return double(p)*other.q-double(q)*other.p;}

bool Rational::operator !=(const Rational& other) const{return !operator==(other);}
bool Rational::operator <(const Rational& other) const {return computable(other) && compare(other)<0;}
bool Rational::operator <=(const Rational& other) const{return computable(other) && compare(other)<=0;}
bool Rational::operator >(const Rational& other) const{return computable(other) && compare(other)>0;}
bool Rational::operator >=(const Rational& other) const{return computable(other) && compare(other)>=0;}
ostream& operator<<(ostream& os, const Rational& other) { os << string(other); return os; }

Rational Rational::getNaN() {return Rational(0,0);}
Rational& Rational::operator -() {
    p=-p;
    return *this;
}

Rational Rational::operator +(const Rational& other) const{
    if (!computable(other)) return getNaN();
    return Rational (p*other.q+ q*other.p, q*other.q);
}
Rational Rational::operator -(const Rational& other) const{
    if (!computable(other)) return getNaN();
    return Rational (p*other.q- q*other.p, q*other.q);
}
Rational Rational::operator *(const Rational& other) const{
    if (!computable(other)) return getNaN();
    return Rational (p*other.p, q*other.q);
}
Rational Rational::operator /(const Rational& other) const{
    if (!computable(other) || other.isZero()) return getNaN();
    return Rational (p*other.q, q*other.p);
}
Rational& Rational::operator+=(const Rational &other){
    if (!computable(other)) return *this;
    p = p*other.q+ q*other.p;
    q = q*other.q;
    normalize();
    return *this;
}
Rational& Rational::operator/=(const Rational& other) {
    if (!computable(other) || other.isZero()) return *this;
    p *= other.q;
    q *= other.p;
    normalize();
    return *this;
}
Rational& Rational::operator*=(const Rational& other) {
    if (!computable(other)) return *this;
    p *= other.p;
    q *= other.q;
    normalize();
    return *this;
}
Rational::operator bool() const{return isNumber() && !isZero();}
Rational::operator long() const{
    if (!isNumber()) return 0;
    if (q==1) return p;
    return long(double(p)/q);
}
Rational::operator double() const {
    if (!isNumber()) return numeric_limits<double>::quiet_NaN();
    return double(p)/q;
}
Rational::operator std::string() const{
    if (!isNumber()) return string("_ERROR_");
    string s=to_string(p);
    if (isInteger()) return s;
    return s+"/"+to_string(q);
}

// this version uses standart function gcd from numeric lib
// another two possible options to find GCD

/* void divAll2(long &a){while ((a&1)==0) a>>=1;}
long GCD(long a,long b){
    if (a==0) return b;
    if (b==0) return a;
    if (a<0) a=-a;
    if (b<0) b=-b;
    long gcd=1;
    while (!(a&1) && !(b&1)) {gcd<<=1;a>>=1;b>>=1;}
    while (a && b) {
        divAll2(a);
        divAll2(b);
        if (a>=b) a-=b; else b-=a;
    }
    gcd*=(a+b);
    return gcd;
}*/

/*long GCD(long a, long b){
    for(;;){
        a %= b;
        if(!a)
            return b;
        b %= a;
        if(!b)
            return a;
    }
}*/
