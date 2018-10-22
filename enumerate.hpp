#pragma once
#include <type_traits>
#include <cstddef>

namespace en
{
template <typename container_type>
struct enumerate_wrapper
{
    using iterator_type = std::conditional_t<std::is_const_v<container_type>, typename container_type::const_iterator, typename container_type::iterator>;
    using pointer_type = std::conditional_t<std::is_const_v<container_type>, typename container_type::const_pointer, typename container_type::pointer>;
    using reference_type = std::conditional_t<std::is_const_v<container_type>, typename container_type::const_reference, typename container_type::reference>;

    enumerate_wrapper(container_type& c): container(c)
    {

    }

    struct enumerate_wrapper_iter
    {
        size_t index;
        iterator_type value;


        bool operator!=(const iterator_type& other) const
        {
            return value != other;
        }
        enumerate_wrapper_iter& operator++()
        {
            ++index;
            ++value;
            return *this;
        }

        std::pair<size_t, reference_type> operator*() {
            return std::pair<size_t, reference_type>{index, *value};
        }
    };

    enumerate_wrapper_iter begin()
    {
        return {0, container.begin()};
    }

    iterator_type end()
    {
        return container.end();
    }
    container_type& container;
};

template <typename container_type>
auto enumerate(container_type& c)
{
    return enumerate_wrapper(c);
}
}
