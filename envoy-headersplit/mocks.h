#pragma once
#include<cstdio>
#include<vector>

using std::vector;
namespace mocktest{
class Base{
};
class MockInt:Base{
  int num;
  int getInt();
};

class MockData:Base{
 public:
  int nums[10];
  int getInt(int index);
};
}
