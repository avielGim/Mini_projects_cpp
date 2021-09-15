#pragma once

#include <iostream>

// using namespace std;

namespace ariel{
    template<typename T>
    class BinaryTree{
        struct Node{
            T value;
            Node* right;
            Node* left;
            Node* fath;

            Node(T v) 
                : value(v), fath(nullptr), right(nullptr), left(nullptr) {}
        };
    public:
        /* preOrder: root -> left -> right */
        class preIterator {
            Node* _pointer;
        public:
            preIterator(Node* ptr = nullptr)
                : _pointer(ptr) {}

            T& operator*() const {return _pointer->value;}

            T* operator->() const {return &(_pointer->value);}

            preIterator& operator++() {
                if(_pointer == nullptr){
                    throw std::invalid_argument("can't move forward at preIterator");
                }
                if(_pointer->left != nullptr){     // if there is a left son - go left
                    _pointer = _pointer->left;
                    return *this;
                }
                if(_pointer->right != nullptr){    // if there is a right son - go right
                    _pointer = _pointer->right;
                    return *this;
                }
                if(_pointer->fath != nullptr){      // if there is a father 
                    Node* temp = _pointer->fath;    // go to the father
                    Node* son = _pointer;
                    while(temp->fath != nullptr){  // and find his next right son
                        if(temp->left == son && temp->right != nullptr){
                            _pointer = temp->right;
                            return *this;
                        }
                        son = temp;
                        temp = temp->fath;
                    }
                    if(temp->left == son && temp->right != nullptr){
                        _pointer = temp->right;
                        return *this;
                    }
                }
                _pointer = nullptr;
                return *this;
            }

            preIterator operator++(int) {
                preIterator tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const preIterator& rhs) const {
                return (_pointer == rhs._pointer);
            }

            bool operator!=(const preIterator& rhs) const {
                return (_pointer != rhs._pointer);
            }
        };

        /* inorder - left -> root -> right */
        class inIterator {
            Node* _pointer;
        public:
            inIterator(Node* ptr = nullptr)
                : _pointer(ptr){}

            T& operator*() const {return _pointer->value;}

            T* operator->() const {return &(_pointer->value);}

            inIterator& operator++() {
                if(_pointer == nullptr){
                    throw std::invalid_argument("can't move forward at inIterator");
                }
                if(_pointer->right != nullptr){        // if there is a right son - go right
                    Node* temp = _pointer->right;
                    while(temp->left != nullptr){      // and if to the right son hes left son - go left
                        temp = temp->left;
                    }
                    _pointer = temp;
                    return *this;
                }
                if(_pointer->fath != nullptr){         // if there is a father
                    Node* temp = _pointer->fath;       // go to the father
                    Node* son = _pointer;
                    while(temp->right == son && temp->fath != nullptr){      // if the current pointer is a right son 
                        son = temp;                                          // go to the father
                        temp = temp->fath;
                    }
                    if(temp->left == son){      // if the current son is a left son - return his father
                        _pointer = temp;
                        return *this;
                    }
                }
                _pointer = nullptr;
                return *this;
            }

            inIterator operator++(int) {
                inIterator tmp= *this;
                ++*this;
                return tmp;
            }

            bool operator==(const inIterator& rhs) const {
                return _pointer == rhs._pointer;
            }

            bool operator!=(const inIterator& rhs) const {
                return _pointer != rhs._pointer;
            }
        };

        /* inorder - left -> root -> right */
        class const_inIterator {
            Node* _pointer;
        public:
            const_inIterator(Node* ptr = nullptr)
                : _pointer(ptr){}

            const T& operator*() const {return _pointer->value;}

            const T* operator->() const {return &(_pointer->value);}

            const_inIterator& operator++() {
                if(_pointer == nullptr){
                    throw std::invalid_argument("can't move forward at inIterator");
                }
                if(_pointer->right != nullptr){        // if there is a right son - go right
                    Node* temp = _pointer->right;
                    while(temp->left != nullptr){      // and if to the right son hes left son - go left
                        temp = temp->left;
                    }
                    _pointer = temp;
                    return *this;
                }
                if(_pointer->fath != nullptr){         // if there is a father
                    Node* temp = _pointer->fath;       // go to the father
                    Node* son = _pointer;
                    while(temp->right == son && temp->fath != nullptr){      // if the current pointer is a right son 
                        son = temp;                                          // go to the father
                        temp = temp->fath;
                    }
                    if(temp->left == son){      // if the current son is a left son - return his father
                        _pointer = temp;
                        return *this;
                    }
                }
                _pointer = nullptr;
                return *this;
            }

            const_inIterator operator++(int) {
                inIterator tmp= *this;
                ++*this;
                return tmp;
            }

            bool operator==(const const_inIterator& rhs) const {
                return _pointer == rhs._pointer;
            }

            bool operator!=(const const_inIterator& rhs) const {
                return _pointer != rhs._pointer;
            }
        };
        
        /* postOrder:  left -> right -> root */
        class postIterator {
            Node* _pointer;
        public:
            postIterator(Node* ptr = nullptr)
                : _pointer(ptr) {}

            T& operator*() const {
                return _pointer->value;
            }

            T* operator->() const {
                return &(_pointer->value);
            }

            postIterator& operator++() {
                if(_pointer == nullptr){
                    throw std::invalid_argument("can't move forward at postIterator");
                }
                if(_pointer->fath != nullptr){        // if the current pointer is not the root of the tree
                    Node* temp = _pointer->fath;
                    if(temp->left == _pointer){
                        while(temp->right != nullptr){     // while has right son - go right
                            temp = temp->right;
                            while(temp->left != nullptr){  // while the right son has left son - go left
                                temp = temp->left;
                            }
                        }
                        _pointer = temp;
                        return *this;
                    }
                    _pointer = temp;
                    return *this;

                }
                _pointer = nullptr;
                return *this;
            }

            postIterator operator++(int) {
                postIterator tmp= *this;
                ++*this;
                return tmp;
            }

            bool operator==(const postIterator& rhs) const {
                return _pointer == rhs._pointer;
            }

            bool operator!=(const postIterator& rhs) const {
                return _pointer != rhs._pointer;
            }
        };

    private:
        Node* _head;

        void clean(Node* node){
            if(node != nullptr){
                clean(node->left);
                clean(node->right);
                delete node;
            }
        }

        Node* find_node(const T& find, Node* node){
            if(node != nullptr){
                if(node->value == find){
                    return node;
                }
                Node* next = find_node(find, node->left);
                if(next == nullptr){
                    next = find_node(find, node->right);;
                }
                return next;
            }
            return nullptr;
        }
        
        void create_node(Node* curr, Node* other){
            if(other->left != nullptr){
                curr->left = new Node{other->left->value};
                curr->left->fath = curr;
                create_node(curr->left, other->left);
            }
            if(other->right != nullptr){
                curr->right = new Node{other->right->value};
                curr->right->fath = curr;
                create_node(curr->right, other->right);
            }
        }

    public:
        /* defualt Constructor */
        BinaryTree(): _head(nullptr){}

        /* Copy Constructor */
        BinaryTree(const BinaryTree& other) {
            _head = new Node{other._head->value};
            create_node(_head, other._head);
        }

        /* Copy move Constructor */
        BinaryTree(BinaryTree && other) noexcept{
            _head = other._head;
            other._head = nullptr;
        }

        /* Destructor */
        ~BinaryTree() { 
            clean(_head);
        }

        BinaryTree& add_root(const T& root) {
            if(_head == nullptr){
                _head = new Node(root);
            }
            else{
                _head->value = root;
            }
            return *this;
        }

        BinaryTree& add_left(const T& father, const T& son) {  
            Node* temp = find_node(father, _head);
            if(temp == nullptr){
                throw std::invalid_argument{"the father is not found"};
        
            }
            if(temp->left != nullptr){
                temp->left->value = son;
            }
            else{  //create a new node
                Node* hijo = new Node{son};
                temp->left = hijo;
                hijo->fath = temp;
            }
            return *this;
        }

        BinaryTree& add_right(const T& father, const T& son) {
            Node* temp = find_node(father, _head);
            if(temp == nullptr){
                throw std::invalid_argument{"the father is not found"};
        
            }
            if(temp->right != nullptr){
                temp->right->value = son;
            }
            else{  //create a new node
                Node* hijo = new Node{son};
                temp->right = hijo;
                hijo->fath = temp;
            }
            return *this;
        }

        /*start from the root*/
        preIterator begin_preorder(){          
            return preIterator{_head};
        }
        preIterator end_preorder(){
            return preIterator{nullptr};
        }

        /* start from the most left node in the tree */
        inIterator begin_inorder(){ 
            if(_head == nullptr){
                return inIterator{nullptr};
            }
            Node* temp = _head;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            return inIterator{temp};
        }
        inIterator end_inorder(){
            return inIterator{nullptr};
        }
        /* start from the most left node in the tree */
        inIterator begin(){
            if(_head == nullptr){
                return inIterator{nullptr};
            }
            Node* temp = _head;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            return inIterator{temp};
        }
        inIterator end(){
            return inIterator{nullptr};
        }

        /* const inOrder iterator */
        const_inIterator cbegin() const {
            if(_head == nullptr){
                return const_inIterator{nullptr};
            }
            Node* temp = _head;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            return const_inIterator{temp};
        }
        const_inIterator cend() const {
            return const_inIterator{nullptr};
        }

        /* start from the most left node in the tree 
         * if get a node that has no left son 
         * than start from the right son. 
         */
        postIterator begin_postorder(){
            if(_head == nullptr){
                return postIterator{nullptr};    
            }
            Node* temp = _head;
            while(true){
                if(temp->left != nullptr){
                    temp = temp->left;
                }
                else if(temp->right != nullptr){
                    temp = temp->right;
                }
                else{
                    return postIterator{temp};
                }
            }
            return postIterator{nullptr};
            
        }
        postIterator end_postorder(){
            return postIterator{nullptr};
        }

        /* operator= - deep Copy */
        BinaryTree<T>& operator=(const BinaryTree<T>& other){
            if(this != &other){
                clean(_head);
                _head = new Node{other._head->value};
                create_node(_head, other._head);
            }
            return *this;
        }

        /* operator= move */
        BinaryTree& operator=(BinaryTree && other) noexcept{
            if(_head != nullptr && _head != other._head){
                clean(_head);
            }
            _head = other._head;
            other._head = nullptr;
            return *this;
        }

        /* print the BinaryTree */
        friend std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& tree){
            out << "\n\n--------------BINARY TREE---------------\n\t";
            for (auto element = tree.cbegin(); element!=tree.cend(); ++element){
                out << *element << " -> " ;
            }
            out << "\n**********  FINISH PRINTING!  **********\n";
            return out;
        }
    };

}