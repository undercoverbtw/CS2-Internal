#pragma once

namespace sdk {
    template <class T>
    class UtlVector {
    public:
        UtlVector() = default;

        T& operator[](const std::int32_t index) {
            return elements_[index];
        }

        T& get_element(std::int32_t index);

        const T& get_element(std::int32_t index) const;

        std::int32_t get_offset(const T& src) const;

        [[nodiscard]] std::int32_t get_size() const;

        std::int32_t add_to_head();

        std::int32_t add_to_head(const T& src);

        std::int32_t add_to_tail();

        std::int32_t add_to_tail(const T& src);

        std::int32_t insert_before(std::int32_t element);

        std::int32_t insert_before(std::int32_t element, const T& src);

        std::int32_t insert_after(std::int32_t element);

        std::int32_t insert_after(std::int32_t element, const T& src);

        void grow_vector(std::int32_t size = 1);

        void shift_elements_right(std::int32_t element, std::int32_t size = 1);

        void shift_elements_left(std::int32_t element, std::int32_t size = 1);

        void fast_remove(std::int32_t element);

        void remove(std::int32_t element);

        bool find_and_remove(const T& src);

        bool find_and_fast_remove(const T& src);

    private:
        std::int32_t size_{ 0 };

        T* elements_{ nullptr };
    };

    template <typename T>
    T& UtlVector<T>::get_element(const std::int32_t index) {
        return elements_[index];
    }

    template <typename T>
    const T& UtlVector<T>::get_element(const std::int32_t index) const {
        return elements_[index];
    }

    template <typename T>
    std::int32_t UtlVector<T>::get_offset(const T& src) const {
        for (std::int32_t index = 0; index < get_size(); ++index) {
            if (get_element(index) == src)
                return index;
        }

        return -1;
    }

    template <typename T>
    std::int32_t UtlVector<T>::get_size() const {
        return size_;
    }

    template <typename T>
    std::int32_t UtlVector<T>::add_to_head() {
        return insert_before(0);
    }

    template <typename T>
    std::int32_t UtlVector<T>::add_to_head(const T& src) {
        return insert_before(0, src);
    }

    template <typename T>
    std::int32_t UtlVector<T>::add_to_tail() {
        return insert_before(size_);
    }

    template <typename T>
    std::int32_t UtlVector<T>::add_to_tail(const T& src) {
        return insert_before(size_, src);
    }

    template <typename T>
    std::int32_t UtlVector<T>::insert_before(const std::int32_t element) {
        grow_vector();

        shift_elements_right(element);

        Construct(&get_element(element));

        return element;
    }

    template <typename T>
    std::int32_t UtlVector<T>::insert_before(const std::int32_t element, const T& src) {
        grow_vector();

        shift_elements_right(element);

        CopyConstruct(&get_element(element), src);

        return element;
    }

    template <typename T>
    std::int32_t UtlVector<T>::insert_after(const std::int32_t element) {
        return insert_before(element + 1);
    }

    template <typename T>
    std::int32_t UtlVector<T>::insert_after(const std::int32_t element, const T& src) {
        return insert_before(element + 1, src);
    }

    template <typename T>
    void UtlVector<T>::grow_vector(const std::int32_t size) {
        size_ += size;

        if (elements_)
            elements_ = static_cast<T*>(realloc(elements_, size_ * sizeof(T)));
        else
            elements_ = static_cast<T*>(malloc(size_ * sizeof(T)));
    }

    template <typename T>
    void UtlVector<T>::shift_elements_right(const std::int32_t element, const std::int32_t size) {
        if (const std::int32_t num_to_move = size_ - element - size; (num_to_move > 0) && (size > 0))
            memmove(&get_element(element + size), &get_element(element), num_to_move * sizeof(T));
    }

    template <typename T>
    void UtlVector<T>::shift_elements_left(const std::int32_t element, const std::int32_t size) {
        if (const std::int32_t num_to_move = size_ - element - size; (num_to_move > 0) && (size > 0)) {
            memmove(&get_element(element), &get_element(element + size), num_to_move * sizeof(T));

#ifdef _DEBUG
            memset(&get_element(size_ - size), 0xDD, size * sizeof(T));
#endif
        }
    }

    template <typename T>
    void UtlVector<T>::fast_remove(const std::int32_t element) {
        destruct(&get_element(element));

        if (size_ > 0) {
            if (element != size_ - 1)
                std::copy(&get_element(size_ - 1), &get_element(size_), &get_element(element));

            --size_;
        }
    }

    template <typename T>
    void UtlVector<T>::remove(const std::int32_t element) {
        destruct(&get_element(element));

        shift_elements_left(element);

        --size_;
    }

    template <typename T>
    bool UtlVector<T>::find_and_remove(const T& src) {
        if (const std::int32_t element = get_offset(src); element != -1) {
            remove(element);

            return true;
        }

        return false;
    }

    template <typename T>
    bool UtlVector<T>::find_and_fast_remove(const T& src) {
        if (const std::int32_t element = get_offset(src); element != -1) {
            fast_remove(element);

            return true;
        }

        return false;
    }
}