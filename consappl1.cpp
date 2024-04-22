#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int findsmallestE(int phi) {
    for (int e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            return e;
        }
    }
}

int findE(int phi) {
    std::vector<int> possible_e;

    for (int e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            possible_e.push_back(e);
            cout << e << endl;
        }
    }

    srand(time(NULL));
    int random_index = rand() % possible_e.size();

    return possible_e[random_index];
}

int findD(int e, int phi) {
    int k = 1;
    while (true) {
        k += phi;
        if (k % e == 0)
            return k / e;
    }
}

string encrypt(string message, int e, int n) {
    string encrypted = "";
    for (char c : message) {
        unsigned char m = c; 
        long long crypted = 1; 
        for (int i = 0; i < e; i++) {
            crypted = (crypted * m) % n;
        }
        encrypted += to_string(crypted) + " ";
    }
    return encrypted;
}

string decrypt(string encrypted, int d, int n) {
    string decrypted = "";
    int pos = 0;
    while (pos < encrypted.length()) {
        int crypted = stoi(encrypted.substr(pos, encrypted.find(' ', pos) - pos));
        pos = encrypted.find(' ', pos) + 1;
        long long m = 1; 
        for (int i = 0; i < d; i++) {
            m = (m * crypted) % n;
        }
        decrypted += char(m);
    }
    return decrypted;
}

int main() {
    int p = 53;
    int q = 3163;
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = findsmallestE(phi);
    int d = findD(e, phi);

    string message = "HELLO";

    string encrypted = encrypt(message, e, n);
    cout << "Encrypted message: " << encrypted << endl;
    string decrypted = decrypt(encrypted, d, n);
    cout << "Decrypted message: " << decrypted << endl;

    return 0;   
}
