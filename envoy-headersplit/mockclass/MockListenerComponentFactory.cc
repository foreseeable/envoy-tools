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
MockListenerComponentFactory::MockListenerComponentFactory()
    : socket_(std::make_shared<Network::MockListenSocket>()) {
  ON_CALL(*this, createListenSocket(_, _, _, _))
      .WillByDefault(Invoke([&](Network::Address::InstanceConstSharedPtr, Network::Socket::Type,
                                const Network::Socket::OptionsSharedPtr& options,
                                const ListenSocketCreationParams&) -> Network::SocketSharedPtr {
        if (!Network::Socket::applyOptions(options, *socket_,
                                           envoy::config::core::v3::SocketOption::STATE_PREBIND)) {
          throw EnvoyException("MockListenerComponentFactory: Setting socket options failed");
        }
        return socket_;
      }));
}

MockListenerComponentFactory::~MockListenerComponentFactory() = default;


}

}
