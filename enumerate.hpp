#pragma once
#include <type_traits>
#include <cstddef>
#include <utility>

namespace en
{
template <typename container_type>
struct enumerate_wrapper
{
    using iterator_type = std::conditional_t<std::is_const_v<container_type>, typename container_type::const_iterator, typename container_type::iterator>;
    using pointer_type = std::conditional_t<std::is_const_v<container_type>, typename container_type::const_pointer, typename container_type::pointer>;
    using reference_type = std::conditional_t<std::is_const_v<container_type>, typename container_type::const_reference, typename container_type::reference>;

    constexpr enumerate_wrapper(container_type& c): container(c)
    {

    }

    struct enumerate_wrapper_iter
    {
        size_t index;
        iterator_type value;


        constexpr bool operator!=(const iterator_type& other) const
        {
            return value != other;
        }
        constexpr enumerate_wrapper_iter& operator++()
        {
            ++index;
            ++value;
            return *this;
        }

        constexpr std::pair<size_t, reference_type> operator*() {
            return std::pair<size_t, reference_type>{index, *value};
        }
    };

    constexpr enumerate_wrapper_iter begin()
    {
        return {0, std::begin(container)};
    }

    constexpr iterator_type end()
    {
        return std::end(container);
    }
    container_type& container;
};

template <typename container_type>
constexpr auto enumerate(container_type& c)
{
    return enumerate_wrapper(c);
}
}
