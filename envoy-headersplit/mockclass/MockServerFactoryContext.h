#pragma once

#include <chrono>
#include <cstdint>
#include <list>
#include <string>

#include "envoy/common/mutex_tracer.h"
#include "envoy/config/bootstrap/v3/bootstrap.pb.h"
#include "envoy/config/core/v3/base.pb.h"
#include "envoy/config/core/v3/config_source.pb.h"
#include "envoy/config/listener/v3/listener.pb.h"
#include "envoy/config/listener/v3/listener_components.pb.h"
#include "envoy/protobuf/message_validator.h"
#include "envoy/server/admin.h"
#include "envoy/server/bootstrap_extension_config.h"
#include "envoy/server/configuration.h"
#include "envoy/server/drain_manager.h"
#include "envoy/server/filter_config.h"
#include "envoy/server/health_checker_config.h"
#include "envoy/server/instance.h"
#include "envoy/server/options.h"
#include "envoy/server/overload_manager.h"
#include "envoy/server/tracer_config.h"
#include "envoy/server/transport_socket_config.h"
#include "envoy/server/worker.h"
#include "envoy/ssl/context_manager.h"
#include "envoy/stats/scope.h"
#include "envoy/thread/thread.h"

#include "common/grpc/context_impl.h"
#include "common/http/context_impl.h"
#include "common/secret/secret_manager_impl.h"
#include "common/stats/fake_symbol_table_impl.h"

#include "extensions/transport_sockets/tls/context_manager_impl.h"

#include "test/mocks/access_log/mocks.h"
#include "test/mocks/api/mocks.h"
#include "test/mocks/event/mocks.h"
#include "test/mocks/http/mocks.h"
#include "test/mocks/init/mocks.h"
#include "test/mocks/local_info/mocks.h"
#include "test/mocks/network/mocks.h"
#include "test/mocks/protobuf/mocks.h"
#include "test/mocks/router/mocks.h"
#include "test/mocks/runtime/mocks.h"
#include "test/mocks/secret/mocks.h"
#include "test/mocks/stats/mocks.h"
#include "test/mocks/thread_local/mocks.h"
#include "test/mocks/tracing/mocks.h"
#include "test/mocks/upstream/mocks.h"
#include "test/test_common/test_time_system.h"

#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "spdlog/spdlog.h"

#include "MockInstance.h"
#include "MockDrainManager.h"
#include "MockAdmin.h"
namespace Envoy {
namespace Server {
namespace Configuration {
class MockServerFactoryContext : public virtual ServerFactoryContext {
public:
  MockServerFactoryContext();
  ~MockServerFactoryContext() override;

  MOCK_METHOD(Upstream::ClusterManager&, clusterManager, ());
  MOCK_METHOD(Event::Dispatcher&, dispatcher, ());
  MOCK_METHOD(const Network::DrainDecision&, drainDecision, ());
  MOCK_METHOD(const LocalInfo::LocalInfo&, localInfo, (), (const));
  MOCK_METHOD(Envoy::Runtime::RandomGenerator&, random, ());
  MOCK_METHOD(Envoy::Runtime::Loader&, runtime, ());
  MOCK_METHOD(Stats::Scope&, scope, ());
  MOCK_METHOD(Singleton::Manager&, singletonManager, ());
  MOCK_METHOD(ThreadLocal::Instance&, threadLocal, ());
  MOCK_METHOD(Server::Admin&, admin, ());
  MOCK_METHOD(TimeSource&, timeSource, ());
  Event::TestTimeSystem& timeSystem() { return time_system_; }
  MOCK_METHOD(ProtobufMessage::ValidationContext&, messageValidationContext, ());
  MOCK_METHOD(ProtobufMessage::ValidationVisitor&, messageValidationVisitor, ());
  MOCK_METHOD(Api::Api&, api, ());
  Grpc::Context& grpcContext() override { return grpc_context_; }
  MOCK_METHOD(Server::DrainManager&, drainManager, ());
  MOCK_METHOD(Init::Manager&, initManager, ());
  MOCK_METHOD(ServerLifecycleNotifier&, lifecycleNotifier, ());

  testing::NiceMock<Upstream::MockClusterManager> cluster_manager_;
  testing::NiceMock<Event::MockDispatcher> dispatcher_;
  testing::NiceMock<MockDrainManager> drain_manager_;
  testing::NiceMock<LocalInfo::MockLocalInfo> local_info_;
  testing::NiceMock<Envoy::Runtime::MockRandomGenerator> random_;
  testing::NiceMock<Envoy::Runtime::MockLoader> runtime_loader_;
  testing::NiceMock<Stats::MockIsolatedStatsStore> scope_;
  testing::NiceMock<ThreadLocal::MockInstance> thread_local_;
  testing::NiceMock<ProtobufMessage::MockValidationContext> validation_context_;
  Singleton::ManagerPtr singleton_manager_;
  testing::NiceMock<MockAdmin> admin_;
  Event::GlobalTimeSystem time_system_;
  testing::NiceMock<Api::MockApi> api_;
  Grpc::ContextImpl grpc_context_;
};
}

}

}
