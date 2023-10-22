
template <typename T>
class Shared_ptr {
private:
    T* ptr;
    size_t* ref_count;

public:
    Shared_ptr() : ptr(nullptr), ref_count(nullptr) {}

    Shared_ptr(T* p) : ptr(p), ref_count(new size_t(1)) {}

    // Copy constructor
    Shared_ptr(const Shared_ptr<T>& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    // Move constructor
    Shared_ptr(Shared_ptr<T>&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // Destructor
    ~Shared_ptr() {
        if (ref_count && --(*ref_count) == 0) {

            delete ptr;
            delete ref_count;
        }
    }

    Shared_ptr<T>& operator=(const Shared_ptr<T>& other) {
        if (this != &other) {
            if (ref_count && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }

            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    // Move assignment operator
    Shared_ptr<T>& operator=(Shared_ptr<T>&& other) noexcept 
    {
        if (this != &other) 
        {
            if (ref_count && --(*ref_count) == 0) 
            {
                delete ptr;
                delete ref_count;
            }

            ptr = other.ptr;
            ref_count = other.ref_count;

            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    // Dereference operator
    T& operator*() 
    {
        return *ptr;
    }

};
