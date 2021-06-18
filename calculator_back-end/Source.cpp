#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "Source.h"
using namespace std;
#define all(a) a.begin(), a.end()
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
#define N 300000
template <typename T>
ostream &operator<<(ostream &os, vector<T> a)
{
    os << "( ";
    for (T &x : a)
        os << x << " ";
    os << ")" << endl;
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, set<T> a)
{
    os << "( ";
    for (T x : a)
        os << x << " ";
    os << ")" << endl;
    return os;
}
template <typename X, typename Y>
ostream &operator<<(ostream &os, pair<X, Y> a)
{
    os << "(" << a.first << " " << a.second << ") ";
    os.flush();
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, complex<T> a)
{
    os << "(r=" << a.real() << " i=" << a.imag() << ") ";
    os.flush();
    return os;
}
template <typename X, typename Y>
pair<X, Y> &operator-=(pair<X, Y> &A, pair<X, Y> B)
{
    A.x -= B.x;
    A.y -= B.y;
    return A;
}
template <typename X, typename Y>
pair<X, Y> &operator+=(pair<X, Y> &A, pair<X, Y> B)
{
    A.x += B.x;
    A.y += B.y;
    return A;
}
//template<typename X,typename Y,typename Z>pair<X,Y>&operator*=(pair<X,Y>&A,Z n){A.x*=n;A.y*=n;return A;}
template <typename X, typename Y>
X operator*(pair<X, Y> A, pair<X, Y> B) { return A.x * B.x + A.y * B.y; }
template <typename X, typename Y>
X operator^(pair<X, Y> A, pair<X, Y> B) { return A.x * B.y - A.y * B.x; }
template <typename X, typename Y>
X operator^(X a, Y b) { return a ^= b; }
template <typename X, typename Y>
X operator+(X a, Y b) { return a += b; }
template <typename X, typename Y>
X operator-(X a, Y b) { return a -= b; }
template <typename X, typename Y>
X operator*(X a, Y b) { return a *= b; }
template <typename X, typename Y>
X operator/(X a, Y b) { return a /= b; }
typedef long long ll;
typedef double dd;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<vi> vvi;
const int base = 1000000007;
ll power(ll a, ll n, ll mod = base)
{
    a = a < 0 ? (mod - (-a) % mod) : (a % mod);
    ll r = 1;
    while (n)
    {
        if (n & 1)
            r = r * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return r;
}
//================================================================Head=========================================================================//
vvi list_of_subsquence_with_size[100];
int n, flag;
char idSeq[N][20];
char des[N][2000];
char numSeq[N][2000];
int cntNum;
bool status = false;

void init()
{
    if (flag)
        return;
    flag = 1;
    for (int k = 1 << n; k--;)
    {
        vi lst;
        for (int i = 0; i < n; ++i)
        {

            if (k >> i & 1)
                lst.push_back(i);
        }
        list_of_subsquence_with_size[lst.size()].push_back(lst);
    }
}

bool fileExists(const std::string &filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

void read()
{
    if (status == false)
    {
        cntNum = 0;
        // if (fileExists("web_api_with_cpp/calculator_back-end/oeis.txt")){
        FILE *f = fopen("/home/tnt/DoAn_DucNguyenAnh/calculator_back-end/oeis.txt", "r");
        while (fgets(idSeq[cntNum], 20, f))
        {
            fgets(des[cntNum], 2000, f);
            fgets(numSeq[cntNum], 2000, f);
            cntNum++;
        }
        fclose(f);
        status == true;
    }
}

vector<int> check(vector<int> numbers)
{
    char s[2000];
    int sp = 0;
    int n = numbers.size();
    for (int i = 0; i < n - 1; ++i)
        sp += sprintf(s + sp, "%d,", numbers[i]);
    sp += sprintf(s + sp, "%d", numbers[n - 1]);
    s[sp] = '\0';

    vector<int> found;
    for (int i = 0; i < cntNum; ++i)
    {
        if (strstr(numSeq[i], s) != NULL)
        {
            found.push_back(i);
        }
    }
    return found;
}

struct permutation
{
    vi p;

    //basic function
    permutation(int n)
    {
        p.resize(n);
        iota(all(p), 0);
    }

    permutation(vi a)
    {
        p = a;
    }

    permutation() {}

    int &operator[](int i)
    {
        return p[i];
    }

    //properties of permutation (value of some popular function)
    vi descent()
    {
        vi ans;
        for (int i = 0; i < n - 1; ++i)
        {
            if (p[i] > p[i + 1])
                ans.push_back(i);
        }
        return ans;
    }

    vii inversions()
    {
        vii ans;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
            {
                if (p[i] > p[j])
                    ans.push_back({i, j});
            }
        return ans;
    }

    int des()
    {
#define DES -1
        return descent().size();
    }

    int inv()
    {
#define INV -2
        return inversions().size();
    }

    int maj()
    {
#define MAJ -3
        int ans = 0;
        vi D = descent();
        for (int i : D)
        {
            ans += i + 1;
        }
        return ans;
    }

    int numberOfRun()
    {
#define RUN 0
        int ans = 1;
        for (int i = 1; i < p.size(); ++i)
        {
            ans += p[i] < p[i - 1];
        }
        return ans;
    }

    int eulerNumber1()
    {
#define EULER 1
        int ans = 0;
        for (int i = 0; i < p.size(); ++i)
        {
            ans += p[i] > i;
        }
        return ans;
    }

    int stat();

    int match(vi pattern)
    { //return number of times this permutation matches the pattern. The pattern numbered from 1, negative mean it does not need to continue the previous one
        int ans = 0;
        init();
        for (auto &lst : list_of_subsquence_with_size[pattern.size()])
        {
            vii a;
            for (int i = 0; i < lst.size(); ++i)
            {
                if (pattern[i] > 0 && i > 0 && lst[i] != lst[i - 1] + 1)
                {
                    goto next_list;
                }
                a.push_back({p[lst[i]], abs(pattern[i])});
            }
            sort(all(a));
            for (int i = 1; i < lst.size(); ++i)
            {
                //if (a[i].second <= a[i-1].second) goto next_list;
                if ((a[i].second > a[i - 1].second) != (a[i].first > a[i - 1].first))
                    goto next_list;
                if ((a[i].second == a[i - 1].second) != (a[i].first == a[i - 1].first))
                    goto next_list;
            }
            ans++;
        next_list:;
        }
        return ans;
    }

    int match(vvi patterns)
    {
        int ans = 0;
        for (auto &pattern : patterns)
        {
            ans += match(pattern);
        }
        return ans;
    }

    int value(int functionID)
    {
        if (functionID == RUN)
            return numberOfRun();
        else //if (functionID == EULER)
            return eulerNumber1();
        // else return maj(pattern);
    }
};

vvi antiPatterns;
bool restrictedGrowthFuntion;
std::ostringstream oss;

struct Permutation_counting
{

    int functionID;
    vvi patterns = {};
    vector<int> core_vector = {};
    vector<vvi> partition_by_f_value = {};

    bool next_word(permutation &p)
    {
        int k = n - 1;
        while (k > 0)
        {
            if (p[k] == n - 1)
                k--;
            else
            {
                p[k]++;
                for (int i = k + 1; i < n; ++i)
                    p[i] = 0;
                return true;
            }
        }
        return false;
    }

    bool next_word_permutation(permutation &p)
    {
        int k = n - 1;
        while (k >= 0)
        {
            if (p[k] == n - 1)
                k--;
            else
            {
                p[k]++;
                for (int i = k + 1; i < n; ++i)
                    p[i] = 0;
                return true;
            }
        }
        return false;
    }

    Permutation_counting(int functionID = -1, vvi patterns = vvi(0)) : functionID(functionID), patterns(patterns)
    {
        int count = 0;
        if (restrictedGrowthFuntion)
        {
            core_vector.clear();
            for (int i = 0; i < n; i++)
                core_vector.push_back(0);
            permutation p({core_vector}); //Tạo một từ
                                          // permutation p({0,0,1,1,2,2});//Tạo một từ
                                          // nếu gọi p(n) thì đoạn lặp sau sẽ check mọi hoán vị độ dài n

            do
            {
                //for (int i=0; i<n; ++i) cout << p[i]; cout << endl;
                int k;
                std::vector<int> result = {};

                if (restrictedGrowthFuntion)
                {
                    for (int i = 1; i < n; ++i)
                    {
                        if (p[i] > 1 + *max_element(&p[0], &p[i]))
                            goto nextPermutation;
                    }
                }

                if (p.match(antiPatterns))
                    goto nextPermutation;

                k = functionID == -1 ? p.match(patterns) : p.value(functionID);
                if (k >= partition_by_f_value.size())
                {
                    partition_by_f_value.resize(k + 1);
                }
                partition_by_f_value[k].push_back(p.p);
                for (int i = 0; i < n; ++i)
                {
                    result.push_back(p[i]);
                }
                std::copy(result.begin(), result.end(),
                          std::ostream_iterator<int>(oss, ""));

                // Now add the last element with no delimiter
                oss << ";";
                count++;
            nextPermutation:;
            } while (next_word(p));
        }
        else
        {
            permutation p(n); //Tạo một hoán vị n số
            do
            {
                //for (int i=0; i<n; ++i) cout << p[i]; cout << endl;
                int k;
                std::vector<int> result = {};

                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = i + 1; j <= n - 1; j++)
                    {
                        if (p[i] == p[j])
                            goto nextPermutation1;
                    }
                }
                if (p.match(antiPatterns))
                    goto nextPermutation1;

                k = functionID == -1 ? p.match(patterns) : p.value(functionID);
                if (k >= partition_by_f_value.size())
                {
                    partition_by_f_value.resize(k + 1);
                }
                partition_by_f_value[k].push_back(p.p);
                for (int i = 0; i < n; ++i)
                {
                    result.push_back(p[i]);
                }
                std::copy(result.begin(), result.end(),
                          std::ostream_iterator<int>(oss, ""));

                // Now add the last element with no delimiter
                oss << ";";
                count++;
            nextPermutation1:;
            } while (next_word_permutation(p));
        }
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            list_of_subsquence_with_size[i].clear();
        }
    };

    int count_by_f_value(int k)
    {
        if (k >= partition_by_f_value.size())
            return 0;
        return partition_by_f_value[k].size();
    }
};

void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        std::cout << input.at(i) << ' ';
    }
}

std::string Calculation(int num, int checked, std::string string1)
{
#ifdef oeis
    printf("here");
#endif
    int C[100];

    // declaring character array
    char char_array[n + 1];
    int countPattern = 0;
    char argv1[100][100];
    int Note[100];
    int m = 0;
    Note[0] = -1;
    bool checkVin;
    antiPatterns.clear();
    oss.str("");
    strcpy(char_array, string1.c_str());
    for (int i = 0; i < strlen(string1.c_str()); i++)
    {
        if (char_array[i] == 44)
        {
            countPattern++;
            Note[countPattern] = i;
        }
    }
    Note[countPattern + 1] = strlen(string1.c_str());
    for (int i = 0; i <= countPattern; i++)
    {

        for (int j = 0; j < Note[i + 1] - Note[i] - 1; j++)
        {
            argv1[i][j] = char_array[m];
            m++;
        }
        m++;
    }

    for (int i = 0; i <= countPattern; i++)
    {
        int countOp = 0;
        int countCl = 0;
        std::vector<int> my_vector = {};
        int begin = 0;
        int end = 0;
        int checkVin = false;
        for (int p = 0; p < Note[i + 1] - Note[i] - 1; p++)
        {
            if (countOp > 1)
            {
                printf("Press your pattern you want correctly1!\n");
                exit(0);
            }
            else
            {
                if (argv1[i][p] == 40)
                {
                    checkVin = true;
                    countOp++;
                    begin = p;
                }
                if (argv1[i][p] == 41)
                {
                    countCl++;
                    end = p;
                }
            }
        }

        for (int p = 0; p < Note[i + 1] - Note[i] - 1; p++)
        {

            if (!checkVin)
            {
                if (p == 0)
                {
                    my_vector.push_back(argv1[i][p] - 48);
                }
                if (p > 0)
                {
                    my_vector.push_back(48 - argv1[i][p]);
                }
            }

            else
            {
                if (countCl != countOp || countOp != 1)
                {
                    printf("%d\n", countOp);
                    printf("Press your pattern you want correctly!\n");
                    exit(0);
                }
                else
                {
                    if (p == begin || p == end)
                        continue;
                    if (p < begin && p == 0)
                        my_vector.push_back(argv1[i][p] - 48);
                    if (p > end)
                        my_vector.push_back(48 - argv1[i][p]);
                    if (p < begin && p != 0)
                        my_vector.push_back(48 - argv1[i][p]);
                    if (p < end && p > begin && p == begin + 1)
                        my_vector.push_back(48 - argv1[i][p]);
                    if (p < end && p > begin && p != begin + 1)
                        my_vector.push_back(argv1[i][p] - 48);
                }
            }
        }
        antiPatterns.push_back(vi(my_vector));
    }
    //freopen("rgf.inp", "r", stdin);
    //freopen("rgf.out", "w", stdout);
    vi vt;
    for(int i = 0; i <antiPatterns.size();i++){
        cout << antiPatterns[i] << endl;
    }
    if (num > 0)
    {
        n = num;
        vvi patterns;
        patterns.clear();

        /*Số âm có nghĩa là nó không cần liền kề với phần tử trước đó. VD -1, -3, 2 có nghĩa 132 với 32 kề nhau*/
        //patterns.push_back(vi({1, -2, 2}));
        //patterns.push_back(vi({-2,1}));
        //patterns.push_back(vi({-2,-3,1}));

        /*Các hoán vị sẽ tránh hết mọi pattern trong danh sách antiPatterns*/
        //antiPatterns.push_back(vi({2,-1,3}));
        // antiPatterns.push_back(vi({1, -2, 2}));
        // antiPatterns.push_back(vi({1, 2, 3}));
        if (checked == 1)
            restrictedGrowthFuntion = true; //Có dùng điều kiện pi<=max(pj+1) mọi j<i hay không?
        else
            restrictedGrowthFuntion = false;
        Permutation_counting run(-1, patterns);
        for (int k = 0; k < run.partition_by_f_value.size(); ++k)
        {
            printf("k = %d, #value = %d\n", k, run.count_by_f_value(k));
        }
    }
    else
    {
        if (cntNum == 0)
        {
            read();
        }
        for (int i = 0; i < antiPatterns.size(); i++)
        {
            cout << antiPatterns[i];
        }
        cout << endl;
        for (n = 1; n < 10; n++)
        {
            vvi patterns;
            /*Số âm có nghĩa là nó không cần liền kề với phần tử trước đó. VD -1, -3, 2 có nghĩa 132 với 32 kề nhau*/
            //patterns.push_back(vi({1, -2, 2}));
            //patterns.push_back(vi({-2,1}));
            //patterns.push_back(vi({-2,-3,1}));

            /*Các hoán vị sẽ tránh hết mọi pattern trong danh sách antiPatterns*/
            //antiPatterns.push_back(vi({2,-1,3}));
            // antiPatterns.push_back(vi({3, -1, -2}));

            if (checked == 1)
                restrictedGrowthFuntion = true; //Có dùng điều kiện pi<=max(pj+1) mọi j<i hay không?
            else
                restrictedGrowthFuntion = false;

            Permutation_counting run(-1, patterns);
            for (int k = 0; k < run.partition_by_f_value.size(); ++k)
            {
                // printf("k = %d, #value = %d\n", k, run.count_by_f_value(k));
                vt.push_back(run.count_by_f_value(k));
            }
        }
        vector<int> found = check(vt);
        cout << endl;
        oss.str("");
        if (found.size() > 0)
        {
            for (int i = 0; i < found.size(); i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    oss << des[found[i]][j];
                }
                oss << ";";
                // Now add the last element with no delimiter
            }
        }
        vt.clear();
        found.clear();
    }
    return oss.str();
}
