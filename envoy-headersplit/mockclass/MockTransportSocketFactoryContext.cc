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
MockTransportSocketFactoryContext::MockTransportSocketFactoryContext()
    : secret_manager_(std::make_unique<Secret::SecretManagerImpl>(config_tracker_)) {
  ON_CALL(*this, clusterManager()).WillByDefault(ReturnRef(cluster_manager_));
  ON_CALL(*this, api()).WillByDefault(ReturnRef(api_));
  ON_CALL(*this, messageValidationVisitor())
      .WillByDefault(ReturnRef(ProtobufMessage::getStrictValidationVisitor()));
}


MockTransportSocketFactoryContext::~MockTransportSocketFactoryContext() = default;



}

}

}
