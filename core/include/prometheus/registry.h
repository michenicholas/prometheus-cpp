#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "prometheus/collectable.h"
#include "prometheus/detail/future_std.h"
#include "prometheus/family.h"
#include "prometheus/metric_family.h"

namespace prometheus {

namespace detail {

template <typename T>
class Builder;

}
/// \brief Manages the collection of a number of metrics.
///
/// The Registry is responsible to expose data to a class/method/function
/// "bridge", which returns the metrics in a format Prometheus supports.
///
/// The key class is the Collectable. This has a method - called Collect() -
/// that returns zero or more metrics and their samples. The metrics are
/// represented by the class Family<>, which implements the Collectable
/// interface. A new metric is registered with BuildCounter(), BuildGauge(),
/// BuildHistogram() or BuildSummary().
///
/// The class is thread-safe. No concurrent call to any API of this type causes
/// a data race.
class Registry : public Collectable {
 public:
  /// \brief How to deal with repeatedly added family names for a type
  enum class InsertBehavior {
    /// \brief Create new family object and append
    Append,
    /// \brief Merge with existing ones if possible
    Merge,
  };

  /// \brief name Create a new registry.
  ///
  /// \param insert_behavior How to handle families with the same name.
  explicit Registry(InsertBehavior insert_behavior = InsertBehavior::Append)
      : insert_behavior_{insert_behavior} {}

  /// \brief Returns a list of metrics and their samples.
  ///
  /// Every time the Registry is scraped it calls each of the metrics Collect
  /// function.
  ///
  /// \return Zero or more metrics and their samples.
  std::vector<MetricFamily> Collect() override;

 private:
  template <typename T>
  friend class detail::Builder;

  template <typename T>
  Family<T>& Add(const std::string& name, const std::string& help,
                 const std::map<std::string, std::string>& labels);

  const InsertBehavior insert_behavior_;
  std::vector<std::unique_ptr<Collectable>> collectables_;
  std::mutex mutex_;
};

template <typename T>
Family<T>& Registry::Add(const std::string& name, const std::string& help,
                         const std::map<std::string, std::string>& labels) {
  std::lock_guard<std::mutex> lock{mutex_};
  auto family = detail::make_unique<Family<T>>(name, help, labels);
  auto& ref = *family;
  collectables_.push_back(std::move(family));
  return ref;
}

}  // namespace prometheus
