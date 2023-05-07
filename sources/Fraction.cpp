#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Fraction.hpp"


namespace ariel{
    Fraction :: Fraction(){
        this->numerator = 1;
        this->denomirator = 1;
        // cout << this->numerator << endl;
        // cout << this->denomirator << endl;
    }
    Fraction :: Fraction(int numerator, int denomirator)
    {
        if (denomirator == 0)
        {
            throw std :: invalid_argument("Division by zero is not defined\n");
        }

        int greatestCommonDivisor = gcdFoo(numerator, denomirator);

        this->numerator = numerator/greatestCommonDivisor;
        this->denomirator = denomirator/greatestCommonDivisor;
        if ((this->denomirator < 0) && (this->numerator > 0)) {
            this->denomirator *= -1;
            this->numerator *= -1;
        }
    }

    Fraction :: Fraction(float fractNum)

    {   int max = 1000;
        fractNum *= max;
        int gcd = gcdFoo((int) fractNum, max);
        Fraction fract = Fraction(fractNum / gcd, max / gcd);

        this->numerator = fract.getNumerator();
        this->denomirator = fract.getDenominator();
        // cout << this->numerator << endl;
        // cout << this->denomirator << endl;
    }

    void Fraction::setNumerator(int numerator)
    {
        this->numerator = numerator;
    }

    void Fraction::setDenomirator(int denomirator)
    {
        if (denomirator == 0){
            throw std :: invalid_argument ("Division by zero is not defined\n");
        }
        this->denomirator = denomirator;
    }

    const Fraction Fraction::operator+(const Fraction& other)const{

        long long newNuminator = (long long) (this->numerator * other.denomirator) + (other.numerator * this->denomirator);
        long long newDenominator = (long long) this->denomirator * other.denomirator;
        if ((newNuminator < std::numeric_limits<int>::min()) || (newNuminator > std::numeric_limits<int>::max()) || ((newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min()))) {
            throw std::overflow_error("Overflow!");
        }
        return Fraction(newNuminator,newDenominator);
    }
    
    const Fraction Fraction::operator+(const float& fractNum)const{
        return Fraction(fractNum) + (*this);
    }

    const Fraction operator+(const float& fractNum,const Fraction& other){
        Fraction fract(fractNum);
        int newNuminator = (fract.getNumerator() * other.getDenominator()) + (other.getNumerator() * fract.getDenominator());
        int newDenominator = fract.getDenominator() * other.getDenominator();
        return Fraction(newNuminator,newDenominator);
    }

    Fraction Fraction::operator-(const Fraction& other)const{
        long long newNuminator = (long long)(this->numerator * other.getDenominator()) - (other.getNumerator() * this->denomirator);
        long long newDenominator = (long long)(this->denomirator * other.getDenominator());

        long long greatestCommonDivisor = __gcd(numerator, denomirator);

        newNuminator = newNuminator/greatestCommonDivisor;
        newDenominator = newDenominator/greatestCommonDivisor;

        if (newNuminator > std::numeric_limits<int>::max() || newNuminator < std::numeric_limits<int>::min() || newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Overflow!");
        }

        int num = (this->numerator * other.getDenominator()) - (other.getNumerator() * this->denomirator);
        int den = (this->denomirator * other.getDenominator());
        return Fraction(num, den);

    }

    Fraction Fraction::operator-(float fractNum)const{
        Fraction result(fractNum);
        return *this - result;
    }

    Fraction operator-(float fractNum, const Fraction& other){
        Fraction fract(fractNum);
        int newNuminator = (fract.getNumerator() * other.getDenominator()) - (other.getNumerator() * fract.getDenominator());
        int newDenominator = fract.getDenominator() * other.getDenominator();
        return Fraction(newNuminator,newDenominator);
    }

    Fraction Fraction::operator*(const Fraction& other)const {

        long long newNuminator = (long long)this->numerator * other.getNumerator();
        long long newDenominator = (long long)this->denomirator * other.getDenominator();
        if ((newNuminator < std::numeric_limits<int>::min()) || (newNuminator > std::numeric_limits<int>::max()) || ((newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min()))) {
            throw std::overflow_error("Overflow!");
        }

        return Fraction(newNuminator,newDenominator);
    }

    Fraction Fraction::operator*(float fractNum)const{
        Fraction result(fractNum);
        return (*this) * result;
    }

    const Fraction operator*(float fractNum, const Fraction &other){
       Fraction result(fractNum);
       return result * (other);
    }

    const Fraction Fraction::operator/(const Fraction& other)const{
        if (other.getNumerator() == 0){
            throw std::overflow_error("division by zero is not defined");
        }
        long long newNuminator = (long long)this->numerator * other.getDenominator();
        long long newDenominator = (long long)this->denomirator * other.getNumerator();
        if ((newNuminator < std::numeric_limits<int>::min()) || (newNuminator > std::numeric_limits<int>::max()) || ((newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min()))) {
            throw std::overflow_error("Overflow!");
        }
        return Fraction(newNuminator,newDenominator);
    }

    const Fraction Fraction::operator/(float fractNum)const{
        if (fractNum == 0){
            throw std::overflow_error("division by zero is not defined");
        }
        Fraction origin = *this;
        Fraction res(fractNum);
        return origin / res;
    }

    const Fraction operator/(float fractNum, const Fraction &other){
        if (other.getDenominator() == 0){
            throw std::overflow_error("division by zero is not defined");
        }

        Fraction result(fractNum);
        return result/other;
    }


    const bool Fraction::operator<(const Fraction& other) const {
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return thisValue < otherValue;    
    }

    const bool Fraction::operator<(float fractNum) const{
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        return thisValue < fractNum;
    }
    const bool operator<(float fractNum, const Fraction& other){
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return fractNum < otherValue;
    }

    const bool Fraction::operator>(const Fraction& other) const {
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return thisValue > otherValue;
    }

    const bool Fraction::operator>(float fractNum)const{
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        return thisValue > fractNum;
    }

    const bool operator>(float fractNum, const Fraction& other){
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return fractNum > otherValue;
    }

    const bool operator==(const Fraction& left, const Fraction& right){
        float leftValue = (static_cast<float>(left.getNumerator()) / static_cast<float>(left.getDenominator()));
        float rightValue = (static_cast<float>(right.getNumerator()) / static_cast<float>(right.getDenominator()));
        return leftValue == rightValue;
    }
    const bool operator==(const Fraction& left, float fractNum){
        float leftValue = (static_cast<float>(left.getNumerator()) / static_cast<float>(left.getDenominator()));
        return leftValue == fractNum;
    }
    const bool operator==(float fractNum, const Fraction& right){
        float rightValue = (static_cast<float>(right.getNumerator()) / static_cast<float>(right.getDenominator()));
        return fractNum == rightValue;
    }
        
    const bool Fraction::operator<=(const Fraction& other) const {
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return thisValue <= otherValue;
    }

    const bool Fraction::operator<=(float fractNum)const{
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        return thisValue <= fractNum;
    }

    const bool operator<=(float fractNum, const Fraction& other){
        Fraction res(fractNum);
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return fractNum <= otherValue;
    }

    const bool Fraction::operator>=(const Fraction& other) const {
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return thisValue >= otherValue;    }

    const bool Fraction::operator>=(float fractNum)const{
        float thisValue = static_cast<float>(this->numerator) / (this->denomirator);
        return thisValue >= fractNum;
    }

    const bool operator>=(float fractNum, const Fraction& other){
        float otherValue = static_cast<float>(other.getNumerator()) / (other.getDenominator());
        return fractNum >= otherValue;
    }


    //prefix
    Fraction& Fraction::operator++(){
        this->setNumerator(this->getNumerator() + this->getDenominator());
        return *this;
    }

    //postfix
    Fraction Fraction::operator++(int) {
        Fraction a = *this;
        this->setNumerator(this->getNumerator() + this->getDenominator());
        return a;
    }

    //prefix
    Fraction& Fraction::operator--(){
        this->setNumerator(this->getNumerator() - this->getDenominator());
        return *this;
    }

    //postfix
    Fraction Fraction::operator--(int) {
        Fraction a = *this;
        this->setNumerator(this->getNumerator() - this->getDenominator());
        return a;
    }


    std::ostream& operator<<(std::ostream& output, const Fraction& fraction)
    {
        output << fraction.getNumerator() << "/" << fraction.getDenominator();
        return output;
    }

    std::istream& operator>>(std::istream& input, Fraction& fraction)
    {
        int numerator, denomirator;
        if (!((input) >> numerator >> denomirator)) {throw runtime_error("Invalid input for Fraction");}
        if (denomirator == 0) throw runtime_error("Division by zero is undefined!");

        fraction = Fraction(numerator, denomirator);
        return input;
    }
    int Fraction::gcdFoo(int a, int b)
    {
        if (b == 0)
        {
            return a;
        }
        else
        {
            return gcdFoo(b, a % b);
        }
    }
}
