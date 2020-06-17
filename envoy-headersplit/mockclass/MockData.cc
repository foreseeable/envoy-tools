#include "mocks.h"

mocktest::MockInt mocktest::MockData::getInt(int index){
  return 54;
}
mocktest::MockInt mocktest::MockData::getInt(MockInt index){
  return 540;
}
