#include <iostream>
#include <fstream>
#include "Rope.hpp"

void printRequest(Rope<int> & R, size_t left, size_t right);
void FourthProblem();

int main()
{
    std::cout << "Fourth problem prints: ";
    FourthProblem();
    std::cout << "\n";

    Rope<char> a;
    char ar1[7] = {'A','B','C','D','E','F','G'};
    for (size_t i = 0; i < 7; ++i)
        a.insert(ar1[i]);
    std::cout << "Rope a = ";
    a.print();
    a.remove(0, 1);
    std::cout << "After Remove(0,1)\nRope a = ";
    a.print();
    Rope<char> b;
    char ar2[8] = {'O','P','Q','R','S','T','U','V'};
    for (size_t i = 0; i < 8; ++i)
        b.insert(ar2[i]);
    std::cout << "Rope b = ";
    b.print();
    Rope<char> c = a + b;
    std::cout << "Rope c = a + b";
    std::cout << "\nRope c = ";
    c.print();
    std::cout << "But!!!\nRope a = ";
    a.print();
    std::cout << "Rope b = ";
    b.print();
}

void printRequest(Rope<int> & R, size_t left, size_t right) {
    std::cout << "\nRequest to move [" << left << " ; " << right << "]\n";
    std::cout << "Result : ";
    R.print();
    std::cout << "\n";
}

void FourthProblem() {
    std::ifstream fin("input.txt");
    Rope<int> R;
    size_t n = 0, m = 0;
    fin >> n >> m;
    for (size_t i = 0; i < n; ++i)
        R.insert(i + 1);
    //R.print();
    size_t left = 0;
    size_t right = 0;
    for (size_t i = 0; i != m; ++i) {
        fin >> left >> right;
        if (left > right) std::swap(left, right);
        if (left < 0 || left > n || right < 0 || right > n) {
            std::cout << "Incorrect input" << "\n";
            continue;
        }
        R.moveToBegin(left - 1, right - 1);
        //printRequest(R, left, right);
    }
    R.print();
}
