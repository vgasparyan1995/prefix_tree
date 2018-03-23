#pragma once

#include <utility>

namespace local {

template <typename T1, typename T2>
struct unsafe_pair : public std::pair<T1, T2>
{
    template <typename ... Args>
    unsafe_pair(Args&& ... args)
        : std::pair<T1, T2>(std::forward<Args>(args)...)
    {
    }

    template <typename U1, typename U2>
    friend bool operator== (const unsafe_pair<T1, T2>& lhs, const unsafe_pair<U1, U2>& rhs)
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }

    template <typename U1, typename U2>
    friend bool operator== (const unsafe_pair<T1, T2>& lhs, const std::pair<U1, U2>& rhs)
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }

    template <typename U1, typename U2>
    friend bool operator== (const std::pair<U1, U2>& lhs, const unsafe_pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }
};

} // namespace local
