#include "mocks.h"

int mocktest::MockInt::getInt(){
  return 42;
}
mocktest::MockInt mocktest::MockInt::addOne(){
  return {};
}

mocktest::MockInt mocktest::MockData::getInt(int index){
  return 54;
}

mocktest::MockInt mocktest::MockData::getInt(MockInt index){
  return 540;
}
