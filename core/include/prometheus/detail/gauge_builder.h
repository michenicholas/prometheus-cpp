#pragma once

#include <map>
#include <string>

#include "prometheus/detail/core_export.h"

namespace prometheus {

template <typename T>
class Family;
class Gauge;
class Registry;

namespace detail {

class PROMETHEUS_CPP_CORE_EXPORT GaugeBuilder {
 public:
  GaugeBuilder& Labels(const std::map<std::string, std::string>& labels);
  GaugeBuilder& Name(const std::string&);
  GaugeBuilder& Help(const std::string&);
  Family<Gauge>& Register(Registry&);

 private:
  std::map<std::string, std::string> labels_;
  std::string name_;
  std::string help_;
};

}  // namespace detail
}  // namespace prometheus
