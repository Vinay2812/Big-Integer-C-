#include <bits/stdc++.h>
using namespace std;

class StringArithmeticOperations{
    int digit(char a){return (a-'0');}
    bool isPositive(string a){
        return (a[0] != '-');
    }
protected:
    void trim(string& a){
        int i = 0;
        string sign;
        if(a[i] == '-'){
            sign = "-";
            i++;
        }

        while(a[i] == '0')i++;
        if(i == 0)return;
        if(i == a.size()){
            a = "0";
            return;
        }
        if(sign.size())a = sign + a.substr(i, a.size() - i);
        else a = a.substr(i, a.size() - i);
    }
    bool isEqual(string a, string b){
        if(a.size() != b.size())return false;
        int n = a.size();
        for(int i=0;i<n;i++){
            if(a[i] != b[i])return false;
        }
        return true;
    }
    bool notEqual(string a, string b){
        return !isEqual(a, b);
    }
    bool lessThan(string a, string b){
        bool apos = isPositive(a);
        bool bpos = isPositive(b);
        if(apos and !bpos)return false;
        if(!apos and bpos)return true;
        bool rev = false;
        if(!apos and !bpos){
            rev = true;
        }
        if(a.size() < b.size())return (rev)?0:1;
        if(a.size() > b.size())return (rev)?1:0;
        int n = a.size();
        for(int i=0;i<n;i++){
            if(a[i] < b[i])return (rev)?0:1;
            if(a[i] > b[i])return (rev)?1:0;
        }
        return false;
    }
    bool lessThanEqual(string a, string b){
        bool apos = isPositive(a);
        bool bpos = isPositive(b);
        if(apos and !bpos)return false;
        if(!apos and bpos)return true;
        bool rev = false;
        if(!apos and !bpos){
            rev = true;
        }
        if(a.size() < b.size())return (rev)?0:1;
        if(a.size() > b.size())return (rev)?1:0;
        int n = a.size();
        for(int i=0;i<n;i++){
            if(a[i] < b[i])return (rev)?0:1;
            if(a[i] > b[i])return (rev)?1:0;
        }
        return true;
    }
    bool greaterThan(string a, string b){
        return !lessThanEqual(a, b);
    }
    bool greaterThanEqual(string a, string b){
        return !lessThan(a, b);
    }
    
    string add(string a, string b){
        int n1 = a.size();
        int n2 = b.size();

        if(n1 < n2)return add(b, a);
        if(n2 == 0)return a;

        bool apos = isPositive(a);
        bool bpos = isPositive(b);

        if(apos and !bpos){
            return subtract(a, b.substr(1));
        }
        else if(!apos and bpos){
            return subtract(b, a.substr(1));
        }
        else if(!apos and !bpos){
            return "-" + add(a.substr(1), b.substr(1));
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        string ans;

        int carry = 0;
        for(int i=0;i<n1;i++){
            int sum = digit(a[i]) + ((i>=n2)?0:digit(b[i])) + carry;
            ans.push_back(sum%10 + '0');
            carry = sum/10;
        }
        if(carry)ans.push_back(carry+'0');
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string multiply(string a, string b){
        if(a.size() == 0 || b.size() == 0 || a == "0" || b == "0"){
            return "0";
        }
        int sign = 1;
        if(a[0] == '-'){
            sign *= -1;
            a = a.substr(1);
        }
        if(b[0] == '-'){
            sign *= -1;
            b = b.substr(1);
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        
        int N = a.size() + b.size();
        string answer(N, '0');
        
        for(int j=0;j<b.size();j++){
            int digit2 = digit(b[j]);
            for(int i=0;i<a.size();i++){
                int digit1 = digit(a[i]);
                int numZeros = i+j;
                int carry = answer[numZeros] - '0';

                int multiply = digit1 * digit2 + carry;
                
                answer[numZeros] = multiply%10 + '0';
                answer[numZeros+1] += multiply/10 ;
            }
        }
        if(answer.back() == '0')answer.pop_back();
        reverse(answer.begin(), answer.end());
        if(answer[0] == 0)return "0";
        if(sign == -1)return ("-"+answer);
        return answer;
    }

    string subtract(string a, string b){
        if(isEqual(a, b))return "0";
        bool apos = isPositive(a);
        bool bpos = isPositive(b);

        if(apos and !bpos){
            return add(a, b.substr(1));
        }
        if(!apos and bpos){
            return "-"+add(a.substr(1), b);
        }
        if(!apos and !bpos){
            return subtract(b.substr(1), a.substr(1));
        }
        if(lessThan(a, b)){
            return "-"+subtract(b, a);
        }
        string ans;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        int n1 = a.size(), n2 = b.size();
        int borrow = 0;
        for(int i=0;i<n1;i++){
            int dig1 = digit(a[i]);
            int dig2 = (i>=n2)?0:digit(b[i]);

            int sub = dig1 - dig2 - borrow;

            if(sub < 0){
                sub += 10;
                borrow = 1;
            }
            else{
                borrow = 0;
            }
            ans.push_back(sub+'0');
        }
        reverse(ans.begin(), ans.end());
        trim(ans);
        return ans;

    }

    string divideBy2(string a){
        string ans;
        int rem = 0;
        for(char c : a){
            int dig = rem*10 + digit(c);
            if(dig < 2){
                ans.push_back('0');
                rem = dig;
            }
            else{
                ans.push_back(dig/2 + '0');
                rem = dig%2;
            }
        }
        trim(ans);
        return ans;
    }

    string divide(string a, string b){
        int sign = 1;
        if(a[0] == '-'){
            sign *= -1;
            a = a.substr(1);
        }
        if(b[0] == '-'){
            sign *= -1;
            b = b.substr(1);
        }

        string l = "0", h = multiply(a, b);
        string ans = "0";

        while(lessThanEqual(l, h)){
            string mid = divideBy2(add(l, h));
            string mult = multiply(b, mid);
            // cout<<mult<<" "<<mid<<" "<<b<<endl;
            if(lessThanEqual(mult, a)){
                ans = mid;
                l = add(mid, "1");
            }
            else{
                h = subtract(mid, "1");
            }
        }
        if(ans[0] == '0')return "0";
        if(sign == -1)return "-"+ans;
        return ans;
    }

    string modulo(string a, string b){
        string div = divide(a, b);
        string rem = subtract(a , multiply(b, div));
        return rem;
    }

    string power(string x, string n){
        if(isEqual(x, "0"))return "0";
        if(isEqual(n, "0"))return "1";
        if(isEqual(n, "1"))return x;

        long long N = stoll(n);
        string ans = "1";
        for(long long i=1;i<=N;i++){
            ans = multiply(ans, x);
        }
        return ans;
    }

    string gcd(string a, string b){
        if(isEqual(b, "0"))return a;
        return gcd(b, modulo(a, b));
    }
};

class BigInteger : protected StringArithmeticOperations
{
    string number;
public:
    BigInteger(){
        this->number = "0";
    }
    BigInteger(const char *num){
        string a = "";
        int i = 0;
        while (num[i] != '\0')a.push_back(char(num[i++]));
        trim(a);
        this->number = a;
    }
    BigInteger(string num){
        trim(num);
        this->number = num;
    }
    
    friend ostream &operator<<(ostream &out, const BigInteger &other){
        if (other.number == "")
            out << "0";
        else
            out << other.number;
        return out;
    }
    friend istream &operator>>(istream &in, BigInteger &other){
        in >> other.number;
        other.trim(other.number);
        return in;
    }
    
    BigInteger &operator=(const BigInteger &other){
        this->number = other.number;
        return *this;
    }
    BigInteger &operator=(string &other){
        this->number = other;
        return *this;
    }
    
    bool operator==(BigInteger &other){
        return isEqual(this->number, other.number);
    }
    bool operator!=(BigInteger &other){
        return notEqual(this->number, other.number);
    }
    bool operator<(BigInteger &other){
        return lessThan(this->number, other.number);
    }
    bool operator>(BigInteger &other){
        return greaterThan(this->number, other.number);
    }
    bool operator<=(BigInteger &other){
        return lessThanEqual(this->number, other.number);
    }
    bool operator>=(BigInteger &other){
        return greaterThanEqual(this->number, other.number);
    }

    BigInteger operator+(BigInteger other){
        string ans = add(this->number, other.number);
        BigInteger res(ans);
        return res;
    }
    BigInteger operator-(BigInteger other){
        string ans = subtract(this->number, other.number);
        BigInteger res(ans);
        return res;
    }
    BigInteger operator*(BigInteger other){
        string answer = multiply(this->number, other.number);
        BigInteger final_ans(answer);
        return final_ans;
    }
    BigInteger operator/(BigInteger other){
        string answer = divide(this->number, other.number);
        BigInteger final_ans(answer);
        return final_ans;
    }
    BigInteger operator%(BigInteger other){
        string answer = modulo(this->number, other.number);
        BigInteger final_ans(answer);
        return final_ans;
    }
    void operator+=(BigInteger other){
        this->number = add(this->number, other.number);
    }
    void operator*=(BigInteger other){
        this->number = multiply(this->number, other.number);
    }
    void operator-=(BigInteger other){
        this->number = subtract(this->number, other.number);
    }
    void operator/=(BigInteger other){
        this->number = divide(this->number, other.number);
    }
    void operator%=(BigInteger other){
        this->number = modulo(this->number, other.number);
    }
    BigInteger operator++(){
        return this->number = add(this->number, "1");
    }
    BigInteger operator--(){
        return this->number = subtract(this->number, "1");
    }
    BigInteger operator++(int){
        BigInteger temp = this->number;
        this->number = add(this->number, "1");
        return temp;
    }
    BigInteger operator--(int){
        BigInteger temp = this->number;
        this->number = subtract(this->number, "1");
        return temp;
    }

    int size(){
        return (int)number.size();
    } 
    void swap(BigInteger &a){
        BigInteger temp = *this;
        *this = a;
        a = temp;
    }
    BigInteger power(BigInteger a){
        BigInteger ans(StringArithmeticOperations::power(this->number, a.number));
        return ans;
    }  
    BigInteger gcd(BigInteger a){
        return StringArithmeticOperations::gcd(this->number, a.number);
    }
};


