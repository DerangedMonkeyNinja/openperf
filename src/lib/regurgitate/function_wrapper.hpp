#ifndef _LIB_REGURGITATE_FUNCTION_WRAPPER_H_
#define _LIB_REGURGITATE_FUNCTION_WRAPPER_H_

#include <array>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>

#include "benchmark.hpp"
#include "instruction_set.hpp"

namespace regurgitate {

constexpr std::string_view debug_var_name = "REGURGITATE_DEBUG";

template <typename FunctionType>
constexpr FunctionType get_function(
    const std::array<std::pair<instruction_set::type, FunctionType>,
                     static_cast<int>(instruction_set::type::MAX)>& functions,
    instruction_set::type t)
{
    auto cursor = std::begin(functions), end = std::end(functions);
    while (cursor != end) {
        if (cursor->first == t) { return (cursor->second); }
        cursor++;
    }
    return (nullptr);
}

template <typename FunctionType>
constexpr instruction_set::type get_instruction_set(
    const std::array<std::pair<instruction_set::type, FunctionType>,
                     static_cast<int>(instruction_set::type::MAX)>& functions,
    FunctionType f)
{
    auto cursor = std::begin(functions), end = std::end(functions);
    while (cursor != end) {
        if (cursor->second == f) return (cursor->first);
        cursor++;
    }
    return (instruction_set::type::NONE);
}

template <typename FunctionType> struct function_wrapper
{
    constexpr static std::array<std::pair<instruction_set::type, FunctionType>,
                                static_cast<int>(instruction_set::type::MAX)>
        functions;
    std::string_view name;
    FunctionType best = nullptr;

    template <typename... Args> auto operator()(Args&&... args)
    {
        return (std::invoke(std::forward<FunctionType>(best),
                            std::forward<Args>(args)...));
    }

    template <typename... Args> void init(Args&&... args)
    {
        using timed_function =
            std::pair<std::chrono::nanoseconds, FunctionType>;
        std::vector<timed_function> runtimes;
        runtimes.reserve(static_cast<int>(instruction_set::type::MAX));

        if constexpr (instruction_set::enabled(instruction_set::type::AUTO)) {
            auto f = get_function(functions, instruction_set::type::AUTO);
            runtimes.emplace_back(
                benchmark::measure_function_runtime(
                    std::forward<FunctionType>(f), std::forward<Args>(args)...),
                f);
        }
        if constexpr (instruction_set::enabled(instruction_set::type::SSE2)) {
            if (instruction_set::available(instruction_set::type::SSE2)) {
                auto f = get_function(functions, instruction_set::type::SSE2);
                runtimes.emplace_back(benchmark::measure_function_runtime(
                                          std::forward<FunctionType>(f),
                                          std::forward<Args>(args)...),
                                      f);
            }
        }
        if constexpr (instruction_set::enabled(instruction_set::type::SSE4)) {
            if (instruction_set::available(instruction_set::type::SSE4)) {
                auto f = get_function(functions, instruction_set::type::SSE4);
                runtimes.emplace_back(benchmark::measure_function_runtime(
                                          std::forward<FunctionType>(f),
                                          std::forward<Args>(args)...),
                                      f);
            }
        }
        if constexpr (instruction_set::enabled(instruction_set::type::AVX)) {
            if (instruction_set::available(instruction_set::type::AVX)) {
                auto f = get_function(functions, instruction_set::type::AVX);
                runtimes.emplace_back(benchmark::measure_function_runtime(
                                          std::forward<FunctionType>(f),
                                          std::forward<Args>(args)...),
                                      f);
            }
        }
        if constexpr (instruction_set::enabled(instruction_set::type::AVX2)) {
            if (instruction_set::available(instruction_set::type::AVX2)) {
                auto f = get_function(functions, instruction_set::type::AVX2);
                runtimes.emplace_back(benchmark::measure_function_runtime(
                                          std::forward<FunctionType>(f),
                                          std::forward<Args>(args)...),
                                      f);
            }
        }
        if constexpr (instruction_set::enabled(
                          instruction_set::type::AVX512SKX)) {
            if (instruction_set::available(instruction_set::type::AVX512SKX)) {
                auto f =
                    get_function(functions, instruction_set::type::AVX512SKX);
                runtimes.emplace_back(benchmark::measure_function_runtime(
                                          std::forward<FunctionType>(f),
                                          std::forward<Args>(args)...),
                                      f);
            }
        }

        best = std::min_element(
                   begin(runtimes),
                   end(runtimes),
                   [](const timed_function& x, const timed_function& y) {
                       return (x.first < y.first);
                   })
                   ->second;

        /*
         * Log benchmarking details to stderr if the proper environment variable
         * is set
         */
        static const char* debug_var = std::getenv(debug_var_name.data());
        if (debug_var && std::strncmp(debug_var, "0", 1) != 0) {
            std::cerr << "Benchmarking " << name << "..." << std::endl;
            for (const auto& item : runtimes) {
                std::cerr << " Measured " << item.first.count() << " ns using "
                          << instruction_set::to_string(
                                 get_instruction_set(functions, item.second))
                          << " instructions" << std::endl;
            }

            std::cerr << " Picking the "
                      << instruction_set::to_string(
                             get_instruction_set(functions, best))
                      << " version" << std::endl;
        }
    }
};

template <typename FunctionType>
constexpr instruction_set::type
get_instruction_set(const function_wrapper<FunctionType>& wrapper)
{
    auto item = std::find_if(
        std::begin(function_wrapper<FunctionType>::functions),
        std::end(function_wrapper<FunctionType>::functions),
        [&](const auto& pair) { return (pair.second == wrapper.best); });
    return (item == std::end(function_wrapper<FunctionType>::functions)
                ? instruction_set::type::NONE
                : (*item).first);
}

} // namespace regurgitate

#define ISPC_FUNCTION_WRAPPER_INIT_FUNCTION_DATA(f)                            \
    {regurgitate::instruction_set::type::AUTO,                                 \
     (regurgitate::instruction_set::automatic_enabled ? ispc::f : nullptr)},   \
        {regurgitate::instruction_set::type::SSE2,                             \
         (regurgitate::instruction_set::sse2_enabled ? ispc::f##_sse2          \
                                                     : nullptr)},              \
        {regurgitate::instruction_set::type::SSE4,                             \
         (regurgitate::instruction_set::sse4_enabled ? ispc::f##_sse4          \
                                                     : nullptr)},              \
        {regurgitate::instruction_set::type::AVX,                              \
         (regurgitate::instruction_set::avx_enabled ? ispc::f##_avx            \
                                                    : nullptr)},               \
        {regurgitate::instruction_set::type::AVX2,                             \
         (regurgitate::instruction_set::avx2_enabled ? ispc::f##_avx2          \
                                                     : nullptr)},              \
    {                                                                          \
        regurgitate::instruction_set::type::AVX512SKX,                         \
            (regurgitate::instruction_set::avx512skx_enabled                   \
                 ? ispc::f##_avx512skx                                         \
                 : nullptr)                                                    \
    }

#define ISPC_FUNCTION_WRAPPER_INIT(ret, f, ...)                                \
    namespace ispc {                                                           \
    extern "C" ret f(__VA_ARGS__);                                             \
    extern "C" ret f##_sse2(__VA_ARGS__);                                      \
    extern "C" ret f##_sse4(__VA_ARGS__);                                      \
    extern "C" ret f##_avx(__VA_ARGS__);                                       \
    extern "C" ret f##_avx2(__VA_ARGS__);                                      \
    extern "C" ret f##_avx512skx(__VA_ARGS__);                                 \
    }                                                                          \
    template <>                                                                \
    constexpr std::array<                                                      \
        std::pair<regurgitate::instruction_set::type, decltype(&ispc::f)>,     \
        static_cast<int>(regurgitate::instruction_set::type::MAX)>             \
        regurgitate::function_wrapper<decltype(&ispc::f)>::functions = {       \
            {ISPC_FUNCTION_WRAPPER_INIT_FUNCTION_DATA(f)}}

#endif /* _LIB_REGURGITATE_FUNCTION_WRAPPER_H_ */
