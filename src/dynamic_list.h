#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H


template<typename Type>
class DynamicList {
public:
    DynamicList() {
        reallocate(2);
    }

    ~DynamicList() {
        delete[] values;
    };

    void push_back(Type item) {
        if (m_size >= m_capacity) {
            reallocate(2 * m_capacity);
        }
        values[m_size++] = item;
    }

    size_t size() {
        return m_size;
    }


    Type& operator[](int index) {
        return values[index];
    }

private:
    void reallocate(size_t newCapacity) {
        Type* new_values = new Type[newCapacity];
        if (newCapacity < m_size) {
            m_size = newCapacity;
        }
        for (int i = 0; i < m_size; ++i) {
            new_values[i] = values[i];
        }
        delete[] values;
        m_capacity = newCapacity;
        values = new_values;
    }

private:
    size_t m_capacity = 0, m_size = 0;
    Type* values = nullptr;
};
#endif // DYNAMIC_LIST_H
