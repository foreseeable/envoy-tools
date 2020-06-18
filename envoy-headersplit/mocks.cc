#include "mocks.h"

namespace mocktest{
int MockInt::getInt(){
  return 42;
}
MockInt MockInt::addOne(){
  return {};
}

MockInt MockData::getInt(int index){
  return {};
}

MockInt MockData::getInt(MockInt index){
  return {};
}

}