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
MockHotRestart::MockHotRestart() : stats_allocator_(*symbol_table_) {
  ON_CALL(*this, logLock()).WillByDefault(ReturnRef(log_lock_));
  ON_CALL(*this, accessLogLock()).WillByDefault(ReturnRef(access_log_lock_));
  ON_CALL(*this, statsAllocator()).WillByDefault(ReturnRef(stats_allocator_));
}

MockHotRestart::~MockHotRestart() = default;



}

}
