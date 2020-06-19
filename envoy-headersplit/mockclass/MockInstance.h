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

#include "MockOverloadManager.h"
#include "MockOptions.h"
#include "MockTransportSocketFactoryContext.h"
#include "MockDrainManager.h"
#include "MockServerFactoryContext.h"
#include "MockAdmin.h"
#include "MockServerLifecycleNotifier.h"
#include "MockListenerManager.h"
#include "MockHotRestart.h"
namespace Envoy {
namespace Server {
class MockInstance : public Instance {
public:
  MockInstance();
  ~MockInstance() override;

  Secret::SecretManager& secretManager() override { return *(secret_manager_.get()); }

  MOCK_METHOD(Admin&, admin, ());
  MOCK_METHOD(Api::Api&, api, ());
  MOCK_METHOD(Upstream::ClusterManager&, clusterManager, ());
  MOCK_METHOD(Ssl::ContextManager&, sslContextManager, ());
  MOCK_METHOD(Event::Dispatcher&, dispatcher, ());
  MOCK_METHOD(Network::DnsResolverSharedPtr, dnsResolver, ());
  MOCK_METHOD(void, drainListeners, ());
  MOCK_METHOD(DrainManager&, drainManager, ());
  MOCK_METHOD(AccessLog::AccessLogManager&, accessLogManager, ());
  MOCK_METHOD(void, failHealthcheck, (bool fail));
  MOCK_METHOD(void, exportStatsToChild, (envoy::HotRestartMessage::Reply::Stats*));
  MOCK_METHOD(bool, healthCheckFailed, ());
  MOCK_METHOD(HotRestart&, hotRestart, ());
  MOCK_METHOD(Init::Manager&, initManager, ());
  MOCK_METHOD(ServerLifecycleNotifier&, lifecycleNotifier, ());
  MOCK_METHOD(ListenerManager&, listenerManager, ());
  MOCK_METHOD(Envoy::MutexTracer*, mutexTracer, ());
  MOCK_METHOD(const Options&, options, ());
  MOCK_METHOD(OverloadManager&, overloadManager, ());
  MOCK_METHOD(Runtime::RandomGenerator&, random, ());
  MOCK_METHOD(Runtime::Loader&, runtime, ());
  MOCK_METHOD(void, shutdown, ());
  MOCK_METHOD(bool, isShutdown, ());
  MOCK_METHOD(void, shutdownAdmin, ());
  MOCK_METHOD(Singleton::Manager&, singletonManager, ());
  MOCK_METHOD(time_t, startTimeCurrentEpoch, ());
  MOCK_METHOD(time_t, startTimeFirstEpoch, ());
  MOCK_METHOD(Stats::Store&, stats, ());
  MOCK_METHOD(Grpc::Context&, grpcContext, ());
  MOCK_METHOD(Http::Context&, httpContext, ());
  MOCK_METHOD(ProcessContextOptRef, processContext, ());
  MOCK_METHOD(ThreadLocal::Instance&, threadLocal, ());
  MOCK_METHOD(const LocalInfo::LocalInfo&, localInfo, (), (const));
  MOCK_METHOD(std::chrono::milliseconds, statsFlushInterval, (), (const));
  MOCK_METHOD(void, flushStats, ());
  MOCK_METHOD(ProtobufMessage::ValidationContext&, messageValidationContext, ());
  MOCK_METHOD(Configuration::ServerFactoryContext&, serverFactoryContext, ());
  MOCK_METHOD(Configuration::TransportSocketFactoryContext&, transportSocketFactoryContext, ());

  void setDefaultTracingConfig(const envoy::config::trace::v3::Tracing& tracing_config) override {
    http_context_.setDefaultTracingConfig(tracing_config);
  }

  TimeSource& timeSource() override { return time_system_; }

  NiceMock<Stats::MockIsolatedStatsStore> stats_store_;
  testing::NiceMock<ThreadLocal::MockInstance> thread_local_;
  std::shared_ptr<testing::NiceMock<Network::MockDnsResolver>> dns_resolver_{
      new testing::NiceMock<Network::MockDnsResolver>()};
  testing::NiceMock<Api::MockApi> api_;
  testing::NiceMock<MockAdmin> admin_;
  Event::GlobalTimeSystem time_system_;
  std::unique_ptr<Secret::SecretManager> secret_manager_;
  testing::NiceMock<Upstream::MockClusterManager> cluster_manager_;
  Thread::MutexBasicLockable access_log_lock_;
  testing::NiceMock<Runtime::MockLoader> runtime_loader_;
  Extensions::TransportSockets::Tls::ContextManagerImpl ssl_context_manager_;
  testing::NiceMock<Event::MockDispatcher> dispatcher_;
  testing::NiceMock<MockDrainManager> drain_manager_;
  testing::NiceMock<AccessLog::MockAccessLogManager> access_log_manager_;
  testing::NiceMock<MockHotRestart> hot_restart_;
  testing::NiceMock<MockOptions> options_;
  testing::NiceMock<Runtime::MockRandomGenerator> random_;
  testing::NiceMock<MockServerLifecycleNotifier> lifecycle_notifier_;
  testing::NiceMock<LocalInfo::MockLocalInfo> local_info_;
  testing::NiceMock<Init::MockManager> init_manager_;
  testing::NiceMock<MockListenerManager> listener_manager_;
  testing::NiceMock<MockOverloadManager> overload_manager_;
  Singleton::ManagerPtr singleton_manager_;
  Grpc::ContextImpl grpc_context_;
  Http::ContextImpl http_context_;
  testing::NiceMock<ProtobufMessage::MockValidationContext> validation_context_;
  std::shared_ptr<testing::NiceMock<Configuration::MockServerFactoryContext>>
      server_factory_context_;
  std::shared_ptr<testing::NiceMock<Configuration::MockTransportSocketFactoryContext>>
      transport_socket_factory_context_;
};
}

}
