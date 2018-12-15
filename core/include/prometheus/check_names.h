#pragma once

#include <string>

#include "prometheus/detail/visibility.h"

namespace prometheus {

PROMETHEUSCPP_API bool CheckMetricName(const std::string& name);
PROMETHEUSCPP_API bool CheckLabelName(const std::string& name);
}  // namespace prometheus
