// upizpp 2024/4/20
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

constexpr const char *alpha = "α";

using int_t = std::int64_t;

vector<int_t> sin_c{1};
vector<int_t> cos_c{1};
int_t k = 1;

void print(const char *func, int_t pow) {
    if (pow == 0) {
        return;
    }
    cout << func;
    if (pow > 1)
        cout << "^" << pow;
    cout << " " << alpha;
}

void print(int_t sin_pow) {
    print("sin", sin_pow);
    if (k - sin_pow != 0) {
        if (sin_pow != 0)
            cout << " ";
        print("cos", k - sin_pow);
    }
}

void print(int_t k, bool no_symbol) {
    if (k == -1)
        cout << (no_symbol ? '\0' : '-');
    else if (k == 1)
        cout << (no_symbol ? '\0' : '+');
    else if (k > 0)
        cout << (no_symbol ? '\0' : '+') << k;
    else if (k < 0)
        cout << (no_symbol ? '\0' : '-') << -k;
}
void print(int_t k, const vector<int_t> &sin, const vector<int_t> &cos) {
    cout << "sin " << k << alpha << " = ";
    for (int_t i = 0, sin_pow = k % 2 == 0 ? k - 1 : k; sin_pow >= 0;
         ++i, sin_pow -= 2) {
        print(sin[i], i == 0);
        print(sin_pow);
    }
    cout << endl;
    cout << "cos " << k << alpha << " = ";
    for (int_t i = 0, sin_pow = k % 2 == 0 ? k : k - 1; sin_pow >= 0;
         ++i, sin_pow -= 2) {
        print(cos[i], i == 0);
        print(sin_pow);
    }
    cout << endl;
    cout << "tan " << k << alpha << " = " << '(';
    for (int_t i = 0, sin_pow = k % 2 == 0 ? k - 1 : k; sin_pow >= 0;
         ++i, sin_pow -= 2) {
        print(sin[i], i == 0);
        print("tan", sin_pow);
    }
    cout << ") / (";
    for (int_t i = 0, sin_pow = k % 2 == 0 ? k : k - 1; sin_pow >= 0;
         ++i, sin_pow -= 2) {
        print(cos[i], i == 0);
        print("tan", sin_pow);
    }
    cout << ")";
    cout << endl;
}

void next_level() {
    vector<int_t> new_sin;
    vector<int_t> new_cos;
    k += 1;
    if (k % 2 == 0) {
        for (size_t i = 0; i < sin_c.size(); i++)
            new_sin.push_back(sin_c[i] + cos_c[i]);
        new_cos.push_back(-sin_c[0]);
        for (size_t i = 0; i < cos_c.size(); i++)
            new_cos.push_back(cos_c[i] -
                              (i + 1 < sin_c.size() ? sin_c[i + 1] : 0));
    } else {
        new_sin.push_back(cos_c[0]);
        for (size_t i = 0; i < sin_c.size(); i++)
            new_sin.push_back(sin_c[i] +
                              (i + 1 < cos_c.size() ? cos_c[i + 1] : 0));
        for (size_t i = 0; i < cos_c.size(); i++)
            new_cos.push_back(cos_c[i] - sin_c[i]);
    }
    while (new_sin.size() > new_cos.size())
        new_cos.push_back(0);
    while (new_cos.size() > new_sin.size())
        new_sin.push_back(0);
    sin_c.swap(new_sin);
    cos_c.swap(new_cos);
}

int main() {
    int_t n;
    cin >> n;
    for (size_t i = 0; i < n - 1; i++)
        next_level();
    print(k, sin_c, cos_c);
    return 0;
}