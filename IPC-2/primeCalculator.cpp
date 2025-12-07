#include <iostream>
#include <unistd.h>
using namespace std;

long long nthPrime(int n) {
    int count = 0;
    long long num = 2;
    while (true) {
        bool prime = true;
        for (long long i = 2; i * i <= num; i++)
            if (num % i == 0) { prime = false; break; }
        if (prime && ++count == n) return num;
        num++;
    }
}

int main() {
    int p2c[2], c2p[2];
    pipe(p2c);
    pipe(c2p);
    pid_t pid = fork();

    if (pid == 0) {
        close(p2c[1]);
        close(c2p[0]);
        while (true) {
            int m;
            if (read(p2c[0], &m, sizeof(m)) != sizeof(m))
                break;
            long long prime = nthPrime(m);
            write(c2p[1], &prime, sizeof(prime));
        }
        return 0;
    }

    close(p2c[0]);
    close(c2p[1]);
    while (true) {
        string s;
        if (!(cin >> s)) break;
        if (s == "exit") break;
        int m = stoi(s);
        write(p2c[1], &m, sizeof(m));
        long long result;
        read(c2p[0], &result, sizeof(result));
        cout << "Prime #" << m << " = " << result << endl;
    }
    return 0;
}

