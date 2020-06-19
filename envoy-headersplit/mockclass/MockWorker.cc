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
MockWorker::MockWorker() {
  ON_CALL(*this, addListener(_, _, _))
      .WillByDefault(
          Invoke([this](absl::optional<uint64_t> overridden_listener,
                        Network::ListenerConfig& config, AddListenerCompletion completion) -> void {
            UNREFERENCED_PARAMETER(overridden_listener);
            config.listenSocketFactory().getListenSocket();
            EXPECT_EQ(nullptr, add_listener_completion_);
            add_listener_completion_ = completion;
          }));

  ON_CALL(*this, removeListener(_, _))
      .WillByDefault(
          Invoke([this](Network::ListenerConfig&, std::function<void()> completion) -> void {
            EXPECT_EQ(nullptr, remove_listener_completion_);
            remove_listener_completion_ = completion;
          }));

  ON_CALL(*this, stopListener(_, _))
      .WillByDefault(Invoke([](Network::ListenerConfig&, std::function<void()> completion) -> void {
        if (completion != nullptr) {
          completion();
        }
      }));

  ON_CALL(*this, removeFilterChains(_, _, _))
      .WillByDefault(Invoke([this](uint64_t, const std::list<const Network::FilterChain*>&,
                                   std::function<void()> completion) -> void {
        EXPECT_EQ(nullptr, remove_filter_chains_completion_);
        remove_filter_chains_completion_ = completion;
      }));
}

MockWorker::~MockWorker() = default;



}

}
