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
namespace Configuration {
class MockMain : public Main {
public:
  MockMain() : MockMain(0, 0, 0, 0) {}
  MockMain(int wd_miss, int wd_megamiss, int wd_kill, int wd_multikill);
  ~MockMain() override;

  MOCK_METHOD(Upstream::ClusterManager*, clusterManager, ());
  MOCK_METHOD(std::list<Stats::SinkPtr>&, statsSinks, ());
  MOCK_METHOD(std::chrono::milliseconds, statsFlushInterval, (), (const));
  MOCK_METHOD(std::chrono::milliseconds, wdMissTimeout, (), (const));
  MOCK_METHOD(std::chrono::milliseconds, wdMegaMissTimeout, (), (const));
  MOCK_METHOD(std::chrono::milliseconds, wdKillTimeout, (), (const));
  MOCK_METHOD(std::chrono::milliseconds, wdMultiKillTimeout, (), (const));

  std::chrono::milliseconds wd_miss_;
  std::chrono::milliseconds wd_megamiss_;
  std::chrono::milliseconds wd_kill_;
  std::chrono::milliseconds wd_multikill_;
};
}

}

}
