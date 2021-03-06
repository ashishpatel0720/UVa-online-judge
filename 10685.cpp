#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class UnionFindDisjointSets {
  public:
    UnionFindDisjointSets(int size);
    int findSet(int a);
    bool isSameSet(int a, int b);
    void unionSet(int a, int b);
    int numDisjointSets();
    int sizeOfSet(int a);
  private:
    int size;
    vector<int> pset;
    vector<int> set_size;
};

UnionFindDisjointSets::UnionFindDisjointSets(int size) {
  this->size = size;

  set_size.assign(size, 1);
  pset.assign(size, 0);

  for (int i = 0; i < size; i++)
    pset[i] = i;
}

int UnionFindDisjointSets::findSet(int a) {
  return pset[a] == a ? a : (pset[a] = findSet(pset[a]));
}

bool UnionFindDisjointSets::isSameSet(int a, int b) {
  return findSet(a) == findSet(b);
}

void UnionFindDisjointSets::unionSet(int a, int b) {
  if (isSameSet(a, b)) return;

  size--;
  set_size[findSet(b)] += set_size[findSet(a)];
  pset[findSet(a)] = findSet(b);
}

int UnionFindDisjointSets::numDisjointSets() {
  return size;
}

int UnionFindDisjointSets::sizeOfSet(int a) {
  return set_size[findSet(a)];
}

int main(void) {
  int c, r;
  string input, anotherinput;

  while (cin >> c >> r) {
    if (c == 0 && r == 0)
      break;

    int counter = 0;
    map<string,int> m;
    UnionFindDisjointSets ds(c);

    cin.ignore(100, '\n');
    while (c--) {
      getline(cin ,input);
      m[input] = counter;
      counter++;
    }

    int result = 1;
    while (r--) {
      cin >> input >> anotherinput;
      ds.unionSet(m[input], m[anotherinput]);
      if (ds.sizeOfSet(m[input]) > result)
        result = ds.sizeOfSet(m[input]);
    }

    cout << result << endl;
  }

  return 0;
}
