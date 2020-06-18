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

#include "MockOptions.h"
#include "MockConfigTracker.h"
#include "MockAdmin.h"
#include "MockAdminStream.h"
#include "MockDrainManager.h"
#include "MockWatchDog.h"
#include "MockGuardDog.h"
#include "MockHotRestart.h"
#include "MockListenerComponentFactory.h"
#include "MockListenerManager.h"
#include "MockServerLifecycleNotifier.h"
#include "MockWorkerFactory.h"
#include "MockWorker.h"
#include "MockOverloadManager.h"
#include "MockInstance.h"
#include "MockMain.h"
#include "MockServerFactoryContext.h"
#include "MockFactoryContext.h"
#include "MockTransportSocketFactoryContext.h"
#include "MockListenerFactoryContext.h"
#include "MockHealthCheckerFactoryContext.h"
#include "MockFilterChainFactoryContext.h"
#include "MockTracerFactory.h"
#include "MockTracerFactoryContext.h"
#include "MockBootstrapExtensionFactory.h"
namespace Envoy {
namespace Server {
class MockOptions : public Options {
public:
  MockOptions() : MockOptions(std::string()) {}
  MockOptions(const std::string& config_path);
  ~MockOptions() override;

  MOCK_METHOD(uint64_t, baseId, (), (const));
  MOCK_METHOD(bool, useDynamicBaseId, (), (const));
  MOCK_METHOD(const std::string&, baseIdPath, (), (const));
  MOCK_METHOD(uint32_t, concurrency, (), (const));
  MOCK_METHOD(const std::string&, configPath, (), (const));
  MOCK_METHOD(const envoy::config::bootstrap::v3::Bootstrap&, configProto, (), (const));
  MOCK_METHOD(const std::string&, configYaml, (), (const));
  MOCK_METHOD(const absl::optional<uint32_t>&, bootstrapVersion, (), (const));
  MOCK_METHOD(bool, allowUnknownStaticFields, (), (const));
  MOCK_METHOD(bool, rejectUnknownDynamicFields, (), (const));
  MOCK_METHOD(bool, ignoreUnknownDynamicFields, (), (const));
  MOCK_METHOD(const std::string&, adminAddressPath, (), (const));
  MOCK_METHOD(Network::Address::IpVersion, localAddressIpVersion, (), (const));
  MOCK_METHOD(std::chrono::seconds, drainTime, (), (const));
  MOCK_METHOD(std::chrono::seconds, parentShutdownTime, (), (const));
  MOCK_METHOD(Server::DrainStrategy, drainStrategy, (), (const));
  MOCK_METHOD(spdlog::level::level_enum, logLevel, (), (const));
  MOCK_METHOD((const std::vector<std::pair<std::string, spdlog::level::level_enum>>&),
              componentLogLevels, (), (const));
  MOCK_METHOD(const std::string&, logFormat, (), (const));
  MOCK_METHOD(bool, logFormatEscaped, (), (const));
  MOCK_METHOD(const std::string&, logPath, (), (const));
  MOCK_METHOD(uint64_t, restartEpoch, (), (const));
  MOCK_METHOD(std::chrono::milliseconds, fileFlushIntervalMsec, (), (const));
  MOCK_METHOD(Mode, mode, (), (const));
  MOCK_METHOD(const std::string&, serviceClusterName, (), (const));
  MOCK_METHOD(const std::string&, serviceNodeName, (), (const));
  MOCK_METHOD(const std::string&, serviceZone, (), (const));
  MOCK_METHOD(bool, hotRestartDisabled, (), (const));
  MOCK_METHOD(bool, signalHandlingEnabled, (), (const));
  MOCK_METHOD(bool, mutexTracingEnabled, (), (const));
  MOCK_METHOD(bool, fakeSymbolTableEnabled, (), (const));
  MOCK_METHOD(bool, cpusetThreadsEnabled, (), (const));
  MOCK_METHOD(const std::vector<std::string>&, disabledExtensions, (), (const));
  MOCK_METHOD(Server::CommandLineOptionsPtr, toCommandLineOptions, (), (const));

  std::string config_path_;
  envoy::config::bootstrap::v3::Bootstrap config_proto_;
  std::string config_yaml_;
  absl::optional<uint32_t> bootstrap_version_;
  bool allow_unknown_static_fields_{};
  bool reject_unknown_dynamic_fields_{};
  bool ignore_unknown_dynamic_fields_{};
  std::string admin_address_path_;
  std::string service_cluster_name_;
  std::string service_node_name_;
  std::string service_zone_name_;
  spdlog::level::level_enum log_level_{spdlog::level::trace};
  std::string log_path_;
  uint32_t concurrency_{1};
  uint64_t hot_restart_epoch_{};
  bool hot_restart_disabled_{};
  bool signal_handling_enabled_{true};
  bool mutex_tracing_enabled_{};
  bool cpuset_threads_enabled_{};
  std::vector<std::string> disabled_extensions_;
};
}

}
