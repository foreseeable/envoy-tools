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
#include "MockOverloadManager.h"
#include "MockDrainManager.h"
#include "MockServerFactoryContext.h"
#include "MockAdmin.h"
#include "MockServerLifecycleNotifier.h"
namespace Envoy {
namespace Server {
namespace Configuration {
class MockFactoryContext : public virtual FactoryContext {
public:
  MockFactoryContext();
  ~MockFactoryContext() override;

  MOCK_METHOD(ServerFactoryContext&, getServerFactoryContext, (), (const));
  MOCK_METHOD(TransportSocketFactoryContext&, getTransportSocketFactoryContext, (), (const));
  MOCK_METHOD(AccessLog::AccessLogManager&, accessLogManager, ());
  MOCK_METHOD(Upstream::ClusterManager&, clusterManager, ());
  MOCK_METHOD(Event::Dispatcher&, dispatcher, ());
  MOCK_METHOD(const Network::DrainDecision&, drainDecision, ());
  MOCK_METHOD(bool, healthCheckFailed, ());
  MOCK_METHOD(Init::Manager&, initManager, ());
  MOCK_METHOD(ServerLifecycleNotifier&, lifecycleNotifier, ());
  MOCK_METHOD(Envoy::Runtime::RandomGenerator&, random, ());
  MOCK_METHOD(Envoy::Runtime::Loader&, runtime, ());
  MOCK_METHOD(Stats::Scope&, scope, ());
  MOCK_METHOD(Singleton::Manager&, singletonManager, ());
  MOCK_METHOD(OverloadManager&, overloadManager, ());
  MOCK_METHOD(ThreadLocal::Instance&, threadLocal, ());
  MOCK_METHOD(Server::Admin&, admin, ());
  MOCK_METHOD(Stats::Scope&, listenerScope, ());
  MOCK_METHOD(const LocalInfo::LocalInfo&, localInfo, (), (const));
  MOCK_METHOD(const envoy::config::core::v3::Metadata&, listenerMetadata, (), (const));
  MOCK_METHOD(envoy::config::core::v3::TrafficDirection, direction, (), (const));
  MOCK_METHOD(TimeSource&, timeSource, ());
  Event::TestTimeSystem& timeSystem() { return time_system_; }
  Grpc::Context& grpcContext() override { return grpc_context_; }
  Http::Context& httpContext() override { return http_context_; }
  MOCK_METHOD(ProcessContextOptRef, processContext, ());
  MOCK_METHOD(ProtobufMessage::ValidationContext&, messageValidationContext, ());
  MOCK_METHOD(ProtobufMessage::ValidationVisitor&, messageValidationVisitor, ());
  MOCK_METHOD(Api::Api&, api, ());

  testing::NiceMock<MockServerFactoryContext> server_factory_context_;
  testing::NiceMock<AccessLog::MockAccessLogManager> access_log_manager_;
  testing::NiceMock<Upstream::MockClusterManager> cluster_manager_;
  testing::NiceMock<Event::MockDispatcher> dispatcher_;
  testing::NiceMock<MockDrainManager> drain_manager_;
  testing::NiceMock<Init::MockManager> init_manager_;
  testing::NiceMock<MockServerLifecycleNotifier> lifecycle_notifier_;
  testing::NiceMock<LocalInfo::MockLocalInfo> local_info_;
  testing::NiceMock<Envoy::Runtime::MockRandomGenerator> random_;
  testing::NiceMock<Envoy::Runtime::MockLoader> runtime_loader_;
  testing::NiceMock<Stats::MockIsolatedStatsStore> scope_;
  testing::NiceMock<ThreadLocal::MockInstance> thread_local_;
  Singleton::ManagerPtr singleton_manager_;
  testing::NiceMock<MockAdmin> admin_;
  Stats::IsolatedStoreImpl listener_scope_;
  Event::GlobalTimeSystem time_system_;
  testing::NiceMock<ProtobufMessage::MockValidationContext> validation_context_;
  testing::NiceMock<MockOverloadManager> overload_manager_;
  Grpc::ContextImpl grpc_context_;
  Http::ContextImpl http_context_;
  testing::NiceMock<Api::MockApi> api_;
};
}

}

}
