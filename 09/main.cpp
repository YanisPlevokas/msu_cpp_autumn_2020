#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <cstdio>
#include "sort.h"

using namespace std;

void gen_test(const string &str, const string &teststr, size_t cnt) {
  ofstream fout(str, ios::binary);
  ofstream testfout(teststr, ios::binary);
  for (size_t i = 0; i < cnt; ++i) {
    uint64_t tmp = rand() + (1llu << 31) * rand();
    fout.write((char *)&tmp, sizeof(tmp));
    testfout.write((char *)&tmp, sizeof(tmp));
  }
}

void make_test() {
  gen_test("test.bin", "testtmp.bin", 12345678);
  allSort("test.bin", "out.bin");
  ifstream fin("testtmp.bin", ios::binary);
  ifstream fout("out.bin", ios::binary);
  vector<uint64_t> v;
  uint64_t tmp;
  while (fin.read((char *)&tmp, sizeof(tmp))) {
    v.push_back(tmp);
  }
  sort(v.begin(), v.end());
  for (size_t i = 0; i < v.size(); ++i) {
    if (fout.read((char *)&tmp, sizeof(tmp))) {
      if (tmp != v[i]) {
        cout << "Sort problem" << endl;
        exit(-1);
      }
    } else {
      cout << "Not full" << endl;
      exit(-1);
    }
  }
  remove("test.bin");
  remove("testtmp.bin");
  remove("out.bin");
}

int main() {
  try {
    make_test();
  } catch (...) {
    cout << "Problem\n";
    exit(-1);
  }
  cout << "OK" << endl;
  return 0;
}