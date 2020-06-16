#include "mocks.h"

int mocktest::MockMap::getInt(int key){
  return 42;
}

map<int,int> mocktest::MockSet::getSet(){
  return {};
}
