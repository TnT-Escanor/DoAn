#include <tuple>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

#ifdef ONLINE_JUDGE
#define DEBUG 0
#else
#define DEBUG 1
#endif
#define debug(a) \
    if (DEBUG)   \
    cout << #a << " = " << (a) << endl
#define x first
#define y second
#define Time ((long long)(clock() * 1000 / CLOCKS_PER_SEC))

void init();
void print(std::vector<int> const &input);
std::string Calculation(int num, int checked, std::string string1);