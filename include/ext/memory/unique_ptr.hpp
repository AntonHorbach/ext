//
// Created by anton on 03.10.2020.
//

#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include "notowner_ptr.hpp"

#include <memory>

namespace ext::memory {

template <typename T>
struct default_create
{
    template <typename... TArgs>
    T* operator()(TArgs&&... args)
    {
        return new T(std::forward<TArgs>(args)...);
    }
};

template <typename DataType, typename Deleter = std::default_delete<DataType>>
class UniquePtr
{
    static_assert(std::is_invocable_v<Deleter&, DataType*>, "Bad deleter type");

    template <typename AllocatedType>
    explicit UniquePtr(AllocatedType* data)
            : m_data(data)
    {
    }

    template <typename AllocatedType, typename OthDeleter>
    UniquePtr(AllocatedType* data, OthDeleter&& deleter)
            : m_data(data), m_deleter(std::forward<OthDeleter>(deleter))
    {
    }

    template <typename OtherDataType, typename OthDeleter>
    friend class UniquePtr;

public:
    template <
            typename AllocType,
            typename CreatorType,
            typename DeleterType,
            typename FirstType,
            typename SecondType,
            typename  ...TArgs
    >
    friend UniquePtr<AllocType, DeleterType> make_unique(
            FirstType val1, SecondType val2, TArgs&&... args
    );

    template <
            typename AllocType,
            typename CreatorType,
            typename DeleterType,
            typename FirstType
    >
    friend UniquePtr<AllocType, DeleterType> make_unique(FirstType val);

    template <
            typename AllocType,
            typename CreatorType,
            typename DeleterType
    >
    friend UniquePtr<AllocType, DeleterType> make_unique();

    constexpr UniquePtr(std::nullptr_t val)
        : m_data(val)
    {
        static_assert(
                !std::is_pointer_v<Deleter>,
                "This constructor not for unique ptr with function deleter"
        );
    }

    explicit UniquePtr(Deleter&& deleter)
        : m_deleter(std::forward<Deleter>(deleter))
    {
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    template <typename Type, typename OthDeleter>
    UniquePtr(UniquePtr<Type, OthDeleter>&& oth) noexcept
            : m_data(oth.m_data)
    {
        if constexpr (std::is_pointer_v<Deleter>)
        {
            m_deleter = oth.m_deleter;
        }

        oth.m_data = nullptr;
    }

    template <typename Type, typename OthDeleter>
    UniquePtr& operator=(UniquePtr<Type, OthDeleter>&& oth) noexcept
    {
        free();

        m_data = oth.m_data;
        oth.m_data = nullptr;

        return *this;
    }

    explicit operator bool() const noexcept
    {
        return m_data;
    }

    DataType* release() noexcept
    {
        auto* data = m_data;

        m_data = nullptr;

        return data;
    }

    NotOwnerPtr<DataType> get() noexcept
    {
        return { m_data };
    }

    void swap(UniquePtr& oth)
    {
        std::swap(m_data, oth.m_data);
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

    friend bool operator==(const UniquePtr& ptr, std::nullptr_t val)
    {
        return ptr.m_data == val;
    }

    friend bool operator!=(const UniquePtr& ptr, std::nullptr_t val)
    {
        return ptr.m_data != val;
    }

    ~UniquePtr()
    {
        free();
    }

private:
    void free() noexcept
    {
        m_deleter(m_data);
    }

    DataType* m_data = nullptr;
    Deleter m_deleter;
};

template <
        typename AllocType,
        typename CreatorType = default_create<AllocType>,
        typename DeleterType = std::default_delete<AllocType>,
        typename FirstType,
        typename SecondType,
        typename  ...TArgs
>
UniquePtr<AllocType, DeleterType> make_unique(
        FirstType val1, SecondType val2, TArgs&&... args
)
{
    if constexpr (std::is_pointer_v<CreatorType>)
    {
        if constexpr (std::is_pointer_v<DeleterType>)
        {
            return UniquePtr<AllocType, DeleterType>{
                val1(std::forward<TArgs>(args)...), val2
            };
        }
        else
        {
            return UniquePtr<AllocType, DeleterType>{
                val1(val2, std::forward<TArgs>(args)...)
            };
        }
    }
    else
    {
        if constexpr (std::is_pointer_v<DeleterType>)
        {
            return UniquePtr<AllocType, DeleterType>{
                CreatorType{}(val2, std::forward<TArgs>(args)...), val1
            };
        }
        else
        {
            return UniquePtr<AllocType, DeleterType>{
                CreatorType{}(val1, val2, std::forward<TArgs>(args)...)
            };
        }
    }
}

template <
        typename AllocType,
        typename CreatorType = default_create<AllocType>,
        typename DeleterType = std::default_delete<AllocType>,
        typename FirstType
>
UniquePtr<AllocType, DeleterType> make_unique(FirstType val)
{
    if constexpr (!std::is_pointer_v<CreatorType> && !std::is_pointer_v<DeleterType>)
    {
        return UniquePtr<AllocType, DeleterType>{ CreatorType{}(val) };
    }
    else if constexpr (!std::is_pointer_v<CreatorType>)
    {
        return UniquePtr<AllocType, DeleterType>{ CreatorType{}(), val };
    }
    else
    {
        return UniquePtr<AllocType, DeleterType>{ val() };
    }
}

template <
        typename AllocType,
        typename CreatorType = default_create<AllocType>,
        typename DeleterType = std::default_delete<AllocType>
>
UniquePtr<AllocType, DeleterType> make_unique()
{
    return UniquePtr<AllocType, DeleterType>{ CreatorType{}() };
}

}

#endif //UNIQUE_PTR_HPP
