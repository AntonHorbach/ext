//
// Created by anton on 03.10.2020.
//

#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <memory>

namespace ext::memory {

//TODO: CUSTOM CREATOR FOR MAKE_UNIQUE

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
    static_assert(std::is_invocable<Deleter&, DataType*>::value, "Bad deleter type");

    template <typename AllocatedType>
    explicit UniquePtr(AllocatedType* data)
            : m_data(data)
    {}

    template <typename AllocatedType, typename OthDeleter>
    UniquePtr(AllocatedType* data, OthDeleter&& deleter)
            : m_data(data), m_deleter(std::forward<OthDeleter>(deleter))
    {}

    template <typename OtherDataType, typename OthDeleter>
    friend class UniquePtr;

public:
    template <
            typename AllocatedType, typename OthDeleter,
            typename FirstVal, typename ...TArgs
    >
    friend UniquePtr<AllocatedType, OthDeleter> make_unique(FirstVal val, TArgs&&... args);

    template <typename AllocatedType, typename OthDeleter, typename IsNotPointer>
    friend UniquePtr<AllocatedType, OthDeleter> make_unique();

    constexpr UniquePtr(std::nullptr_t val)
        : m_data(val)
    {
        static_assert(
                !std::is_pointer_v<Deleter>,
                "This constructor not for unique ptr with function deleter"
        );
    }

    explicit UniquePtr(Deleter&& deleter)
        : m_data(nullptr), m_deleter(std::forward<Deleter>(deleter))
    {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    template <typename Type, typename OthDeleter>
    UniquePtr(UniquePtr<Type, OthDeleter>&& oth) noexcept
        : m_data(oth.m_data)
    {
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

    DataType* m_data;
    Deleter m_deleter;
};

template <
        typename DataType,
        typename Deleter = std::default_delete<DataType>,
        typename FirstType,
        typename  ...TArgs
>
UniquePtr<DataType, Deleter> make_unique(FirstType val, TArgs&&... args)
{
    if constexpr (std::is_pointer_v<Deleter>)
    {
        return UniquePtr<DataType, Deleter>{
                new DataType(std::forward<TArgs>(args)...), val
        };
    }
    else if constexpr (std::is_same_v<Deleter, FirstType>)
    {
        return UniquePtr<DataType, Deleter>{
            new DataType(std::forward<TArgs>(args)...), val
        };
    }
    else
    {
        return UniquePtr<DataType, Deleter>{
            new DataType(val, std::forward<TArgs>(args)...)
        };
    }
}

template <
        typename DataType,
        typename Deleter = std::default_delete<DataType>,
        typename = std::enable_if_t<!std::is_pointer_v<Deleter>>
>
UniquePtr<DataType, Deleter> make_unique()
{
    return UniquePtr<DataType, Deleter>{ new DataType{} };
}

}

#endif //UNIQUE_PTR_HPP
