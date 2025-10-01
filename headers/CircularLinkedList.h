/* Lukyanova Angelina st128743@student.spbu.ru
 * Home assignment 7 - Circular list
 */
#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <cstddef> 
#include <stdexcept>
#include <iterator>
#include <algorithm>

/**
 * \class CircularLinkedList
 * \brief Template class for circular doubly linked list
 * \tparam T Type of elements in the list
 */
template<typename T>
class CircularLinkedList {
private:
    /**
     * \struct Node
     * \brief Internal node structure of the list
     */
    struct Node {
        T data;         ///< Node data
        Node* next;     ///< Pointer to next node
        Node* prev;     ///< Pointer to previous node
        
        /**
         * \brief Node constructor
         * \param value Value for the node
         */
        Node(const T& value) : data(value), next(this), prev(this) {}
    };
    
    Node* head;     ///< Pointer to the head element of the list
    size_t _size;   ///< Number of elements in the list

public:
    // Forward declarations
    class iterator;
    class const_iterator;

    // Constructors and destructor
    /**
     * \brief Default constructor
     */
    CircularLinkedList();
    
    /**
     * \brief Copy constructor
     * \param other List to copy from
     */
    CircularLinkedList(const CircularLinkedList& other);
    
    /**
     * \brief Move constructor
     * \param other List to move from
     */
    CircularLinkedList(CircularLinkedList&& other) noexcept;
    
    /**
     * \brief Destructor
     */
    ~CircularLinkedList();
    
    // Assignment operators
    /**
     * \brief Copy assignment operator
     * \param other List to copy from
     * \return Reference to current object
     */
    CircularLinkedList& operator=(const CircularLinkedList& other);
    
    /**
     * \brief Move assignment operator
     * \param other List to move from
     * \return Reference to current object
     */
    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept;
    
    // Capacity
    /**
     * \brief Check if list is empty
     * \return true if list is empty, false otherwise
     */
    bool empty() const;
    
    /**
     * \brief Get number of elements
     * \return Number of elements in the list
     */
    size_t size() const;
    
    // Element access
    /**
     * \brief Access first element
     * \return Reference to first element
     * \throw std::out_of_range if list is empty
     */
    T& front();
    
    /**
     * \brief Access last element
     * \return Reference to last element
     * \throw std::out_of_range if list is empty
     */
    T& back();
    
    /**
     * \brief Const access to first element
     * \return Const reference to first element
     * \throw std::out_of_range if list is empty
     */
    const T& front() const;
    
    /**
     * \brief Const access to last element
     * \return Const reference to last element
     * \throw std::out_of_range if list is empty
     */
    const T& back() const;
    
    // Modifiers
    /**
     * \brief Add element to the beginning
     * \param value Value to add
     */
    void push_front(const T& value);
    
    /**
     * \brief Add element to the end
     * \param value Value to add
     */
    void push_back(const T& value);
    
    /**
     * \brief Remove first element
     * \throw std::out_of_range if list is empty
     */
    void pop_front();
    
    /**
     * \brief Remove last element
     * \throw std::out_of_range if list is empty
     */
    void pop_back();
    
    /**
     * \brief Clear the list
     */
    void clear();
    
    /**
     * \brief Insert element before position
     * \param pos Iterator to position for insertion
     * \param value Value to insert
     * \return Iterator to inserted element
     */
    iterator insert(iterator pos, const T& value);
    
    /**
     * \brief Remove element at position
     * \param pos Iterator to position for removal
     * \return Iterator to next element
     * \throw std::out_of_range if list is empty
     * \throw std::invalid_argument if pos = end()
     */
    iterator erase(iterator pos);
    
    /**
     * \brief Replace list content
     * \param n Number of elements
     * \param value Value to fill with
     */
    void assign(size_t n, const T& value);
    
    /**
     * \brief Swap content with another list
     * \param other Another list to swap with
     */
    void swap(CircularLinkedList& other) noexcept;
    
    // Iterators
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /**
     * \brief Iterator to beginning of list
     * \return Iterator to first element
     */
    iterator begin();
    
    /**
     * \brief Iterator to end of list
     * \return Iterator to position after last element
     */
    iterator end();
    
    /**
     * \brief Const iterator to beginning of list
     * \return Const iterator to first element
     */
    const_iterator begin() const;
    
    /**
     * \brief Const iterator to end of list
     * \return Const iterator to position after last element
     */
    const_iterator end() const;
    
    /**
     * \brief Const iterator to beginning of list
     * \return Const iterator to first element
     */
    const_iterator cbegin() const;
    
    /**
     * \brief Const iterator to end of list
     * \return Const iterator to position after last element
     */
    const_iterator cend() const;
    
    /**
     * \brief Reverse iterator to beginning of reversed list
     * \return Reverse iterator to last element
     */
    reverse_iterator rbegin();
    
    /**
     * \brief Reverse iterator to end of reversed list
     * \return Reverse iterator to position before first element
     */
    reverse_iterator rend();
    
    /**
     * \brief Const reverse iterator to beginning of reversed list
     * \return Const reverse iterator to last element
     */
    const_reverse_iterator rbegin() const;
    
    /**
     * \brief Const reverse iterator to end of reversed list
     * \return Const reverse iterator to position before first element
     */
    const_reverse_iterator rend() const;
    
    /**
     * \brief Const reverse iterator to beginning of reversed list
     * \return Const reverse iterator to last element
     */
    const_reverse_iterator crbegin() const;
    
    /**
     * \brief Const reverse iterator to end of reversed list
     * \return Const reverse iterator to position before first element
     */
    const_reverse_iterator crend() const;

    // Comparison operators
    /**
     * \brief Equality operator
     * \param other Another list to compare with
     * \return true if lists are equal
     */
    bool operator==(const CircularLinkedList& other) const;
    
    /**
     * \brief Inequality operator
     * \param other Another list to compare with
     * \return true if lists are not equal
     */
    bool operator!=(const CircularLinkedList& other) const;
    
    /**
     * \brief Less than operator
     * \param other Another list to compare with
     * \return true if current list is less than other
     */
    bool operator<(const CircularLinkedList& other) const;
    
    /**
     * \brief Greater than operator
     * \param other Another list to compare with
     * \return true if current list is greater than other
     */
    bool operator>(const CircularLinkedList& other) const;
    
    /**
     * \brief Less than or equal operator
     * \param other Another list to compare with
     * \return true if current list is less than or equal to other
     */
    bool operator<=(const CircularLinkedList& other) const;
    
    /**
     * \brief Greater than or equal operator
     * \param other Another list to compare with
     * \return true if current list is greater than or equal to other
     */
    bool operator>=(const CircularLinkedList& other) const;

    /**
     * \class CircularLinkedList::iterator
     * \brief Iterator for CircularLinkedList
     */
    class iterator {
    private:
        Node* current;  ///< Current node
        Node* head;     ///< Head of the list (for end detection)
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * \brief Iterator constructor
         * \param n Current node
         * \param s Head of the list
         */
        iterator(Node* n = nullptr, Node* s = nullptr) : current(n), head(s) {}
        
        /**
         * \brief Dereference operator
         * \return Reference to current node's data
         * \throw std::out_of_range if iterator is invalid
         */
        reference operator*() const;
        
        /**
         * \brief Member access operator
         * \return Pointer to current node's data
         * \throw std::out_of_range if iterator is invalid
         */
        pointer operator->() const;
        
        /**
         * \brief Prefix increment
         * \return Reference to incremented iterator
         * \throw std::out_of_range if iterator is invalid
         */
        iterator& operator++();
        
        /**
         * \brief Postfix increment
         * \return Iterator before increment
         * \throw std::out_of_range if iterator is invalid
         */
        iterator operator++(int);
        
        /**
         * \brief Prefix decrement
         * \return Reference to decremented iterator
         */
        iterator& operator--();
        
        /**
         * \brief Postfix decrement
         * \return Iterator before decrement
         */
        iterator operator--(int);
        
        /**
         * \brief Equality comparison
         * \param other Another iterator to compare with
         * \return true if iterators are equal
         */
        bool operator==(const iterator& other) const;
        
        /**
         * \brief Inequality comparison
         * \param other Another iterator to compare with
         * \return true if iterators are not equal
         */
        bool operator!=(const iterator& other) const;
        
        friend class CircularLinkedList;
    };

    /**
     * \class CircularLinkedList::const_iterator
     * \brief Const iterator for CircularLinkedList
     */
    class const_iterator {
    private:
        Node* current;  ///< Current node
        Node* head;     ///< Head of the list (for end detection)
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /**
         * \brief Const iterator constructor
         * \param n Current node
         * \param s Head of the list
         */
        const_iterator(Node* n = nullptr, Node* s = nullptr) : current(n), head(s) {}
        
        /**
         * \brief Conversion constructor from regular iterator
         * \param it Iterator to convert from
         */
        const_iterator(const iterator& it) : current(it.current), head(it.head) {}
        
        /**
         * \brief Dereference operator
         * \return Const reference to current node's data
         * \throw std::out_of_range if iterator is invalid
         */
        reference operator*() const;
        
        /**
         * \brief Member access operator
         * \return Const pointer to current node's data
         * \throw std::out_of_range if iterator is invalid
         */
        pointer operator->() const;
        
        /**
         * \brief Prefix increment
         * \return Reference to incremented iterator
         * \throw std::out_of_range if iterator is invalid
         */
        const_iterator& operator++();
        
        /**
         * \brief Postfix increment
         * \return Iterator before increment
         * \throw std::out_of_range if iterator is invalid
         */
        const_iterator operator++(int);
        
        /**
         * \brief Prefix decrement
         * \return Reference to decremented iterator
         */
        const_iterator& operator--();
        
        /**
         * \brief Postfix decrement
         * \return Iterator before decrement
         */
        const_iterator operator--(int);
        
        /**
         * \brief Equality comparison
         * \param other Another iterator to compare with
         * \return true if iterators are equal
         */
        bool operator==(const const_iterator& other) const;
        
        /**
         * \brief Inequality comparison
         * \param other Another iterator to compare with
         * \return true if iterators are not equal
         */
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
