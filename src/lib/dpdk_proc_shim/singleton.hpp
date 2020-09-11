#ifndef _LIB_DPDK_PROC_SHIM_UTILS_SINGLETON_HPP_
#define _LIB_DPDK_PROC_SHIM_UTILS_SINGLETON_HPP_

namespace dpdk_proc_shim::utils {

template <typename T> class singleton
{
public:
    static T& instance()
    {
        static T instance;
        return (instance);
    }

    singleton(const singleton&) = delete;
    singleton& operator=(const singleton) = delete;

protected:
    singleton() = default;
};

} // namespace dpdk_proc_shim::utils

#endif /* _LIB_DPDK_PROC_SHIM_UTILS_SINGLETON_HPP_ */
