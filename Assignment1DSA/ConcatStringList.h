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
        private:
            void insertNode(CharALNode* , int);
            refList* search(CharALNode* );
            void UpdatenumRef(CharALNode*&);
            void clear();
            friend class ConcatStringList;
        public:
            ReferencesList() {
                this->head = nullptr;
                this->capacity = 0;
                this->tail = nullptr;
            }
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
                    friend class DeleteStringList;
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
            void insertNode(CharALNode*, CharALNode* );
            void deleteNode(deleteList* );
        private:
            void getnumRef();
            friend class ConcatStringList;
        public:
            DeleteStringList() {
                this->delListHead = nullptr;
                this->delListTail = nullptr;
                this->capacity = 0;
            }
            int size() const;
            std::string totalRefCountsString() const;
            ~DeleteStringList(); //This destructor will delete all node in heap

            class deleteList {
                private:
                    ReferencesList::refList* ref_head;
                    ReferencesList::refList* ref_tail;
                    deleteList* next;
                    friend class DeleteStringList;
                public:
                    deleteList(ReferencesList::refList* ref_head, ReferencesList::refList* ref_tail, deleteList* next) {
                        this->ref_head = ref_head;
                        this->ref_tail = ref_tail;
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
                return (int)(this->s.length());
            }
            char operator[] (int index) {
                 return this->s[index];
            }
            string getString() {
                return s;
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
