//
// Created by anton on 05.10.2020.
//

#ifndef NOTOWNER_PTR_HPP
#define NOTOWNER_PTR_HPP

#include <cstddef>

namespace ext::memory {

template <typename DataType>
class NotOwnerPtr
{
public:
    NotOwnerPtr(DataType* data)
        : m_data(data)
    {
    }

    NotOwnerPtr(const NotOwnerPtr&) = default;
    NotOwnerPtr(NotOwnerPtr&&) noexcept = default;

    NotOwnerPtr& operator=(const NotOwnerPtr&) = default;
    NotOwnerPtr& operator=(NotOwnerPtr&&) noexcept = default;

    explicit operator bool() const noexcept
    {
        return m_data;
    }

    const DataType& operator*() const
    {
        return *m_data;
    }

    DataType& operator*()
    {
        return *m_data;
    }

    const DataType* operator->() const
    {
        return m_data;
    }

    DataType* operator->()
    {
        return m_data;
    }

    friend bool operator==(const NotOwnerPtr& left, const NotOwnerPtr& right)
    {
        return left.m_data == right.m_data;
    }

    friend bool operator!=(const NotOwnerPtr& left, const NotOwnerPtr& right)
    {
        return left.m_data != right.m_data;
    }

    friend bool operator<(const NotOwnerPtr& left, const NotOwnerPtr& right)
    {
        return left.m_data < right.m_data;
    }

    friend bool operator>(const NotOwnerPtr& left, const NotOwnerPtr& right)
    {
        return left.m_data > right.m_data;
    }

    friend bool operator<=(const NotOwnerPtr& left, const NotOwnerPtr& right)
    {
        return left.m_data <= right.m_data;
    }

    friend bool operator>=(const NotOwnerPtr& left, const NotOwnerPtr& right)
    {
        return left >= right.m_data;
    }

    friend bool operator==(const NotOwnerPtr& ptr, std::nullptr_t val)
    {
        return ptr.m_data == val;
    }

    friend bool operator!=(const NotOwnerPtr& ptr, std::nullptr_t val)
    {
        return ptr.m_data != val;
    }

private:
    DataType* m_data;
};

}

#endif //NOTOWNER_PTR_HPP
