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

namespace Server {
namespace Envoy {
MockDrainManager::MockDrainManager() {
  ON_CALL(*this, startDrainSequence(_)).WillByDefault(SaveArg<0>(&drain_sequence_completion_));
}

MockDrainManager::~MockDrainManager() = default;


}

}
