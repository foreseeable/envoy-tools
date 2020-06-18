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
class MockHotRestart : public HotRestart {
public:
  MockHotRestart();
  ~MockHotRestart() override;

  // Server::HotRestart
  MOCK_METHOD(void, drainParentListeners, ());
  MOCK_METHOD(int, duplicateParentListenSocket, (const std::string& address));
  MOCK_METHOD(std::unique_ptr<envoy::HotRestartMessage>, getParentStats, ());
  MOCK_METHOD(void, initialize, (Event::Dispatcher & dispatcher, Server::Instance& server));
  MOCK_METHOD(void, sendParentAdminShutdownRequest, (time_t & original_start_time));
  MOCK_METHOD(void, sendParentTerminateRequest, ());
  MOCK_METHOD(ServerStatsFromParent, mergeParentStatsIfAny, (Stats::StoreRoot & stats_store));
  MOCK_METHOD(void, shutdown, ());
  MOCK_METHOD(uint32_t, baseId, ());
  MOCK_METHOD(std::string, version, ());
  MOCK_METHOD(Thread::BasicLockable&, logLock, ());
  MOCK_METHOD(Thread::BasicLockable&, accessLogLock, ());
  MOCK_METHOD(Stats::Allocator&, statsAllocator, ());

private:
  Stats::TestSymbolTable symbol_table_;
  Thread::MutexBasicLockable log_lock_;
  Thread::MutexBasicLockable access_log_lock_;
  Stats::AllocatorImpl stats_allocator_;
};
}

}
