#pragma once

#include <vector>

#include "prometheus/detail/visibility.h"

namespace prometheus {
struct MetricFamily;
}

namespace prometheus {

/// @brief Interface implemented by anything that can be used by Prometheus to
/// collect metrics.
///
/// A Collectable has to be registered for collection. See Registry.
class PROMETHEUSCPP_API Collectable {
 public:
  virtual ~Collectable() = default;

  /// \brief Returns a list of metrics and their samples.
  virtual std::vector<MetricFamily> Collect() = 0;
};

}  // namespace prometheus
