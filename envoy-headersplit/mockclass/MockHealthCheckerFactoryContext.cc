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
namespace Configuration {
MockHealthCheckerFactoryContext::MockHealthCheckerFactoryContext() {
  event_logger_ = new NiceMock<Upstream::MockHealthCheckEventLogger>();
  ON_CALL(*this, cluster()).WillByDefault(ReturnRef(cluster_));
  ON_CALL(*this, dispatcher()).WillByDefault(ReturnRef(dispatcher_));
  ON_CALL(*this, random()).WillByDefault(ReturnRef(random_));
  ON_CALL(*this, runtime()).WillByDefault(ReturnRef(runtime_));
  ON_CALL(*this, eventLogger_()).WillByDefault(Return(event_logger_));
  ON_CALL(*this, messageValidationVisitor())
      .WillByDefault(ReturnRef(ProtobufMessage::getStrictValidationVisitor()));
  ON_CALL(*this, api()).WillByDefault(ReturnRef(api_));
}


MockHealthCheckerFactoryContext::~MockHealthCheckerFactoryContext() = default;



}

}

}
