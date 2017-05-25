#include "server/config/http/zipkin_http_tracer.h"

#include <string>

#include "common/common/utility.h"
#include "common/tracing/http_tracer_impl.h"
#include "common/tracing/zipkin/zipkin_tracer_impl.h"

namespace Envoy {
namespace Server {
namespace Configuration {

Tracing::HttpTracerPtr
ZipkinHttpTracerFactory::createHttpTracer(const Json::Object& json_config, Server::Instance& server,
                                          Upstream::ClusterManager& cluster_manager) {

  Envoy::Runtime::RandomGenerator& rand = server.random();

  Tracing::DriverPtr zipkin_driver(new Zipkin::Driver(json_config, cluster_manager, server.stats(),
                                                      server.threadLocal(), server.runtime(),
                                                      server.localInfo(), rand));

  return Tracing::HttpTracerPtr(
      new Tracing::HttpTracerImpl(std::move(zipkin_driver), server.localInfo()));
}

std::string ZipkinHttpTracerFactory::name() { return "zipkin"; }

/**
 * Static registration for the lightstep http tracer. @see RegisterHttpTracerFactory.
 */
static RegisterHttpTracerFactory<ZipkinHttpTracerFactory> register_;

} // Configuration
} // Server
} // Envoy
