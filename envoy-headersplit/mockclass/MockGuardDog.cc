#include "MockOptions.h"

#include <string>

#include "envoy/admin/v3/server_info.pb.h"
#include "envoy/config/core/v3/base.pb.h"

#include "common/singleton/manager_impl.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::_;
using testing::Invoke;
using testing::Return;
using testing::ReturnPointee;
using testing::ReturnRef;
using testing::SaveArg;

namespace Envoy {
namespace Server {
MockGuardDog::MockGuardDog() : watch_dog_(new NiceMock<MockWatchDog>()) {
  ON_CALL(*this, createWatchDog(_, _)).WillByDefault(Return(watch_dog_));
}

MockGuardDog::~MockGuardDog() = default;



}

}
