#pragma once

#include <map>
#include <string>

#include "prometheus/detail/core_export.h"

namespace prometheus {

template <typename T>
class Family;
class Histogram;
class Registry;

namespace detail {

class PROMETHEUS_CPP_CORE_EXPORT HistogramBuilder {
 public:
  HistogramBuilder& Labels(const std::map<std::string, std::string>& labels);
  HistogramBuilder& Name(const std::string&);
  HistogramBuilder& Help(const std::string&);
  Family<Histogram>& Register(Registry&);

 private:
  std::map<std::string, std::string> labels_;
  std::string name_;
  std::string help_;
};

}  // namespace detail
}  // namespace prometheus
