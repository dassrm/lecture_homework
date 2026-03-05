#include <iostream>

template <class T>
struct BiList {
    T val;
    BiList<T>* next;
    BiList<T>* prev;
};

template <typename T>
class List {
private:
    BiList<T>* fake;

public:
    List() {
        fake = new BiList<T>;
        fake->next = nullptr;
        fake->prev = nullptr;
    }
    
    ~List() {
        clear();
        delete fake;
    }

    bool empty() const {
        return fake->next == nullptr;
    }

    void push_front(const T& value) {
        BiList<T>* newNode = new BiList<T>{value, fake->next, nullptr};
        if (fake->next) {
            fake->next->prev = newNode;
        }
        fake->next = newNode;
        if (!fake->prev) {
            fake->prev = newNode;
        }
    }

    void push_back(const T& value) {
        BiList<T>* newNode = new BiList<T>{value, nullptr, fake->prev};
        if (fake->prev) {
            fake->prev->next = newNode;
        } else {
            fake->next = newNode;
        }
        fake->prev = newNode;
    }

    void pop_front() {
        if (empty()) return;
        BiList<T>* temp = fake->next;
        fake->next = temp->next;
        if (fake->next) {
            fake->next->prev = nullptr;
        } else {
            fake->prev = nullptr;
        }
        delete temp;
    }

    void pop_back() {
        if (empty()) return;
        BiList<T>* temp = fake->prev;
        fake->prev = temp->prev;
        if (fake->prev) {
            fake->prev->next = nullptr;
        } else {
            fake->next = nullptr;
        }
        delete temp;
    }

    T& front() {
        return fake->next->val;
    }

    const T& front() const {
        return fake->next->val;
    }

    T& back() {
        return fake->prev->val;
    }

    const T& back() const {
        return fake->prev->val;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void print() const {
        BiList<T>* current = fake->next;
        while (current) {
            std::cout << current->val << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

template <typename T>
List<T> arrayToList(const T* arr, size_t size) {
    List<T> lst;
    for (size_t i = 0; i < size; ++i) {
        lst.push_back(arr[i]);
    }
    return lst;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    List<int> myList = arrayToList(arr, size);

    std::cout << "Список из массива: ";
    myList.print();

    myList.push_front(5);
    myList.push_back(60);
    std::cout << "После push_front(5) и push_back(60): ";
    myList.print();

    myList.pop_front();
    myList.pop_back();
    std::cout << "После pop_front() и pop_back(): ";
    myList.print();

    return 0;
}
