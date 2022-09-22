#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration
    class CharArrayList; // forward declaration
    class CharALNode; // forward declaration
public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
    // Try all algorithm always in linear complexity
private:
    int sizeofStr;
    CharALNode* head;
    CharALNode* tail;
public:
    ConcatStringList(const char *);
    ConcatStringList(CharALNode *,CharALNode *, int );
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

public:
    class ReferencesList {
        // TODO: may provide some attributes
        public :
            class refList; //Forward Declaration
        private:
            refList* head;
            refList* tail;
            int capacity;
            void insertionSort(refList* );
            bool checkAllZero();
        public:
            ReferencesList() {
                this->head = nullptr;
                this->capacity = 0;
                this->tail = nullptr;
            }
            void insertNode(CharALNode* , int);
            refList* search(CharALNode* );
            void UpdatenumRef(CharALNode*&);
            void clear();
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;
            ~ReferencesList(); //Using this to delete all CharALNode

            class refList {
                private:
                    CharALNode* ref;
                    int numsofRef;
                    refList* next;
                    friend class ReferencesList;
                public:
                    refList(CharALNode* ref, int numsofRef, refList* next) {
                        this->ref = ref;
                        this->numsofRef = numsofRef;
                        this->next = next;
                    }
                    int getnumsofRef() {
                        return this->numsofRef;
                    }
            };
    };

    class DeleteStringList {
        // TODO: may provide some attributes
        public:
            class delNode;
            class deleteList;
        private:
            deleteList* delListHead;
            deleteList* delListTail;
            int capacity;
        public:
            void insertNode(CharALNode*, CharALNode* );
            void deleteNode(deleteList* );
            void getnumRef();
            int size() const;
            std::string totalRefCountsString() const;
            ~DeleteStringList(); //This destructor will delete all node in heap

            class delNode {
                public:
                    CharALNode* ptr;
                    ReferencesList::refList* reference;
            };

            class deleteList {
                delNode head, tail;
                deleteList* next;
                friend class DeleteStringList;
            public:
                deleteList(CharALNode* head, CharALNode* tail, deleteList* next) {
                    this->head.ptr = head;
                    this->tail.ptr = tail;
                    this->next = next;
                }
            };
    };

    class CharArrayList {
    private:
        string s;
    public:
        CharArrayList();
        void operator= (const char*);
        int size() {
            return this->s.length();
        }
        char operator[] (int index) {
             return this->s[index];
        }
    };

    class CharALNode {
        private:
            CharArrayList arr;
            CharALNode* next;
            friend class ConcatStringList;
        public:
            CharALNode(const char*, CharALNode*);
            int lenofNode() {
                return arr.size();
            }
    };
};

#endif // __CONCAT_STRING_LIST_H__