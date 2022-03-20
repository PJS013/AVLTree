#pragma once

#ifndef AVL_HPP
#define AVL_HPP

template <typename Key, typename Info>
class Dictionary { // AVL tree
private:
    struct Node {
        Key key;
        Info info;
        int balance_factor;
        Node* left;
        Node* right;
        Node(const Key& vKey, const Info& vInfo, int bf=0, Node* vleft=nullptr, Node* vright=nullptr) :
            key(vKey),
            info(vInfo),
            balance_factor(bf),
            left(vleft),
            right(vright) {}
    };
    Node* root;

    //Rotations
    Node* llrotation(Node* n);
    Node* lrrotation(Node* n);
    Node* rrrotation(Node* n);
    Node* rlrotation(Node* n);

    Node* lrotation(Node* n);
    Node* rrotation(Node* n);

    void update(Node* n); //method that changes the balance factor value at node n
    Node* balance(Node* n); //method balancing the tree
    Node* insertIntoDictionary(const Key& key, const Info& val, Node* n);  //method inserting new node into tree

    void clearTree(Node* n); //method to clear the tree
    Node* remove(const Key& key, Node* n); //method to remove a node specified by key from the tree
    bool contain(const Key& key, Node* n) const; //method that checks whether a specific node exists in the tree
    Node* copy(Node* n); //method to copy the tree
    Node* height(Node* n); //calculate height of tree (or subtree)

    void printGraph(int width, Node* n) const; //method that prints the graph

    //getters
    Node* getNode(const Key& key, Node* n) const;
    Key& getMaximalNode(Node* n) const {
        if(!n->right)
            return n->key;
        return getMaximalNode(n->right);
    }
    Key& getMinimalNode(Node* n) const {
        if(!n->left)
            return n->key;
        return getMinimalNode(n->left);
    }

    //method that writes data from tree to ring
    void pushIntoRing(Ring<Info, Key>& ring, bool direction, Node* n);

public:
    class Iterator;
    Dictionary() {
        root=nullptr;
    } //constructor
    Dictionary(const Dictionary& src) { //copy constructor
        this->root = copy(src.root);
    }
    ~Dictionary() { //destructor
        clearTree(root);
    }
    bool isEmpty() const; //method checking if the tree is empty
    bool insertIntoDictionary(const Key& key, const Info& info); //method that inserts a node into the tree, calls private method insertIntoDictionary()

    void clearTree(); //method that clears tree, calls private method clearTree()
    void remove(const Key& key); //method to remove a specific node from the tree, calls private function remove()
    bool contain(const Key& key) const { //method checking, whether a specific node exists in the tree
        if(!root)
            return 0;
        return contain(key, root);
    }
    int height() const; //method calculating the height of tree, calls private method height()

    void printGraph() const { //method to print graph
    if(!root)
        std::cout<<"The tree is empty"<<std::endl;
    else {
        std::cout<<"============================================================="<<std::endl;
        printGraph(0, root);
        std::cout<<"============================================================="<<std::endl;
    }
    }
    Dictionary& operator=(const Dictionary& rhs); //operator of assignment

    //getters
    Info& getInfo(const Key& key) const {
        if(!root)
            throw "No data in the tree, unable to find node";
        return getNode(key, root)->info;
    }
    void setInfo(const Key& key, Key& x) {
        if(!root)
            return;
        getNode(key, root)->info=x;
    }
    Key& getMinimalNode() {
        if(!root)
            throw "No data in the tree, unable to find node";
        return getMinimalNode(root);
    }
    Key& getMaximalNode() {
        if(!root)
            throw "No data in the tree, unable to find node";
        return getMaximalNode(root);
    }
    //sets iterator to the beginning of the tree (root)
    Iterator begin();
    //method that writes data from tree to ring
    void pushIntoRing(Ring<Info, Key>& ring, bool direction);

};

template <typename Key, typename Info>
class Dictionary<Key, Info>::Iterator {
    friend class Dictionary<Key, Info>;

private:
    Node* it;

public:
    Iterator();
    ~Iterator();
    Iterator(const Iterator&);
    Iterator(Node*);

    bool right();
    bool left();

    Iterator& operator=(const Iterator&);
    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
    Key& getKey();
    Info& getInfo();
    Key& operator*();
};

template<typename Key, typename Info>
Dictionary<Key, Info>::Iterator::Iterator() {
    this->it=nullptr;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::Iterator::~Iterator() {
    this->it=nullptr;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::Iterator::Iterator(const Iterator& iter) {
    this->it=iter.it;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::Iterator::Iterator(Node* node) {
    this->it=node;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::right() {
    if(this->it == nullptr)
        return false;

    it=it->right;
    return true;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::left() {
    if(this->it == nullptr)
        return false;

    it=it->left;
    return true;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator& Dictionary<Key, Info>::Iterator::operator=(const Iterator& iter) {
    this->it = iter.it;
    return *this;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::operator==(const Iterator& iter){
    return (this->it==iter.it);
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::operator!=(const Iterator& iter) {
    return (this->it!=iter.it);
}

template<typename Key, typename Info>
Key& Dictionary<Key, Info>::Iterator::getKey() {
    if(!it)
        throw "No iterator";
    return it->key;
}

template<typename Key, typename Info>
Info& Dictionary<Key, Info>::Iterator::getInfo() {
    if(!it)
        throw "No iterator";
    return it->info;
}

template<typename Key, typename Info>
Key& Dictionary<Key, Info>::Iterator::operator*() {
    if(!it)
        throw "No iterator";
    return it->key;
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::llrotation(Node* n){
    return rrotation(n);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrrotation(Node* n){
    n->left=lrotation(n->left);
    return rrotation(n);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrrotation(Node* n){
    return lrotation(n);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rlrotation(Node* n){
    n->right=rrotation(n->right);
    return lrotation(n);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrotation(Node* n){
    Node* newParent;
    newParent = n->right;
    n->right=newParent->left;
    newParent->left=n;
    update(n);
    update(newParent);
    return newParent;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrotation(Node* n){
    Node* newParent;
    newParent = n->left;
    n->left=newParent->right;
    newParent->right=n;
    update(n);
    update(newParent);
    return newParent;
}


template <typename Key, typename Info>
bool Dictionary<Key, Info>::isEmpty() const {
    return root == nullptr;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::update(Node* n) {
    n->balance_factor=height(n->right) - height(n->left);
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::balance(Node* n) {
    if(n->balance_factor<-1) {
        if(n->left->balance_factor<=-1)
            return llrotation(n);
        else
            return lrrotation(n);
    }
    else if(n->balance_factor>1) {
        if(n->right->balance_factor>=1)
            return rrrotation(n);
        else
            return rlrotation(n);
    }
    return n;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::insertIntoDictionary(const Key& key, const Info& info) {
    root = insertIntoDictionary(key, info, root);
    return 1;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::insertIntoDictionary(const Key& key, const Info& info, Node* n){
    if(!n)
        return new Node(key, info, 0, nullptr, nullptr);
    if(key>n->key)
        n->right = insertIntoDictionary(key, info, n->right);
    else if(key<n->key)
        n->left = insertIntoDictionary(key, info, n->left);

    update(n);
    return balance(n);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clearTree() {
   clearTree(root);
   root=nullptr;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clearTree(Node* n) {
   if(!n)
    return;
   clearTree(n->left);
   clearTree(n->right);
   delete n;
}


template <typename Key, typename Info>
bool Dictionary<Key, Info>::contain(const Key& key, Node* n) const {
    if(!n)
        return false;
    if(key>n->key)
        return contain(key, n->right);
    else if(key<n->key)
        return contain(key, n->left);
    else
        return true;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::copy(Node* n) {
    Node* other = nullptr;
    if(n) {
        other = new Node(n->key, n->info, n->balance_factor, nullptr, nullptr);
        other->left=copy(n->left);
        other->right=copy(n->right);
    }
    return other;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::height(Node* n) {
    if(!n) return 0;
    return std::max(height(n->left), height(n->right))+1;
}



template<typename Key, typename Info>
void Dictionary<Key, Info>::printGraph(int width, Node* n) const {
    if(n->right)
        printGraph(width+8, n->right);
    if(width>0)
        std::cout<<std::setw(width)<<" ";
    if(n->right)
        std::cout<<std::endl<<std::setw(width)<< " ";

    std::cout<< "["<<n->key<< "," << n->info <<"]"<<std::endl;
    if(n->left) {
        std::cout<<std::setw(width)<< " "<<std::endl;
        printGraph(width + 8, n->left);
    }
}


template<typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(const Dictionary<Key, Info>& rhs) {
    if(rhs.isEmpty()==1) {
        throw "List to be copied is empty";
    }
    clearTree();
    root = copy(rhs.root);
    return *this;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::remove(const Key& key) {
    if(!contain(key))
        throw "Key to remove does not exist";
    root = remove(key, root);
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::remove(const Key& key, Node* n) {
    if(!n)
        return nullptr;
    if(key<n->key)
        n->left = remove(key, n->left);
    else if(key>n->key)
        n->right = remove(key, n->right);
    else {
        if(!n->left)
            return n->right;
        else if(!n->right)
            return n->left;
        else {
            if(height(n->left)>height(n->right)) {
                Node* tmp = getNode(getMaximalNode(n->left), n->left);
                n->info = tmp->info;
                n->key = tmp->key;
                n->left=remove(tmp->key, n->left);
                delete tmp;
            }
            else {
                Node* tmp = getNode(getMinimalNode(n->right), n->right);
                n->info = tmp->info;
                n->key = tmp->key;
                n->right = remove(tmp->key, n->right);
                delete tmp;
            }
        }
    }
    update(n);
    return balance(n);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::getNode(const Key& key, Node* n) const {
    if(!n)
        throw "Tree is empty";
    if(key>n->key)
        return getNode(key, n->right);
    else if(key<n->key)
        return getNode(key, n->left);

    return n;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator Dictionary<Key, Info>::begin() {
    return Iterator(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::pushIntoRing(Ring<Info, Key>& ring, bool direction){
    if(!root)
        return;
    pushIntoRing(ring, direction, root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::pushIntoRing(Ring<Info,Key>& ring, bool direction, Node* n){
    if(n->left)
        pushIntoRing(ring, direction, n->left);
    if(n->right)
        pushIntoRing(ring, direction, n->right);

    ring.push(n->info, n->key, direction);
}

#endif // AVL_HPP
