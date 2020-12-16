#pragma once
#include <fstream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>
#include <vector>
#include <mutex>
#include <thread>
#include <stdexcept>

const size_t maxSize = 4 * 1024 * 1024 / sizeof(uint64_t) - 100;

using namespace std;

void soloSort(ifstream &fin, mutex &f_mutex, size_t &fnum, mutex &n_mutex) {
  uint64_t *arr = new uint64_t[maxSize]();
  size_t top;
  while (true) {
    for (top = 0; top < maxSize; top++) {
      unique_lock<mutex> unique(f_mutex);
      if (!fin.read((char *)&arr[top], sizeof(arr[top]))) {
        break;
      }
    }
    if (top == 0) {
      delete[] arr;
      return;
    }
    size_t tmp_fnum;
    {
      lock_guard<mutex> guard(n_mutex);
      tmp_fnum = fnum++;
    }
    sort(arr, arr + top);
    ofstream fout("sort_" + to_string(tmp_fnum) + ".bin", ios::binary);
    if (!fout.is_open()) {
      throw runtime_error("Problem with file\n");
    }
    fout.write((char *)arr, top * sizeof(arr[0]));
  }
}

void allSort(const string &ifn, const string &ofn) {
  ifstream fin(ifn, ios::binary);
  if (!fin.is_open()) {
    throw runtime_error("file can't be opened");
  }
  mutex m1, m2;
  size_t num = 0;
  thread first_thread(soloSort, ref(fin), ref(m1), ref(num), ref(m2));
  thread second_thread(soloSort, ref(fin), ref(m1), ref(num), ref(m2));
  first_thread.join();
  second_thread.join();
  priority_queue<pair<uint64_t, size_t>, vector<pair<uint64_t, size_t> >,
                 greater<pair<uint64_t, size_t> > > q;
  vector<ifstream> f_vec;
  for (size_t i = 0; i < num; i++) {
    f_vec.emplace_back("sort_" + to_string(i) + ".bin", ios::binary);
    if (!f_vec[f_vec.size() - 1].is_open()) {
      throw runtime_error("Problem with file");
    }
  }
  for (size_t i = 0; i < num; i++) {
    int64_t cur;
    f_vec[i].read((char *)&cur, sizeof(cur));
    q.push({cur, i});
  }
  ofstream fout(ofn, ios::binary);
  if (!fout.is_open()) {
    throw runtime_error("file cannot be open");
  }
  while (!q.empty()) {
    fout.write((char *)&q.top(), sizeof(q.top().first));
    int64_t cur;
    if (f_vec[q.top().second].read((char *)&cur, sizeof(cur))) {
      q.push({cur, q.top().second});
    }
    q.pop();
  }
  for (size_t i = 0; i < num; i++) {
    f_vec[i].close();
    if (remove(("sort_" + to_string(i) + ".bin").c_str())) {
      throw runtime_error("file cannot be removed\n");
    }
  }
}