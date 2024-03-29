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
	if (index >= this->sizeofStr || index < 0) //
		throw std::out_of_range("Index of string is invalid!");
	else {
		CharALNode* ptr = head;
		int count = 0;
		while (count + ptr->arr.size() <= index) {
			count += ptr->arr.size();
			ptr = ptr->next;
		}
		return ptr->arr[index - count];
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
	while (ptr != tail) {
		res += ptr->arr.getString();
		ptr = ptr->next;
	}
	res += tail->arr.getString();
	return res;  
}

ConcatStringList ConcatStringList::concat(const ConcatStringList& otherS) const {
	tail->next = otherS.head;
	int tmp = sizeofStr + otherS.sizeofStr;
	refList.insertNode(head, 1);
	refList.insertNode(otherS.tail, 1);
	return ConcatStringList(head, otherS.tail, tmp);
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
	CharALNode* tmp_head = nullptr, * tmp_tail = nullptr;
	int sizeofstr = 0;
	if (from < 0 || from >= this->sizeofStr || to < 0 || to > this->sizeofStr)
		throw std::out_of_range("Index of string is invalid");
	else if (from >= to)
		throw std::logic_error("Invalid range");
	else {
		CharALNode* ptr = head;
		int count = 0;
		while (count + ptr->arr.size() <= from) {
			count += ptr->arr.size();
			ptr = ptr->next;
		}
		string tmp;
		int idx = from - count;
		for (int i = from; i < to; i++) {
			if (idx != ptr->arr.size()) {
				tmp += ptr->arr[idx];
				idx++;
				sizeofstr++;
			}
			if (i == to - 1 || idx == ptr->arr.size()) {
				ptr = ptr->next;
				CharALNode* node = new CharALNode(tmp.c_str(), nullptr); //tmp delete will lead tmp.c_str() also deleted
				if (tmp_head == nullptr) {
					tmp_head = node;
					tmp_tail = node;
				}
				else {
					tmp_tail->next = node;
					tmp_tail = node;
				}
				tmp.clear();
				idx = 0;
			}
		}
	}
	refList.insertNode(tmp_head, 1);
	refList.insertNode(tmp_tail, 1);
	return ConcatStringList(tmp_head, tmp_tail, sizeofstr);
}

ConcatStringList ConcatStringList::reverse() const {
	CharALNode* tmp_head = nullptr, * tmp_tail = nullptr;
	int sizeofstr = 0;
	CharALNode* ptr = head;
	while (ptr != tail) {
		string tmp;
		for (int i = ptr->arr.size() - 1; i >= 0; i--) {
			tmp.push_back(ptr->arr[i]);
			sizeofstr++;
		}
		CharALNode* node = new CharALNode(tmp.c_str(), tmp_head);
		if (tmp_head == nullptr)
			tmp_tail = node;
		tmp_head = node;
		ptr = ptr->next;
	}
	//For Tail
	string tmp;
	for (int i = tail->arr.size() - 1; i >= 0; i--) {
		tmp.push_back(tail->arr[i]);
		sizeofstr++;
	}
	CharALNode* node = new CharALNode(tmp.c_str(), tmp_head);
	if (tmp_head == nullptr)
		tmp_tail = node;
	tmp_head = node;
	refList.insertNode(tmp_head, 1);
	refList.insertNode(tmp_tail, 1);
	return ConcatStringList(tmp_head, tmp_tail, sizeofstr);
}

ConcatStringList::~ConcatStringList() {
	delStrList.insertNode(head, tail);
	refList.UpdatenumRef(head);
	refList.UpdatenumRef(tail);  //Add condition
	delStrList.getnumRef();
	refList.clear();
}

//Class implemantation for ReferencesList
void ConcatStringList::ReferencesList::insertionSort(refList* pivot) {
	refList* ptr = head;
	if (capacity > 0) {
		if (head->next->getnumsofRef() == 0)
			return;
		if (pivot == head)
			head = head->next;
		else {
			while (ptr->next != pivot && ptr->next != nullptr) {
				ptr = ptr->next;
			}
			ptr->next = pivot->next;
			if (ptr->next == nullptr)
				tail = ptr;
		}

		refList* current = head;
		if (head == nullptr || head->numsofRef >= pivot->numsofRef) {
			pivot->next = head;
			head = pivot;
		}
		else {
			while (current->next != nullptr && current->next->numsofRef < pivot->numsofRef) {
				if (current->next->numsofRef == 0)
					break;
				current = current->next;
			}
			if (current->next == nullptr)
				tail = pivot;
			pivot->next = current->next;
			current->next = pivot;
		}
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
			insertionSort(newNode);
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
		this->capacity = 0;
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
	if (tmp->numsofRef == 0 && capacity > 1) {
		refList* pCurr = head;
		refList* pPre = nullptr;
		while (pCurr != tmp) {
			pPre = pCurr;
			pCurr = pCurr->next;
		}
		if (pCurr == head)
			head = head->next;
		else
			pPre->next = pCurr->next;
		tail->next = tmp; //Add
		tail = tmp;
		tmp->next = nullptr;
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
	if(capacity > 0)
		res.pop_back();
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
			/*CharALNode* tmp_ptr = tmp_head;
			while (tmp_head != nullptr) {
				tmp_head = tmp_head->next;
				delete tmp_ptr; 
				tmp_ptr = tmp_head;
			}*/
			head = head->next;
			delete ptr;
			ptr = head;
		}
	}
}

//Class implementation for DeletStringList
void ConcatStringList::DeleteStringList::insertNode(CharALNode* head, CharALNode* tail) {
	deleteList* newNode = new deleteList(refList.search(head), refList.search(tail), nullptr);
	if (newNode->ref_head->getnumsofRef() != 0 || newNode->ref_tail->getnumsofRef() != 0) {
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
}

void ConcatStringList::DeleteStringList::deleteNode(deleteList* node) {
	deleteList* pCurr = delListHead;
	deleteList* pPre = nullptr;
	while (pCurr != node) {
		pPre = pCurr;
		pCurr = pCurr->next;
	}
	if (capacity > 1) {
		if (pCurr == delListHead)
			delListHead = delListHead->next;
		else if (pCurr == delListTail) {
			pPre->next = nullptr;
			delListTail = pPre;
		}
		else
			pPre->next = pCurr->next;
	}
	delete pCurr;
	this->capacity--;
}

void ConcatStringList::DeleteStringList::getnumRef() {
	deleteList* ptr1 = delListHead;
	while (ptr1 != nullptr) {
		if (ptr1->ref_head->getnumsofRef() == 0 && ptr1->ref_tail->getnumsofRef() == 0 && 
			ptr1->ref_head->ref != nullptr && ptr1->ref_tail->ref != nullptr) {
			CharALNode* ptr = ptr1->ref_head->ref;
			while (ptr != ptr1->ref_tail->ref) {
				ptr1->ref_head->ref = ptr1->ref_head->ref->next;
				delete ptr;
				ptr = ptr1->ref_head->ref;
			}
			delete ptr;
			ptr1->ref_head->ref = nullptr;
			ptr1->ref_tail->ref = nullptr;
			deleteList* ptr2 = ptr1;
			ptr1 = ptr1->next;
			deleteNode(ptr2);
			if (capacity == 0) {
				delListHead = nullptr;
				delListTail = nullptr;
			}
				
		}
		else
			ptr1 = ptr1->next;
	}

	deleteList* ptr2 = delListHead;
	while (ptr2 != nullptr) {
		if (ptr2->ref_head->numsofRef == 0 && ptr2->ref_tail->numsofRef == 0) {
			deleteList* ptr3 = ptr2;
			ptr2 = ptr2->next;
			deleteNode(ptr3);
		}
		else
			ptr2 = ptr2->next;
	}
	if (capacity == 0) {
		delListHead = nullptr;
		delListTail = nullptr;
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
		if (ptr->ref_head == ptr->ref_tail)
			res += to_string(ptr->ref_head->getnumsofRef()) + ",";
		else
			res += to_string(ptr->ref_head->getnumsofRef() + ptr->ref_tail->getnumsofRef()) + ",";
		ptr = ptr->next;
	}
	if(capacity > 0)
		res.pop_back();
	res += "]";
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

//Class Implementation for CharALNode
void ConcatStringList::CharArrayList::operator=(const char* init) {
	stringstream stream(init);
	getline(stream, this->s);
}

ConcatStringList::CharALNode::CharALNode(const char* s, CharALNode* next) {
	this->next = next;
	this->arr = s;
}
