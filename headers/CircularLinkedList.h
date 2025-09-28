/* Lukyanova Angelina st128743@student.spbu.ru
 * Home assignment 7 - Circular list
 */
 #ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <cstddef> 
#include <stdexcept>
#include <iterator>
#include <algorithm>

template<typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), next(this), prev(this) {}
    };
    
    Node* head;
    size_t _size;

public:
    // Forward declarations
    class iterator;
    class const_iterator;

    // Constructors and Destructor
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& other);
    CircularLinkedList(CircularLinkedList&& other) noexcept;
    ~CircularLinkedList();
    
    // Operator=
    CircularLinkedList& operator=(const CircularLinkedList& other);
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept;
    
    // Capacity
    bool empty() const;
    size_t size() const;
    
    // Element access
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    
    // Modifiers
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void clear();
    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);
    void assign(size_t n, const T& value);
    void swap(CircularLinkedList& other) noexcept;
    
    // Iterators
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // Comparison operators
    bool operator==(const CircularLinkedList& other) const;
    bool operator!=(const CircularLinkedList& other) const;
    bool operator<(const CircularLinkedList& other) const;
    bool operator>(const CircularLinkedList& other) const;
    bool operator<=(const CircularLinkedList& other) const;
    bool operator>=(const CircularLinkedList& other) const;

    // Iterators classes
    class iterator {
    private:
        Node* current;
        Node* head;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node* n = nullptr, Node* s = nullptr) : current(n), head(s) {}
        
        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        
        friend class CircularLinkedList;
    };

    class const_iterator {
    private:
        Node* current;
        Node* head;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(Node* n = nullptr, Node* s = nullptr) : current(n), head(s) {}
        const_iterator(const iterator& it) : current(it.current), head(it.head) {}
        
        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
        
        friend class CircularLinkedList;
    };
};

// Realization

template<typename T>
CircularLinkedList<T>::CircularLinkedList() : head(nullptr), _size(0) {}

template<typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList& other) : head(nullptr), _size(0) {
     if (!other.empty()) {
        Node* otherCurrent = other.head;
        do {
            push_back(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        } while (otherCurrent != other.head);
    }
}

template<typename T>
CircularLinkedList<T>::CircularLinkedList(CircularLinkedList&& other) noexcept : head(other.head), _size(other._size) {
    other.head = nullptr;
    other._size = 0;
}

template<typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    clear();
}


//Operator=


template<typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList& other) {
    if (this != &other) {
        clear();
        
        if (!other.empty()) {
            Node* otherCurrent = other.head;
            do {
                push_back(otherCurrent->data);
                otherCurrent = otherCurrent->next;
            } while (otherCurrent != other.head);
        }
    }
    return *this;
}

template<typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(CircularLinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        
        head = other.head;
        _size = other._size;
        
        other.head = nullptr;
        other._size = 0;
    }
    return *this;
}

template<typename T>
bool CircularLinkedList<T>::empty() const {
    return _size == 0;
}

template<typename T>
size_t CircularLinkedList<T>::size() const {
    return _size;
}



template<typename T>
T& CircularLinkedList<T>::front() {
    if (empty()) throw std::out_of_range("CircularLinkedList::front: empty list");
    return head->data;
}

template<typename T>
const T& CircularLinkedList<T>::front() const {
    if (empty()) throw std::out_of_range("CircularLinkedList::front: empty list");
    return head->data;
}

template<typename T>
T& CircularLinkedList<T>::back() {
    if (empty()) throw std::out_of_range("CircularLinkedList::back: empty list");
    return head->prev->data;
}

template<typename T>
const T& CircularLinkedList<T>::back() const {
    if (empty()) throw std::out_of_range("CircularLinkedList::back: empty list");
    return head->prev->data;
}

template<typename T>
void CircularLinkedList<T>::push_front(const T& value) {
    push_back(value);
    head = head->prev;
}
template<typename T>
void CircularLinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = newNode;
    } else {
        Node* tail = head->prev;
        
        tail->next = newNode;
        newNode->prev = tail;
        
        newNode->next = head;
        head->prev = newNode;
    }
    _size++;
}

template<typename T>
void CircularLinkedList<T>::pop_front() {
    if (empty()) throw std::out_of_range("CircularLinkedList::pop_front: empty list");
    if (_size == 1) {
        delete head;
        head = nullptr;
    } else {
        Node* newHead = head->next;
        Node* tail = head->prev;
        newHead->prev = tail;
        tail->next = newHead;
        delete head;
        head = newHead;
    }
    _size--;
}

template<typename T>
void CircularLinkedList<T>::pop_back() {
    if (empty()) throw std::out_of_range("CircularLinkedList::pop_back: empty list");
    if (_size == 1) {
        delete head;
        head = nullptr;
    } else {
        Node* tail = head->prev;
        Node* newTail = tail->prev;
        
        newTail->next = head;
        head->prev = newTail;
        
        delete tail;
    }
    _size--;
}

template<typename T>
void CircularLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void CircularLinkedList<T>::assign(size_t n, const T& value) {
    clear();
    for (size_t i = 0; i < n; ++i) {
        push_back(value);
    }
}

template<typename T>
void CircularLinkedList<T>::swap(CircularLinkedList& other) noexcept {
    std::swap(head, other.head);
    std::swap(_size, other._size);
}

// Comparison operators
template<typename T>
bool CircularLinkedList<T>::operator==(const CircularLinkedList& other) const {
    if (size() != other.size()) return false;
    if (empty()) return true;
    auto it1 = begin();
    auto it2 = other.begin();
    while (it1 != end() && it2 != other.end()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }
    return it1 == end() && it2 == other.end();
}

template<typename T>
bool CircularLinkedList<T>::operator!=(const CircularLinkedList& other) const {
    return !(*this == other);
}

template<typename T>
bool CircularLinkedList<T>::operator<(const CircularLinkedList& other) const {
    if (empty() && other.empty()) return false;
    if (empty()) return true;
    if (other.empty()) return false;
    auto it1 = begin();
    auto it2 = other.begin();
    while (it1 != end() && it2 != other.end()) {
        if (*it1 < *it2) return true;
        if (*it2 < *it1) return false;
        ++it1;
        ++it2;
    }
    return it1 == end() && it2 != other.end();
}



template<typename T>
bool CircularLinkedList<T>::operator>(const CircularLinkedList& other) const {
    return other < *this;
}

template<typename T>
bool CircularLinkedList<T>::operator<=(const CircularLinkedList& other) const {
    return !(other < *this);
}

template<typename T>
bool CircularLinkedList<T>::operator>=(const CircularLinkedList& other) const {
    return !(*this < other);
}

// Iterators
template<typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::begin() {
    return iterator(head, head);
}

template<typename T>
typename CircularLinkedList<T>::iterator CircularLinkedList<T>::end() { ////
    return iterator(nullptr, head);
}


template<typename T>
typename CircularLinkedList<T>::const_iterator CircularLinkedList<T>::begin() const {
    return const_iterator(head, head);
}

template<typename T>
typename CircularLinkedList<T>::const_iterator CircularLinkedList<T>::end() const { ////
    return const_iterator(nullptr, head);
}




template<typename T>
typename CircularLinkedList<T>::const_iterator CircularLinkedList<T>::cbegin() const {
    return begin();
}

template<typename T>
typename CircularLinkedList<T>::const_iterator CircularLinkedList<T>::cend() const {
    return end();
}



template<typename T>
typename CircularLinkedList<T>::reverse_iterator CircularLinkedList<T>::rbegin() {
    return reverse_iterator(end());
}

template<typename T>
typename CircularLinkedList<T>::reverse_iterator CircularLinkedList<T>::rend() {
    return reverse_iterator(begin());
}



template<typename T>
typename CircularLinkedList<T>::const_reverse_iterator CircularLinkedList<T>::rbegin() const {
    return const_reverse_iterator(end());
}

template<typename T>
typename CircularLinkedList<T>::const_reverse_iterator CircularLinkedList<T>::rend() const {
    return const_reverse_iterator(begin());
}

template<typename T>
typename CircularLinkedList<T>::const_reverse_iterator CircularLinkedList<T>::crbegin() const {
    return rbegin();
}


template<typename T>
typename CircularLinkedList<T>::const_reverse_iterator CircularLinkedList<T>::crend() const {
    return rend();
}


template<typename T>
typename CircularLinkedList<T>::iterator::reference 
CircularLinkedList<T>::iterator::operator*() const {
    if (!current) throw std::out_of_range("Iterator: dereferencing end iterator");
    return current->data;
}

template<typename T>
typename CircularLinkedList<T>::iterator::pointer 
CircularLinkedList<T>::iterator::operator->() const {
    if (!current) throw std::out_of_range("Iterator: dereferencing end iterator");
    return &current->data;
}

template<typename T>
typename CircularLinkedList<T>::iterator& 
CircularLinkedList<T>::iterator::operator++() {
    if (!current) throw std::out_of_range("Iterator: incrementing end iterator");
    if (current) {
            current = current->next;
            if (current == head) {
                current = nullptr;
            }
        }
        return *this;
}

template<typename T>
typename CircularLinkedList<T>::iterator 
CircularLinkedList<T>::iterator::operator++(int) {
    if (!current) throw std::out_of_range("Iterator: incrementing end iterator");
    iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
typename CircularLinkedList<T>::iterator& 
CircularLinkedList<T>::iterator::operator--() {
    if (!current) {
            if (head) current = head->prev;
        } else {
            current = current->prev;
        }
        return *this;
}

template<typename T>
typename CircularLinkedList<T>::iterator 
CircularLinkedList<T>::iterator::operator--(int) {
    iterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool CircularLinkedList<T>::iterator::operator==(const iterator& other) const {
    return current == other.current;
}

template<typename T>
bool CircularLinkedList<T>::iterator::operator!=(const iterator& other) const {
    return current != other.current;
}

template<typename T>
typename CircularLinkedList<T>::const_iterator::reference 
CircularLinkedList<T>::const_iterator::operator*() const {
    if (!current) throw std::out_of_range("ConstIterator: dereferencing end iterator");
    return current->data;
}

template<typename T>
typename CircularLinkedList<T>::const_iterator::pointer
CircularLinkedList<T>::const_iterator::operator->() const {
    if (!current) throw std::out_of_range("ConstIterator: dereferencing end iterator");
    return &current->data;
}

template<typename T>
typename CircularLinkedList<T>::const_iterator& 
CircularLinkedList<T>::const_iterator::operator++() {
    if (!current) throw std::out_of_range("ConstIterator: incrementing end iterator");
    if (current) {
        current = current->next;
        if (current == head) {
            current = nullptr;
        }
    }
    return *this;
}

template<typename T>
typename CircularLinkedList<T>::const_iterator 
CircularLinkedList<T>::const_iterator::operator++(int) {
    if (!current) throw std::out_of_range("ConstIterator: incrementing end iterator");
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
typename CircularLinkedList<T>::const_iterator& 
CircularLinkedList<T>::const_iterator::operator--() {
    if (!current) {
            if (head) current = head->prev;
        } else {
            current = current->prev;
        }
        return *this;
}


template<typename T>
typename CircularLinkedList<T>::const_iterator 
CircularLinkedList<T>::const_iterator::operator--(int) {
    const_iterator temp = *this;
    --(*this);
    return temp;
}



template<typename T>
bool CircularLinkedList<T>::const_iterator::operator==(const const_iterator& other) const {
    return current == other.current;
}



template<typename T>
bool CircularLinkedList<T>::const_iterator::operator!=(const const_iterator& other) const {
    return current != other.current;
}

template<typename T>
typename CircularLinkedList<T>::iterator 
CircularLinkedList<T>::insert(iterator pos, const T& value) {
    if (empty()) {
        push_back(value);
        return iterator(head, head);
    }
    if (pos == end()) {
        push_back(value);
        return iterator(head->prev, head);
    }
    Node* newNode = new Node(value);
    Node* current = pos.current;
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    if (current == head) {
        head = newNode;
    }
    _size++;
    return iterator(newNode, head);
}


template<typename T>
typename CircularLinkedList<T>::iterator 
CircularLinkedList<T>::erase(iterator pos) {
    if (empty()) throw std::out_of_range("CircularLinkedList::erase: empty list");
    if (pos == end()) throw std::invalid_argument("CircularLinkedList::erase: cannot erase end iterator");
    Node* toDelete = pos.current;
    Node* nextNode = toDelete->next;
        if (_size == 1) {
        delete toDelete;
        head = nullptr;
        _size = 0;
        return end();
    }
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;
    if (toDelete == head) {
        head = head->next;
    }
    delete toDelete;
    _size--;
    if (empty()) return end();
    return iterator(nextNode, head);
}

#endif
