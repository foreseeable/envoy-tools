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
  MockInt addOne();
};

class MockData:Base{
 public:
  MockInt nums[10];
  MockInt getInt(int index);
  MockInt getInt(MockInt index);
};
}
