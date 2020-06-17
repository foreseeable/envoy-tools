#pragma once
#include<cstdio>
#include"tmp.h"

#include "MockInt.h"
#include "Base.h"
namespace mocktest {
class MockData:Base{
 public:
  MockInt nums[10];
  MockInt getInt(int index);
  MockInt getInt(MockInt index);
};
}
