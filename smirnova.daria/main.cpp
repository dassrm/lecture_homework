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
    BiList<T>* head;
    BiList<T>* tail;

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    void push_front(const T& value) {
        BiList<T>* newNode = new BiList<T>{value, head, nullptr};
        if (empty()) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(const T& value) {
        BiList<T>* newNode = new BiList<T>{value, nullptr, tail};
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop_front() {
        if (empty()) return;
        BiList<T>* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (empty()) return;
        BiList<T>* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    T& front() {
        return head->val;
    }

    const T& front() const {
        return head->val;
    }

    T& back() {
        return tail->val;
    }

    const T& back() const {
        return tail->val;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void print() const {
        BiList<T>* current = head;
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
