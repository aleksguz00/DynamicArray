#include <iostream>
#include <memory>
#include <initializer_list>
#include <algorithm>

template <class T>
class DynamicArray {
public:
    DynamicArray() : arr_{ nullptr }, size_{ 0 } {}
    DynamicArray(const size_t size) : arr_{ std::make_unique<T[]>(size) }, size_{ size } {}
    DynamicArray(const std::initializer_list<T>& arr) :
        DynamicArray(arr.size()) {
            std::copy(arr.begin(), arr.end(), arr_.get());
        }

    // DynamicArray(const DynamicArray& other) : size_{ other.size_ } {
    //     arr_ = new T[size_];

    //     for (size_t i = 0; i < other.size_; ++i) {
    //         arr_[i] = other.arr_[i];
    //     }
    // }

    DynamicArray(DynamicArray&& other) noexcept :
        size_{ other.size_ }, arr_{ std::move(other.arr_) } {
            other.size_ = 0;
        }

    ~DynamicArray() {
        size_ = 0;
    }

    // DynamicArray& operator=(DynamicArray& other) {
    //     if (this == &other) return *this;

    //     if (arr_ != nullptr ) {
    //         delete[] arr_;
    //     }
        
    //     arr_ = nullptr;

    //     size_ = other.size_;
    //     arr_ = new T[size_];

    //     for (size_t i = 0; i < size_; ++i) {
    //         arr_[i] = other.arr_[i];
    //     }

    //     return *this;
    // }

    DynamicArray& operator=(DynamicArray&& other) {
        if (this == &other) return *this;

        size_ = other.size_;
        arr_ = std::move(other.arr_);

        other.size_ = 0;

        return *this;
    }

    void PushFront(const T value) {
        auto temp_arr = std::make_unique<T[]>(size_ + 1);

        for (size_t i = 1; i < size_ + 1; ++i) {
            temp_arr[i] = arr_[i - 1];
        }
        temp_arr[0] = value;

        arr_ = std::move(temp_arr);

        ++size_;
    }

    void PushBack(const T value) {
        auto temp_arr = std::make_unique<T[]>(size_ + 1);

        for (size_t i = 0; i < size_; ++i) {
            temp_arr[i] = arr_[i];
        }
        temp_arr[size_] = value;

        // delete[] arr_;
        arr_ = std::move(temp_arr);
        // temp_arr = nullptr;

        ++size_;
    }

    void Insert(const size_t index, const T value) {
        if (index >= 0 && index <= size_) {
            auto temp_arr = std::make_unique<T[]>(size_ + 1);

            for (size_t i = 0; i < index; ++i) {
                temp_arr[i] = arr_[i];
            }

            temp_arr[index] = value;

            for (size_t i = index + 1; i < size_ + 1; ++i) {
                temp_arr[i] = arr_[i - 1];
            }

            // delete[] arr_;
            arr_ = std::move(temp_arr);
            // temp_arr = nullptr;

            ++size_;
        }
        else {
            std::cout << "Out of range!\n";
            return;
        } 
    }

    void PopFront() {
        auto temp_arr = std::make_unique<T[]>(size_ - 1);

        for (size_t i = 1; i < size_; ++i) {
            temp_arr[i - 1] = arr_[i];
        }

        // delete[] arr_;
        arr_ = std::move(temp_arr);
        // temp_arr = nullptr;

        --size_;
    }

    void PopBack() {
        auto temp_arr = std::make_unique<T[]>(size_ - 1);

        for (size_t i = 0; i < size_ - 1; ++i) {
            temp_arr[i] = arr_[i];
        }

        // delete[] arr_;
        arr_ = std::move(temp_arr);
        // temp_arr = nullptr;

        --size_;
    }

    void Remove(T element) {
        auto temp_arr = std::make_unique<T[]>(size_ - 1);

        int index = LinearSearch_(element);

        if (index >= 0) {
            for (size_t i = 0; i < index; ++i) {
                temp_arr[i] = arr_[i];
            }

            for (size_t i = index; i < size_ - 1; ++i) {
                temp_arr[i] = arr_[i + 1];
            }

            --size_;

            // delete[] arr_;
            arr_ = std::move(temp_arr);
            // temp_arr = nullptr;
        }
        else {
            std::cout << "There is no such an element\n";
        }
    }

    T& At(const size_t index) {
        if (index >= 0 && index < size_) {
            return arr_[index];
        }
        else {
            throw std::out_of_range("Out of range\n");
        }
    }

    bool Search(T element) const {
        if (LinearSearch_(element) >= 0) return true;
        else return false;
    }

    void Print() const {
        for (size_t i = 0; i < size_; ++i) {
            std::cout << arr_[i] << ' ';
        }
        std::cout << '\n';
    }

    size_t Size() const {
        return size_;
    }

    T& operator[](const size_t index) {
        if (index >= 0 && index < size_) {
            return arr_[index];
        }
        else {
            throw std::out_of_range("Out of range!\n");
        }
    }

    const T& operator[](const size_t index) const {
        if (index >= 0 && index < size_) {
            return arr_[index];
        }
        else {
            throw std::out_of_range("Out of range!\n");
        }
    }

private:    
    std::unique_ptr<T[]> arr_;
    size_t size_;

    int LinearSearch_(const T element) {
        int index = 0;

        while (index < size_) {
            if (arr_[index] == element) return index;
            ++index;
        }

        return -1;
    }
};

int main() {
    DynamicArray<int> arr{ 3, 1, 4, 1, 5, 9, 2, 6 };
    
    arr.Print();

    arr.PopFront();
    arr.Print();

    arr.PopBack();
    arr.Print();

    arr.Remove(9);
    arr.Print();
}
