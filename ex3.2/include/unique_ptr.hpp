#include "default_deleter.hpp"
#include <utility>

// Impelement your unique_ptr here
#include <functional>

template <typename T> class unique_ptr {
    T *ptr = nullptr;
    std::function<void(T*)> deleter = default_delete<T>;
public:
    using pointer = T*;
    using element_type = T;

    T* get() { return ptr; }

    unique_ptr(T *p) : ptr(p) {}
    unique_ptr(T *p, void (*del)(T*)) : ptr(p), deleter(del) {};
    unique_ptr(unique_ptr&) = delete;
    unique_ptr(unique_ptr&& u) : ptr(std::move(u.ptr)) {
        u.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& u) {
        std::swap(u.ptr, ptr);
        return *this;
    }

    bool operator==(unique_ptr& other) { return ptr == other.ptr; }
    bool operator==( nullptr_t ) const { return ptr == nullptr; }

    bool operator!=(unique_ptr& other) { return ptr != other.ptr; }
    bool operator!=( nullptr_t ) const { return ptr != nullptr; }

    operator bool() const { return (ptr != nullptr); }
    ~unique_ptr() { deleter(ptr); };

    void reset(T *p) {
        deleter(ptr);
        ptr = p;
    }

    void reset() { reset(nullptr); }

    T* release() {
        T* temp = nullptr;
        std::swap(ptr, temp);
        return temp;
    }
};
