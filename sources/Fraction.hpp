#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel {
    
    class Fraction {
    private:
        int numerator;
        int denomirator;
    public:
        //Constructors
        Fraction();
        Fraction(int numerator, int denomirator);
        Fraction(float fractNum);

        //Getters
        int getNumerator() const  
        {
            // std::cout << this->numerator << std::endl;
            return this->numerator;
        }

        int getDenominator() const
        {
            // std::cout<< this->denomirator << std::endl;
            return this->denomirator;
        }

        //Setters
        void setNumerator(int numerator);
        void setDenomirator(int denomirator);

        //Operators
        const Fraction operator+(const float& fractNum)const;
        const Fraction operator+(const Fraction& other)const;
        friend const Fraction operator+(const float& fractNum, const Fraction& other);

        Fraction operator-(const Fraction& other)const;
        Fraction operator-(float fractNum) const;
        friend Fraction operator-(float fractNum, const Fraction& other);

        Fraction operator*(const Fraction& other)const;
        Fraction operator*(float fractNum)const;
        const friend Fraction operator*(float fractNum, const Fraction& other);

        const Fraction operator/(const Fraction& other)const;
        const Fraction operator/(float fractNum)const;
        const friend Fraction operator/(float fractNum, const Fraction& other);

        const bool operator<(const Fraction& other)const;
        const bool operator<(float fractNum)const;
        const friend bool operator<(float fractNum, const Fraction& other);

        const bool operator>(const Fraction& other)const;
        const bool operator>(float fractNum)const;
        const friend bool operator>(float fractNum, const Fraction& other);

        const friend bool operator==(const Fraction& left, const Fraction& right);
        const friend bool operator==(const Fraction& left ,float fractNum);
        const friend bool operator==(float fractNum, const Fraction& right);

        const bool operator<=(const Fraction& other) const;
        const bool operator<=(float fractNum) const;
        const friend bool operator <=(float fractNum, const Fraction& other);

        const bool operator>=(const Fraction& other) const;
        const bool operator>=(float fractNum) const;
        const friend bool operator>=(float fractNum, const Fraction& other);

        //prefix
        Fraction& operator++();
        Fraction& operator--();
        //postfix
        Fraction operator++(int);
        Fraction operator--(int);
        friend std::ostream& operator<<(std::ostream& output, const Fraction& fraction);
        friend std::istream& operator>>(std::istream& input, Fraction& fraction);

        //Methods
        int gcdFoo(int num1, int num2);
    };
};
#endif
