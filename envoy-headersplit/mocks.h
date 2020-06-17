#pragma once
#include<cstdio>
#include"tmp.h"

namespace mocktest{
class Base{
};
class MockInt:Base{
  class tmp{
    long f;
  };
  int num;
  int getInt();
};

class MockData:Base{
 public:
  int nums[10];
  int getInt(int index);
};
}
