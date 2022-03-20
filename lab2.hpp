template <typename Key, typename Info>
class Ring { // doubly-linked ring
private:             // with iterator
struct Node {
    Key key;
    Info info;
    Node* next;
    Node* prev;
    Node(const Key& vKey, const Info& vInfo, Node* vnext = nullptr, Node* vprev = nullptr) :
            key(vKey),
            info(vInfo),
            next(vnext),
            prev(vprev) {}
};
Node* any;
int length;
public:
    Ring();
    Ring(Ring<Key, Info>& otherRing);
    ~Ring();
    const Ring<Key, Info>& operator=(Ring<Key, Info>& otherRing);
    bool findNode(const Key& where, int occurence = 1, bool direction = 1);
    bool findInfo(const Info& where, int occurence = 1, bool direction = 1);
    bool findKey(const Key& where, int occurence = 1, bool direction = 1);
    bool isEmpty() const;
    int lengthOfRing() const;
    bool push(const Key& vKey, const Info& vInfo, bool direction = 1);
    bool pushAfter(const Key& vKey, const Info& vInfo, const Key& where, int occurence=1, bool direction=1);
    void printRingInfo(bool direction = 1) const;
    void printRingKey(bool direction = 1) const;
    void printRing(bool direction = 1) const;
    bool removeNode(const Key& where, int occurence=1, bool direction = 1);
    Key getKey(int occurence=1, bool direction=1) const;
    void setKey(const Key& k, int occurence=1, bool direction = 1);
    Info getInfo(int occurence=1, bool direction = 1) const;
    void setInfo(const Info& i, int occurence=1, bool direction = 1);
    int sameNodes(const Key& where);


    class Iterator {
    private:
        friend class Ring<Key, Info>;
        Node* nodePtr;
        Ring<Key, Info>* ringPtr;
        Iterator(Node* ntr, Ring <Key, Info>* rtr): nodePtr(ntr), ringPtr(rtr) {};
    public:
        Iterator(): nodePtr(nullptr), ringPtr(nullptr) {}; //constructor

        Iterator(Node* it): nodePtr(it) {}

        Iterator& operator++() { //preincrement operator
            if(nodePtr)
                nodePtr=nodePtr->next;
            return *this;
        }

        Iterator operator--() { //predectrement operator
            if(nodePtr)
                nodePtr=nodePtr->prev;
            return *this;
        }

        bool operator==(const Iterator& it) const { //equality operator
            return(nodePtr==it.nodePtr);
        }
        bool operator!=(const Iterator& it) const { //not equal operator
            return(nodePtr!=it.nodePtr);
        }
        Key& operator*() { //dereferencing operator
            if(nodePtr)
                return nodePtr->key;
            throw "NULL value of iterator";
        }

        Key& getKey() const { //getter
            return nodePtr->key;
        }
        void setKey(const Key& vKey) { //setter
            nodePtr->key=vKey;
        }
        Info& getInfo() const { //getter
            return nodePtr->info;
        }
        void setInfo(const Info& vInfo) { //setter
            nodePtr->info=vInfo;
        }
    };

    Iterator begin() const{
        return any ? Iterator(any) : Iterator(nullptr);
    }
    Iterator end(bool direction) const{
        if(direction==1)
            return any ? Iterator(any->prev) : Iterator(nullptr);
        else
            return any ? Iterator(any->next) : Iterator(nullptr);
    }
};

template<typename Key, typename Info>
Ring<Key, Info>::Ring() {
    length = 0;
    any=nullptr;
}

template<typename Key, typename Info>
Ring<Key, Info>::Ring(Ring<Key, Info>& otherRing) {
    Node* curr=any;
    if(curr==NULL)
        std::cout<<"No elements in ring"<<std::endl;
    else {
        for(int i=0; i<length; i++) {
        otherRing.push(curr->key, curr->info);
        curr=curr->next;
        }
    }
}

template<typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    Node* temp;
    Node* curr=any;
    for(int i=length;i>0;i--){
        temp = curr;
        curr=curr->next;
        delete temp;
        length--;
    }
}

template<typename Key, typename Info>
const Ring<Key, Info>& Ring<Key, Info>::operator= (Ring<Key, Info>& otherRing) {
    if(isEmpty())
        std::cout<<"No elements in ring"<<std::endl;
    else {
        typename Ring<Key, Info>::Iterator it = (*this).begin();
        for(int i=0; i<length; i++) {
        otherRing.push(it.getKey(), it.getInfo());
        ++it;
        }
    }
    return *this;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::findNode(const Key& where, int occurence, bool direction) {
    if(isEmpty()) {
        return 0;
    }

    int c, d;
    d=sameNodes(where);
    if(d>1)
        c = occurence%d;
    else
        c=1;
    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1)
    {
    do {
        if((*it) == where) {
            if(c==1) {
            return true;
            }
            c--;
        }
        ++it;
    } while(it!=this->begin());
    return false;
    }
    else {
        do {
        if((*it) == where) {
            if(c==1) {
            return true;
            }
            c--;
        }
        --it;
    } while(it!=this->begin());
    return false;
    }
}

template<typename Key, typename Info>
bool Ring<Key, Info>::findInfo(const Info& where, int occurence, bool direction) {
    if(isEmpty()) {
        return 0;
    }

    else {
    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1)
    {
    do {
        if(it.getInfo() == where) {
            std::cout<<"["<<it.getKey()<<", "<<it.getInfo()<<"]"<<std::endl;
        }
        ++it;
    } while(it!=this->begin());
    }
    else {
        do {
        if(it.getInfo() == where) {
            std::cout<<"["<<it.getKey()<<", "<<it.getInfo()<<"]"<<std::endl;
        }
        --it;
    } while(it!=this->begin());
    }
    return true;
    }
}

template<typename Key, typename Info>
bool Ring<Key, Info>::findKey(const Key& where, int occurence, bool direction) {
    if(isEmpty()) {
        return 0;
    }

    else {
    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1)
    {
    do {
        if(it.getKey() == where) {
            std::cout<<"["<<it.getKey()<<", "<<it.getInfo()<<"]"<<std::endl;
        }
        ++it;
    } while(it!=this->begin());
    }
    else {
        do {
        if(it.getKey() == where) {
            std::cout<<"["<<it.getKey()<<", "<<it.getInfo()<<"]"<<std::endl;
        }
        --it;
    } while(it!=this->begin());
    }
    return true;
    }
}


template<typename Key, typename Info>
bool Ring<Key, Info>::isEmpty() const {
    if(length==0) return 1;
    else return 0;
}

template<typename Key, typename Info>
int Ring<Key, Info>::lengthOfRing() const {
    return length;
}


template<typename Key, typename Info>
bool Ring<Key, Info>::push(const Key& vKey, const Info& vInfo, bool direction) {
    if(direction==1) {
        if(isEmpty()) {
        any = new Node(vKey, vInfo);
        any -> next = any;
        any -> prev = any;
        length++;
        return 1;
    }
    else if(length==1) {
        Node* curr = any->next;
        curr=new Node(vKey, vInfo);
        curr->next=any;
        curr->prev=any;
        any->next=curr;
        any->prev=curr;
        length++;
        return 1;
    }
    else
    {
        Node* curr;
        curr = new Node(vKey, vInfo);
        any->prev->next=curr;
        curr -> next = any;
        curr -> prev = any -> prev;
        any -> prev = curr;
        length++;
        return 1;
    }
    }
    else {
        if(isEmpty()) {
        any = new Node(vKey, vInfo);
        any -> next = any;
        any -> prev = any;
        length++;
        return 1;
    }
        else if(length==1) {
        Node* curr = any->next;
        curr=new Node(vKey, vInfo);
        curr->prev=any;
        curr->next=any;
        any->prev=curr;
        any->next=curr;
        length++;
        return 1;
    }
    else {
        Node* curr;
        curr = new Node(vKey, vInfo);
        any->next->prev=curr;
        curr -> prev = any;
        curr -> next = any -> next;
        any -> next = curr;
        length++;
        return 1;
    }
    }
    return 0;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::pushAfter(const Key& vKey, const Info& vInfo, const Key& where, int occurence, bool direction)
{
    if(isEmpty()) {
        throw "List is empty, unable to find element to push after";
    }
    if(!findNode(where, occurence)) {
        throw "Cannot find element in the ring";
    }

    Node* curr = any;
    Node* next;
    Node* newNode = new Node (vKey, vInfo);

    if(length==1)
    {
        newNode->next=curr;
        newNode->prev=curr;
        curr->next=newNode;
        curr->prev=newNode;
        length++;
        return true;
    }
    else {
    int c, d;
    d=sameNodes(where);
    if(d!=1)
        c = occurence%d;
    else
        c=1;
            if(direction==1) {
                Node* next;
                do {
                    if(curr->key==where) {
                        if(c==1)
                        {
                        next=curr->next;
                        next->prev=newNode;
                        newNode->next=next;
                        newNode->prev=curr;
                        curr->next=newNode;
                        length++;
                        return true;
                        }
                        else
                        c--;
                    }
                    curr=curr->next;
                } while(curr->next!=any);
                return false;
            }
            else{
                Node* prev;
                do {
                    if(curr->key==where) {
                        if(c==1) {
                        prev=curr->prev;
                        prev->next=newNode;
                        newNode->prev=prev;
                        newNode->next=curr;
                        curr->prev=newNode;
                        length++;
                        return true;
                        }
                        else
                            c--;
                    }
                    curr=curr->next;
                } while(curr->next!=any);
                return false;
            }
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::printRingInfo(bool direction) const {
if(isEmpty())
    std::cout<<"No elements in the ring";
    else {
        typename Ring<Key, Info>::Iterator it = (*this).begin();
        if(direction==1) {
            for(int i=0; i<length; i++) {
            std::cout<<std::setw(12)<<it.getInfo();
            ++it;
            }
        }
        else {
            for(int i=0; i<length; i++) {
            std::cout<<std::setw(12)<<it.getInfo();
            ++it;
            }
        }
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::printRingKey(bool direction) const {
if(isEmpty())
    std::cout<<"No elements in the ring";
    else {
        typename Ring<Key, Info>::Iterator it = (*this).begin();
        if(direction==1) {
            for(int i=0; i<length; i++) {
            std::cout<<std::setw(12)<<it.getKey();
            ++it;
            }
        }
        else {
            for(int i=0; i<length; i++) {
            std::cout<<std::setw(12)<<it.getKey();
            ++it;
            }
        }
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::printRing(bool direction) const {
if(isEmpty())
    std::cout<<"No elements in the ring";
    else {
        if(direction==1) {
            typename Ring<Key, Info>::Iterator it = (*this).begin();
            for(int i=0; i<length; i++) {
            std::cout<<"["<<it.getKey()<<", "<<it.getInfo()<<"]";
            ++it;
            }
        }
        else {
            typename Ring<Key, Info>::Iterator it = (*this).end(1);
            for(int i=length; i>0; i--) {
            std::cout<<"["<<it.getKey()<<", "<<it.getInfo()<<"]";
            --it;
            }
        }
    }
}

template<typename Key, typename Info>
bool Ring<Key, Info>::removeNode(const Key& where, int occurence, bool direction) {
    int occ=1;
    if(isEmpty()) {
        std::cout<<"No elements in the list";
        return 0;
    }
    if(!findNode(where, occurence)) {
        std::cout<<"Element is not in the list";
        return 0;
    }
    else if(length == 1 && any->key==where) {
        delete any;
        any=nullptr;
        length--;
        return 1;
    }
    else {
    if(direction==1) {
        Node* curr=any;
        Node* prev=any->prev;
        Node* next=any->next;
        int i = length;
        int c, d;
    d=sameNodes(where);
    if(d!=1)
        c = occurence%d;
    else
        c=1;
        for(i; i>0; i--) {
            if(curr->key==where) {
                    if(occ=c)
                    {
                        curr->prev->next=curr->next;
                        curr->next->prev=curr->prev;
                        any=curr->next;
                        delete curr;
                        length--;
                    }
                    occ++;
            }
            curr=curr->next;
            prev=prev->next;
            next=next->next;
    }
        return 1;
    }
    else {
        Node* curr=any;
        Node* prev=any->prev;
        Node* next=any->next;
        int i = length;
        int c, d;
    d=sameNodes(where);
    if(d!=1)
        c = occurence%d;
    else
        c=1;
        for(i; i>0; i--) {
            if(curr->key==where) {
                    if(occ==c)
                    {
                        curr->prev->next=curr->next;
                        curr->next->prev=curr->prev;
                        any=curr->next;
                        delete curr;
                        length--;
                    }
                    occ++;
            }
            curr=curr->prev;
            prev=prev->prev;
            next=next->prev;
    }
    }
    return 0;
    }
}

template<typename Key, typename Info>
Key Ring<Key, Info>::getKey(int occurance, bool direction) const {
    if(isEmpty()) {
        throw "Ring is empty";
    }

    int c;
    if(length<occurance)
        c=occurance%length;
    else
        c=occurance;

    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1)
    {
    do {
        if (c==1) {
            return it.getKey();
        }
        c--;
        ++it;
    } while(it!=this->begin());
    throw "Unable to find the item";
    }
    else
    {
        do {
        if (c==1) {
            return it.getKey();
        }
        c--;
        --it;
    } while(it!=this->begin());
    throw "Unable to find the item";
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::setKey(const Key& k, int occurance, bool direction) {
    if(isEmpty()) {
        throw "Ring is empty";
    }
    int c;
    if(length<occurance)
        c=occurance%length;
    else
        c=occurance;

    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1) {
    do {
        if(c==1) {
            it.setKey(k);
            break;
        }
        else {
            c--;
            ++it;
        }
    } while(it!=this->begin());
    }
    else {
        do {
        if(c==1) {
            it.setKey(k);
            break;
        }
        else {
            c--;
            --it;
        }
    } while(it!=this->begin());
    }
}

template<typename Key, typename Info>
Info Ring<Key, Info>::getInfo(int occurance, bool direction) const {
    if(isEmpty()) {
        throw "Ring is empty";
    }

    int c;
    if(length<occurance)
        c=occurance%length;
    else
        c=occurance;

    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1) {
    do {
        if (c==1) {
            return it.getInfo();
        }
        c--;
        ++it;
    } while(it!=this->begin());
    throw "Unable to find the item";
    }
    else {
        do {
        if (c==1) {
            return it.getInfo();
        }
        c--;
        --it;
    } while(it!=this->begin());
    throw "Unable to find the item";
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::setInfo(const Info& i, int occurance, bool direction) {
    if(isEmpty()) {
        throw "Ring is empty";
    }

    int c;
    if(length<occurance)
        c=occurance%length;
    else
        c=occurance;

    typename Ring<Key, Info>::Iterator it = (*this).begin();
    if(direction==1) {
    do {
        if(c==1) {
            it.setInfo(i);
            break;
        }
        else {
            c--;
            ++it;
        }
    } while(it!=this->begin());
    }
    else {
    do {
        if(c==1) {
            it.setInfo(i);
            break;
        }
        else {
            c--;
            --it;
        }
    } while(it!=this->begin());
    }
}

template<typename Key, typename Info>
int Ring<Key, Info>::sameNodes(const Key& where) {
    if(isEmpty()) {
        return 0;
    }
    int c=0;
    typename Ring<Key, Info>::Iterator it = (*this).begin();
    do {
        if(it.getKey()==where)
            c++;
        ++it;
    } while(it!=this->begin());
    return c;
}
