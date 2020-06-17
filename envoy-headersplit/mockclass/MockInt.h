#pragma once
#include<cstdio>
#include"tmp.h"

#include "Base.h"
namespace mocktest {
class MockInt:Base{
  class tmp{
    long f;
  };
  int num;
  int getInt();
  MockInt addOne();
};
}
