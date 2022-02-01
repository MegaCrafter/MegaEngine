#pragma once
#include <memory>

namespace Engine {

template <typename T, typename R = std::default_delete<T>>
using Ref = std::unique_ptr<T, R>;

template <typename T>
using Shared = std::shared_ptr<T>;

}  // namespace Engine