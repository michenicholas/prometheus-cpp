#pragma once

#include <string>
#include <vector>

#include "prometheus/client_metric.h"
#include "prometheus/detail/visibility.h"
#include "prometheus/metric_type.h"

namespace prometheus {

struct PROMETHEUSCPP_API MetricFamily {
  std::string name;
  std::string help;
  MetricType type = MetricType::Untyped;
  std::vector<ClientMetric> metric;
};
}  // namespace prometheus
