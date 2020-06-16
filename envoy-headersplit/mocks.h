#pragma once
#include<map>
#include<set>
#include<cstdio>

using std::map;
using std::set;
namespace mocktest{
class MockMap:map<int,int>{
  int getInt(int key);
};

class MockSet:set<map<int,int>>{
  map<int,int> getSet();
};
}
