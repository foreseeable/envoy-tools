#include "mocks.h"

int mocktest::MockInt::getInt(){
  return 42;
}

int mocktest::MockData::getInt(int index){
  return 54;
}
