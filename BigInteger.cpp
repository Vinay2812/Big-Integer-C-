#include <bits/stdc++.h>
using namespace std;

class BigInteger
{
    string number;

public:
    BigInteger &operator=(const BigInteger &other)
    {
        if (this != &other)
        {
            this->number = other.number;
        }
        return *this;
    }
    BigInteger &operator=(string &other)
    {
        if (this->number != other)
        {
            this->number = other;
        }
        return *this;
    }
    int size()
    {
        return number.size();
    }
    bool operator==(BigInteger &other)
    {
        if ((*this).size() != other.size())
            return false;

        for (int i = 0; i < other.size(); i++)
        {
            if ((*this).number[i] != other.number[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator<(BigInteger &other)
    {
        if ((*this).size() > other.size())
            return false;

        for (int i = 0; i < min((*this).size(), other.size()); i++)
        {
            if ((*this).number[i] > other.number[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator>(BigInteger &other)
    {
        if ((*this).size() < other.size())
            return false;

        for (int i = 0; i < min((*this).size(), other.size()); i++)
        {
            if ((*this).number[i] < other.number[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator<=(BigInteger &other)
    {
        if (*this == other || *this < other)
            return true;

        return false;
    }
    bool operator>=(BigInteger &other)
    {
        if (*this == other || *this > other)
            return true;

        return false;
    }

    BigInteger operator+(BigInteger other)
    {
        string ans;
        string a = this->number;
        string b = other.number;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int n1 = a.size();
        int n2 = b.size();
        if (n1 < n2)
        {
            while (n1 < n2)
            {
                a.push_back('0');
                n1++;
            }
        }
        else if (n1 > n2)
        {
            while (n1 > n2)
            {
                b.push_back('0');
                n2++;
            }
        }
        int carry = 0;
        int sum;
        for (int i = 0; i < n1; i++)
        {
            sum = int(a[i] - '0') + int(b[i] - '0') + carry;
            carry = (sum / 10);
            ans.push_back(((sum % 10) + '0'));
        }
        if (carry)
            ans.push_back(carry + '0');

        reverse(ans.begin(), ans.end());
        BigInteger res(ans);
        return res;
    }

    void swap(BigInteger &a, BigInteger &b)
    {
        BigInteger temp = a;
        a = b;
        b = temp;
    }
    // BigInteger operator-(BigInteger other)
    // {
    // }
    BigInteger operator*(BigInteger other)
    {
        string a = this->number;
        string b = other.number;
        string no_of_zeros = "";
        cout << a << " " << b << endl;

        vector<BigInteger> all_nums;

        for (int i = b.size() - 1; i >= 0; i--)
        {
            int num1 = (b[i] - '0');
            int carry = 0;
            string mul_ans = "";
            string zeros = "";
            for (int j = a.size() - 1; j >= 0; j--)
            {
                int num2 = (a[j] - '0');
                int mul = num1 * num2 + carry;
                mul_ans.push_back(char((mul % 10 + '0')));
                carry = mul / 10;
            }
            if (carry)
            {
                mul_ans.push_back(char(carry + '0'));
            }
            int flag = 0;
            for (char c : mul_ans)
            {
                if (c != '0')
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                mul_ans = "0";
            }
            reverse(mul_ans.begin(), mul_ans.end());
            if (mul_ans[0] != '0')
            {
                mul_ans += no_of_zeros;
            }
            no_of_zeros.push_back('0');
            BigInteger b(mul_ans);
            all_nums.push_back(b);
        }
        BigInteger final_ans;
        for (BigInteger b : all_nums)
        {
            final_ans = final_ans + b;
        }
        return final_ans;
    }

    BigInteger operator/(BigInteger other)
    {
        BigInteger i;
        BigInteger one;
        BigInteger ans;
        BigInteger multiply;
        ans = "0";
        i = "1";
        one = "1";
        while (true)
        {
            ans = i;
            cout << i << endl;
            multiply = (i * other);
            if (multiply > *this)
                return ans;
            i = i + one;
        }
        return ans;
    }

    friend ostream &operator<<(ostream &out, const BigInteger &other)
    {
        if (other.number == "")
        {
            out << "0";
        }
        else
        {
            out << other.number;
        }
        return out;
    }
    friend istream &operator>>(istream &in, BigInteger &other)
    {
        in >> other.number;
        return in;
    }
    BigInteger(const char *num)
    {
        string a = "";
        int i = 0;
        while (num[i] != '\0')
        {
            a.push_back(char(num[i++]));
        }
        this->number = a;
    }
    BigInteger(const string num)
    {
        this->number = num;
    }
    BigInteger()
    {
        this->number = "";
    }
};

int main()
{
    BigInteger a, b, c = "100", d = "300";
    a = "1234";
    b = "200";

    // cout << a << " " << b << " " << c << " " << d << endl;
    cout << a * b + c;
    return 0;
}