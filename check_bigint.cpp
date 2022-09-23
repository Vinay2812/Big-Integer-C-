#include <bits/stdc++.h>
#include "BigInteger.h"

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    BigInteger a, b, c = "1";
    a = "60";
    b = "80";

   cout<<a.gcd(b);
    return 0;
}