const int BASE = 27; //may vary, but must be prime and gcd(BASE, M) must be 1
const int M = 1000000007;

int get_hash(string & s) {
    int result = 0;
    for (auto c: s)
        result = ((long long)result * BASE + c - 'a' + 1) % M;
    return result;
}

int get_hash(int i, int j, int * prefix, int * power) {
    return (prefix[j] - (long long)prefix[i-1] * power[j-i+1] % M + M) % M;
}

void calc_prefix(string & s, int * prefix) {
    int n = s.size();
    prefix[0] = 0;
    for (int i = 0; i < n; ++i)
        prefix[i+1] = ((long long)prefix[i] * BASE + s[i] - 'a' + 1) % M;
}

void calc_power(int n, int * power) {
    power[0] = 1;
    for (int i = 0; i < n; ++i)
        power[i+1] = (long long) power[i] * BASE % M;
}