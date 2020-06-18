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
class MockListenerComponentFactory : public ListenerComponentFactory {
public:
  MockListenerComponentFactory();
  ~MockListenerComponentFactory() override;

  DrainManagerPtr
  createDrainManager(envoy::config::listener::v3::Listener::DrainType drain_type) override {
    return DrainManagerPtr{createDrainManager_(drain_type)};
  }
  LdsApiPtr createLdsApi(const envoy::config::core::v3::ConfigSource& lds_config) override {
    return LdsApiPtr{createLdsApi_(lds_config)};
  }

  MOCK_METHOD(LdsApi*, createLdsApi_, (const envoy::config::core::v3::ConfigSource& lds_config));
  MOCK_METHOD(std::vector<Network::FilterFactoryCb>, createNetworkFilterFactoryList,
              (const Protobuf::RepeatedPtrField<envoy::config::listener::v3::Filter>& filters,
               Configuration::FilterChainFactoryContext& filter_chain_factory_context));
  MOCK_METHOD(std::vector<Network::ListenerFilterFactoryCb>, createListenerFilterFactoryList,
              (const Protobuf::RepeatedPtrField<envoy::config::listener::v3::ListenerFilter>&,
               Configuration::ListenerFactoryContext& context));
  MOCK_METHOD(std::vector<Network::UdpListenerFilterFactoryCb>, createUdpListenerFilterFactoryList,
              (const Protobuf::RepeatedPtrField<envoy::config::listener::v3::ListenerFilter>&,
               Configuration::ListenerFactoryContext& context));
  MOCK_METHOD(Network::SocketSharedPtr, createListenSocket,
              (Network::Address::InstanceConstSharedPtr address, Network::Socket::Type socket_type,
               const Network::Socket::OptionsSharedPtr& options,
               const ListenSocketCreationParams& params));
  MOCK_METHOD(DrainManager*, createDrainManager_,
              (envoy::config::listener::v3::Listener::DrainType drain_type));
  MOCK_METHOD(uint64_t, nextListenerTag, ());

  std::shared_ptr<Network::MockListenSocket> socket_;
};
}

}
