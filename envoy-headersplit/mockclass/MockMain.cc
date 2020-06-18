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

namespace Configuration {
namespace Server {
namespace Envoy {
MockMain::MockMain(int wd_miss, int wd_megamiss, int wd_kill, int wd_multikill)
    : wd_miss_(wd_miss), wd_megamiss_(wd_megamiss), wd_kill_(wd_kill), wd_multikill_(wd_multikill) {
  ON_CALL(*this, wdMissTimeout()).WillByDefault(Return(wd_miss_));
  ON_CALL(*this, wdMegaMissTimeout()).WillByDefault(Return(wd_megamiss_));
  ON_CALL(*this, wdKillTimeout()).WillByDefault(Return(wd_kill_));
  ON_CALL(*this, wdMultiKillTimeout()).WillByDefault(Return(wd_multikill_));
}


MockMain::~MockMain() = default;



}

}

}
