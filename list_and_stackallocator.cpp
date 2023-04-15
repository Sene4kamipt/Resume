#include <iostream>

#include <type_traits>

#include <memory>

template <size_t N>
class StackStorage {
public:
    //deleting copy constructor
    StackStorage(const StackStorage & value) = default;
      
    template <typename T, size_t M>
    friend class StackAllocator;
        
    StackStorage():_stack_end(&_memory[0]){}
 
private:
    char _memory[N];
    char* _stack_end;
};

template <typename T, size_t N>
class StackAllocator {
private:
    StackStorage <N>* memory = nullptr;
public:
    template<size_t M>
    friend class StackStorage;

    template <typename U, size_t V>
    friend class StackAllocator;

    using value_type = T;

    template <typename U>
    struct rebind {
        using other = StackAllocator <U, N> ;
    };
    
    //default constructor
    //StackAllocator(): memory(StackStorage<N>()){}

    //copy constructor from StackAlloc
    template <typename U>
    StackAllocator(const StackAllocator <U, N>& stack_alloc): memory(stack_alloc.memory) {}

    //constructor of StackStorage
    StackAllocator (const StackStorage<N>& stack_storage): memory(const_cast<StackStorage<N>*>(&stack_storage)){}
    
    //destructor
    ~StackAllocator() {}

    template <typename U>
    StackAllocator& operator = (StackAllocator <U, N> stack_alloc) {
        memory = stack_alloc.memory;
        return *this;
    }

    T* allocate(size_t n) {
        memory -> _stack_end = ((size_t)(memory -> _stack_end) % alignof(T) == 0) ? (memory -> _stack_end) : ((memory -> _stack_end) + alignof(T) - ((size_t)(memory -> _stack_end) % alignof(T)));
        size_t move = sizeof(T) * n;
        memory->_stack_end += move;
        return reinterpret_cast<T*>(memory->_stack_end - move);
    }

    void deallocate(T*, size_t)const {}

    bool operator == (const StackAllocator& stack_alloc) const {
        return memory == stack_alloc.memory;
    }

    bool operator != (const StackAllocator& stack_alloc) const {
        return memory != stack_alloc.memory;
    }

    StackAllocator& select_on_container_copy_construction() {
        return *this;
    }
};

template <typename T, typename Alloc = std::allocator <T>>
class List {
public:
    class Base_node;
    class Node;
    class Base_node {
    public:
        Base_node* _prev = nullptr;
        Base_node* _next = nullptr;
    };

    class Node: public Base_node {
    public:
        T _value;

        Node(): Base_node(), _value(){}
        //constructor of _value
        Node (const T& _value): Base_node(),_value(_value){}
    };

    using Alloc_for_Node = typename Alloc::template rebind <Node> ::other;
    using Traits_for_Node = std::allocator_traits <Alloc_for_Node> ;
    using Traits_for_T = std::allocator_traits <Alloc> ;

    Base_node _start;
    size_t _sz;
    Alloc_for_Node _alloc;

public:

    List(): _start(Base_node()), _sz(0), _alloc(Alloc()) {
        _start._next =& _start;
        _start._prev =& _start;
        _iter_on_begin = List <T, Alloc> ::iterator (_start._next);
        _iter_on_end = List <T, Alloc> ::iterator (&_start);
    }

    List(size_t n): List() {
        for (size_t i = 0; i < n; ++i) {
            this -> push_back();
        }
    }

    List(size_t n, const T& value): List() {
        for (size_t i = 0; i < n; ++i) {
            this -> push_back(value);
        }
    }

    List(Alloc alloc): _start(), _sz(0), _alloc(Traits_for_T::select_on_container_copy_construction(alloc)) {
        _start._next = &_start;
        _start._prev = &_start;
        _iter_on_begin = List <T, Alloc> ::iterator (_start._next);
        _iter_on_end = List <T, Alloc> ::iterator (&_start);
    }

    List(size_t n, Alloc alloc): List(alloc) {
        for (size_t i = 0; i < n; ++i) {
            this -> push_back();
        }
    }

    List(size_t n,
        const T& value, Alloc alloc): List(alloc) {
        for (size_t i = 0; i < n; ++i) {
            this -> push_back(value);
        }
    }

    List(const List& list): _start(Base_node()), _sz(0), _alloc(Traits_for_T::select_on_container_copy_construction(list._alloc)) {
        _start._next = &_start;
        _start._prev = &_start;
        _iter_on_begin = List <T, Alloc> ::iterator (_start._next);
        _iter_on_end = List <T, Alloc> ::iterator (&_start);
        int k =0;
        try {
            for (auto& value: list) {
                this -> push_back(value);
                ++k;
            }
        } catch (...) {
            for (int i=0;i<k;++i){
                this->pop_back();
            }
            throw;
        }
      }

    ~List() {
        while (_sz != 0) {
            this -> pop_back();
        }
    }

    List& operator = (const List& list) {
        if (Traits_for_T::propagate_on_container_copy_assignment::value) {
            _alloc = list._alloc;
        }
        else {
            _alloc = Traits_for_T::select_on_container_copy_construction(list._alloc);
        }
        size_t _szk = this->size();
        int k = 0;
        try {
            for (auto& value: list) {
                this -> push_back(value);
                ++k;
            }
        } catch (...) {
            for (int i=0;i<k;++i){
                this->pop_back();
            }
            throw;
        }
        for (size_t i=0;i<_szk;++i){
            this->pop_front();
        }
        return *this;
    }

    Alloc_for_Node get_allocator() const {
        return _alloc;
    }

    size_t size() const {
        return _sz;
    }

    void push_back(const T& value) {
        Node* new_node = Traits_for_Node::allocate(_alloc, 1);
        try {
            Traits_for_Node::construct(_alloc, new_node, value);
        } catch (...) {
            //Traits_for_Node::destroy(alloc, new_node);
            Traits_for_Node::deallocate(_alloc, new_node, 1);
            throw;
        }
        new_node -> _next =& _start;
        new_node -> _prev = _start._prev;
        _start._prev = new_node;
        (new_node -> _prev) -> _next = new_node;
        if (_sz == 0) {
            _iter_on_begin = List <T, Alloc> ::iterator(_start._next);
        }
        ++_sz;
    }

    void push_back() {
        Node* new_node = Traits_for_Node::allocate(_alloc, 1);
        try {
            Traits_for_Node::construct(_alloc, new_node);
        } catch (...) {
            Traits_for_Node::deallocate(_alloc, new_node, 1);
        throw;
        }
        new_node -> _next = &_start;
        new_node -> _prev = _start._prev;
        _start._prev = new_node;
        (new_node -> _prev) -> _next = new_node;
        if (_sz == 0) {
            _iter_on_begin = List <T, Alloc> ::iterator (_start._next);
        }
        ++_sz;
    }

    void pop_back() {
        Node* del_node = static_cast<Node*>(_start._prev);
        _start._prev = del_node -> _prev;
        (del_node -> _prev) -> _next = &_start;
        Traits_for_Node::destroy(_alloc, del_node);
        Traits_for_Node::deallocate(_alloc, del_node, 1);
        --_sz;
        if (_sz == 0) {
            _iter_on_begin = List <T, Alloc> ::iterator (&_start);
        }
    }

    void push_front(const T& value) {
        Node* new_node = Traits_for_Node::allocate(_alloc, 1);
        try {
            Traits_for_Node::construct(_alloc, new_node, value);
        } catch (...) {
            Traits_for_Node::destroy(_alloc, new_node);
            Traits_for_Node::deallocate(_alloc, new_node, 1);
            throw;
        }
        new_node -> _next = _start._next;
        new_node -> _prev = &_start;
        _start._next = new_node;
        (new_node -> _next) -> _prev = new_node;
        ++_sz;
        _iter_on_begin = List <T, Alloc> ::iterator (_start._next);
    }

    void pop_front() {
        Node* del_node = static_cast<Node*>(_start._next);
        _start._next = del_node -> _next;
        (del_node -> _next) -> _prev = &_start;
        Traits_for_Node::destroy(_alloc, del_node);
        Traits_for_Node::deallocate(_alloc, del_node, 1);
        --_sz;
        _iter_on_begin = List <T, Alloc> ::iterator (_start._next);
    }

    public:
        template <bool constancy>
        struct Bidir_Iterator{
        private:
            Base_node* _pointer;
        public:
            friend class List <T, Alloc> ;

            using reference = std::conditional_t <constancy, const T& , T&> ;
            using pointer = std::conditional_t <constancy, const T* , T*> ;
            using value_type = std::conditional_t <constancy, const T, T> ;
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = int;
            using iterator_traits = std::iterator_traits <Bidir_Iterator <constancy>> ;

        Bidir_Iterator() = default;

        ~Bidir_Iterator() = default;

        Bidir_Iterator(Base_node * _pointer): _pointer(_pointer) {}

        Bidir_Iterator(const Bidir_Iterator<false>& iter): _pointer(iter._pointer){}

        Bidir_Iterator& operator = (const Bidir_Iterator <false>& iter) {
            _pointer = iter._pointer;
            return *this;
        }

        Bidir_Iterator& operator++() {
            _pointer = _pointer -> _next;
            return *this;
        }

        Bidir_Iterator operator++(int) {
            Bidir_Iterator answer = *this;
            ++(*this);
            return answer;
        }

        Bidir_Iterator& operator--() {
            _pointer = _pointer -> _prev;
            return *this;
        }

        Bidir_Iterator operator--(int) {
            Bidir_Iterator answer = *this;
            --(*this);
            return answer;
        }

        Bidir_Iterator& operator += (size_t value) {
            if (value > 0) {
                for (size_t i = 0; i < value; ++i) {
                    ++(*this);
            }
            } else {
                for (size_t i = 0; i < -value; ++i) {
                --(*this);
                }
            }
            return *this;
        }

        Bidir_Iterator& operator -= (int value) {
            return (*this += -value);
        }

        Bidir_Iterator operator + (int value) const {
            Bidir_Iterator copy = *this;
            return (copy += value);
        }

        Bidir_Iterator operator - (int value) const {
            Bidir_Iterator copy = *this;
            return (copy -= value);
        }

        bool operator == (const Bidir_Iterator& iter) const {
            return _pointer == iter._pointer;
        }

        bool operator != (const Bidir_Iterator& iter) const {
            return _pointer != iter._pointer;
        }   

        difference_type operator - (const Bidir_Iterator& iter) const {
            difference_type answer = 0;
            while (this != iter) {
                ++answer;
                --(*this);
            }
            return answer;
        }

        reference operator * () const {
            return static_cast<Node*>(_pointer) -> _value;
        }

        pointer operator -> () const {
            return &(_pointer -> _value);
        }
    };
public:
    using iterator = Bidir_Iterator<false> ;
    using const_iterator = Bidir_Iterator<true> ;
    using reverse_iterator = std::reverse_iterator<iterator> ;
    using const_reverse_iterator = std::reverse_iterator<const_iterator> ;

    iterator begin() const{
        return _iter_on_begin;
    }

    iterator end() const{
        return _iter_on_end;
    }

    const_iterator cbegin() const {
        const_iterator answer = _iter_on_begin;
        return answer;
    }

    const_iterator cend() const {
        const_iterator answer = _iter_on_end;
        return answer;
    }

    reverse_iterator rbegin() const{
        reverse_iterator answer(_start._prev);
        return --answer;
    }

    reverse_iterator rend() const{
        reverse_iterator answer(_iter_on_begin);
        return answer;
    }


    const_reverse_iterator crbegin() const {
        const_reverse_iterator answer(_start._prev);
        return answer;
    }

    const_reverse_iterator crend() const {
        const_reverse_iterator answer(_iter_on_begin);
        return answer;
    }

    void insert(const_iterator iter, const T& value) {
        Node* new_node = Traits_for_Node::allocate(_alloc, 1);
        Traits_for_Node::construct(_alloc, new_node, value);
        new_node -> _next = iter._pointer;
        new_node -> _prev = (iter._pointer) -> _prev;
        (iter._pointer) -> _prev -> _next = new_node;
        (iter._pointer) -> _prev = new_node;
        ++_sz;
    }

    void erase(const_iterator iter) {
        (iter._pointer) -> _prev -> _next = (iter._pointer) -> _next;
        (iter._pointer) -> _next -> _prev = (iter._pointer) -> _prev;
        Traits_for_Node::destroy(_alloc, iter._pointer);
        Traits_for_Node::deallocate(_alloc, static_cast<Node*>(iter._pointer), 1);
        --_sz;
    }
    private:
        List <T, Alloc> ::Bidir_Iterator <false> _iter_on_begin;
        List <T, Alloc> ::Bidir_Iterator <false> _iter_on_end;
};

