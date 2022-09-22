#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

//Class implementation for ConCAtStringList
ConcatStringList::ConcatStringList(const char *s) {
	CharALNode* newNode = new CharALNode(s, nullptr);
	this->head = newNode;
	this->tail = newNode;
	this->sizeofStr = newNode->lenofNode();
	refList.insertNode(newNode, 2);
}

ConcatStringList::ConcatStringList(CharALNode* head, CharALNode* tail, int len) {
	this->head = head;
	this->tail = tail;
	this->sizeofStr = len;
}

ConcatStringList::CharArrayList::CharArrayList() {
	this->s = "";
}

int ConcatStringList::length() const {
	return this->sizeofStr;
}

char ConcatStringList::get(int index) const {
	if (index >= this->sizeofStr)
		throw std::out_of_range("Index of string is invalid!");
	else {
		CharALNode* ptr = head;
		while (ptr->arr.size() < index)
			ptr = ptr->next;
		return ptr->arr[index];
	}
}

int ConcatStringList::indexOf(char c) const {
	CharALNode* ptr = head;
	int idx = 0;
	while (ptr != nullptr) {
		int tmp = ptr->arr.size();
		for (int i = 0; i < ptr->arr.size(); i++) {
			if (ptr->arr[i] == c)
				return idx + i;
		}
		ptr = ptr->next;
		idx += tmp;
	}
	return -1;
}

std::string ConcatStringList::toString() const {
	string res;
	CharALNode* ptr = head;
	while (ptr != nullptr) {
		for (int i = 0; i < ptr->arr.size(); i++) {
			res.push_back(ptr->arr[i]);
		}
		ptr = ptr->next;
	}
	return res;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList& otherS) const {
	tail->next = otherS.head;
	int tmp = sizeofStr + otherS.sizeofStr;
	ConcatStringList *newStrList = new ConcatStringList(head, otherS.tail, tmp);
	refList.insertNode(newStrList->head, 1);
	refList.insertNode(newStrList->tail, 1);
	return *newStrList;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
	ConcatStringList *subStrList = new ConcatStringList(nullptr, nullptr, 0);
	if (from < 0 || from >= this->sizeofStr || to < 0 || to >= this->sizeofStr)
		throw std::out_of_range("Index of string is invalid");
	else if (from >= to)
		throw std::logic_error("Invalid range");
	else {
		CharALNode* ptr = head;
		int idx = from;
		while (ptr->arr.size() < from)
			ptr = ptr->next;
		string tmp;
		for (int i = from; i <= to; i++) {
			if (idx != ptr->arr.size()) {
				tmp += ptr->arr[idx];
				idx++;
			}
			else {
				ptr = ptr->next;
				CharALNode* node = new CharALNode(tmp.c_str(), nullptr); //tmp delete will lead tmp.c_str() also deleted
				if (subStrList->head == nullptr) {
					subStrList->head = node;
					subStrList->tail = node;
				}
				else {
					subStrList->tail->next = node;
					subStrList->tail = node;
				}
				subStrList->sizeofStr++;
				tmp.clear();
				idx = 0;
			}
		}
	}
	refList.insertNode(subStrList->head, 1);
	refList.insertNode(subStrList->tail, 1);
	return *subStrList;
}

ConcatStringList ConcatStringList::reverse() const {
	ConcatStringList *RevList = new ConcatStringList(nullptr, nullptr, 0);
	CharALNode* ptr = head;
	while (ptr != nullptr) {
		string tmp;
		for (int i = ptr->arr.size() - 1; i >= 0; i--)
			tmp.push_back(ptr->arr[i]);
		CharALNode* node = new CharALNode(tmp.c_str(), RevList->head);
		RevList->head = node;
		if (RevList->length() == 0)
			RevList->tail = node;
		RevList->sizeofStr++;
		ptr = ptr->next;
	}
	refList.insertNode(RevList->tail, 1);
	refList.insertNode(RevList->head, 1);
	return *RevList;
}

ConcatStringList::~ConcatStringList() {
	refList.UpdatenumRef(head);
	refList.UpdatenumRef(tail);
	delStrList.insertNode(head,tail);
	delStrList.getnumRef();
	refList.clear();
}

//Class implemantation for ReferencesList
void ConcatStringList::ReferencesList::insertionSort(refList* pivot) {
	if (pivot->next == nullptr || pivot->numsofRef <= pivot->next->numsofRef) {
		refList* ptr = head;
		refList* prev = nullptr;
		while (ptr->next != pivot) {
			if (ptr->numsofRef < pivot->numsofRef) {
				prev = ptr;
				ptr = ptr->next;
			}
			else {
				break;
			}
		}
		refList* tmp = head;
		while (tmp->next != pivot) {
			tmp = tmp->next;
			if (tmp->next == nullptr)
				break;
		}
		if (tmp->next != ptr->next) {
			tmp->next = pivot->next;
			pivot->next = ptr;
			if (ptr != head)
				prev->next = pivot; //
			else
				head = pivot;
		}
	}
	else {
		refList* ptr = pivot->next;
		refList* prev = nullptr;
		while (ptr != nullptr) {
			if (ptr->numsofRef <= pivot->numsofRef) {
				prev = ptr;
				ptr = ptr->next;
			}
			else {
				break;
			}
		}
		refList* tmp = head;
		while (tmp->next != pivot) {
			tmp = tmp->next;
			if (tmp->next == nullptr)
				break;
		}
		if (tmp == ReferencesList::tail)
			tail = pivot;
		if (pivot == head && head->next != nullptr)
			head = head->next;
		else 
			tmp->next = pivot->next;
		pivot->next = ptr;
		prev->next = pivot;
	}
}

void ConcatStringList::ReferencesList::insertNode(CharALNode* node, int nums) {
	if (ReferencesList::head == nullptr) {
		ReferencesList::refList* newNode = new refList(node, nums, nullptr);
		ReferencesList::head = newNode;
		ReferencesList::tail = newNode;
		this->capacity++;
	}
	else {
		ReferencesList::refList* ptr = ReferencesList::head;
		while (ptr != nullptr) {
			if (ptr->ref == node) {
				ptr->numsofRef++;
				insertionSort(ptr);
				break;
			}
			else
				ptr = ptr->next;
		}
		if (ptr == nullptr) {
			ReferencesList::refList* newNode = new refList(node, nums, head);
			ReferencesList::head = newNode;
			this->capacity++;
		}
	}
}

ConcatStringList::ReferencesList::refList* ConcatStringList::ReferencesList::search(CharALNode* target) {
	refList* ptr = head;
	while (ptr != nullptr) {
		if (ptr->ref == target)
			return ptr;
		ptr = ptr->next;
	}
	return nullptr;
}

void ConcatStringList::ReferencesList::clear() {
	if (checkAllZero()) {
		refList* ptr = head;
		while (ptr != nullptr) {
			head = head->next;
			delete ptr;
			ptr = head;
		}
	}
}

bool ConcatStringList::ReferencesList::checkAllZero() {
	refList* ptr = head;
	while (ptr != nullptr) {
		if (ptr->getnumsofRef() != 0)
			return false;
		ptr = ptr->next;
	}
	return true;
}

void ConcatStringList::ReferencesList::UpdatenumRef(CharALNode*& node) {
	refList* tmp = search(node);
	tmp->numsofRef--;
	if (tmp->numsofRef == 0) {
		refList* pCurr = head;
		refList* pPre = nullptr;
		while (pCurr != tmp) {
			pPre = pCurr;
			pCurr = pCurr->next;
		}
		if (pPre == nullptr)
			head = head->next;
		else
			pPre->next = pCurr->next;
		tail->next = tmp;
		tmp->next = nullptr;
		tail = tmp;
	}
	else {
		insertionSort(tmp);
	}
}

int ConcatStringList::ReferencesList::size() const {
	return capacity;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const {
	if (index >= capacity)
		throw std::out_of_range("Index of references list is invalid!");
	else {
		refList* ptr = head;
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr->getnumsofRef();
	}
}

std::string ConcatStringList::ReferencesList::refCountsString() const {
	string res;
	res += "RefCounts[";
	refList* ptr = head;
	while(ptr != nullptr) {
		res += to_string(ptr->getnumsofRef()) + ",";
		ptr = ptr->next;
	}
	res += "]";
	return res;
}

ConcatStringList::ReferencesList::~ReferencesList() {
	refList* ptr = head;
	while (ptr != nullptr) {
		CharALNode* tmp_head = ptr->ref;
		if (tmp_head == nullptr) {
			head = head->next;
			delete ptr;
			ptr = head;
		}
		else {
			CharALNode* tmp_ptr = tmp_head;
			while (tmp_ptr != nullptr) {
				tmp_head = tmp_head->next;
				delete tmp_ptr;
				tmp_ptr = tmp_head;
			}
			head = head->next;
			delete ptr;
			ptr = head;
		}
	}
}

//Class implementation for DeletStringList
void ConcatStringList::DeleteStringList::insertNode(CharALNode* head, CharALNode* tail) {
	deleteList* newNode = new deleteList(head, tail, nullptr);
	newNode->head.reference = refList.search(head);
	newNode->tail.reference = refList.search(tail);
	if (delListHead == nullptr && delListTail == nullptr) {
		delListHead = newNode;
		delListTail = newNode;
	}
	else {
		delListTail->next = newNode;
		delListTail = newNode;
	}
	this->capacity++;
}

void ConcatStringList::DeleteStringList::deleteNode(deleteList* node) {
	deleteList* pCurr = delListHead;
	deleteList* pPre = nullptr;
	while (pCurr != node) {
		pPre = pCurr;
		pCurr = pCurr->next;
	}
	if (pPre == nullptr) 
		delListHead = delListHead->next;
	else 
		pPre->next = pCurr->next;
	delete pCurr;
}

void ConcatStringList::DeleteStringList::getnumRef() {
	deleteList* ptr1 = delListHead;
	while (ptr1 != nullptr) {
		if (ptr1->head.reference->getnumsofRef() == 0 && ptr1->tail.reference->getnumsofRef() == 0) {
			CharALNode* ptr = delListHead->head.ptr;
			while (ptr != delListHead->tail.ptr) {
				delListHead->head.ptr = delListHead->head.ptr->next;
				delete ptr;	
				ptr = delListHead->head.ptr;
			}
			delete ptr;
			deleteNode(ptr1);
		}
		else
			ptr1 = ptr1->next;
	}
}

int ConcatStringList::DeleteStringList::size() const {
	return capacity;
}

std::string ConcatStringList::DeleteStringList::totalRefCountsString() const {
	string res;
	res += "TotalRefCounts[";
	deleteList* ptr = delListHead;
	while (ptr != nullptr) {
		res += to_string(ptr->head.reference->getnumsofRef());
	}
	return res;
}

ConcatStringList::DeleteStringList::~DeleteStringList() {
	deleteList* ptr = delListHead;
	while (ptr != nullptr) {
		delListHead = delListHead->next;
		delete ptr;
		ptr = delListHead;
	}
}

void ConcatStringList::CharArrayList::operator=(const char* init) {
	stringstream stream(init);
	stream >> this->s;
}

ConcatStringList::CharALNode::CharALNode(const char* s, CharALNode* next) {
	this->next = next;
	this->arr = s;
}