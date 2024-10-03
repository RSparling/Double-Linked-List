#pragma once
#include <stdexcept>

/// <summary>
/// A struct to hold the data and pointers to the next and previous nodes in the list. It is a template struct so it can hold any type of data.
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
struct Node
{
	T data;
	Node* next;
	Node* prev;
};

/// <summary>
/// This is a container class that holds a doubly linked list of nodes. It is a template class so it can hold any type of data which in this case is a Node<T>.
/// The head and tail is private to to prevent outside access to the nodes and prevent the list from being modified in a way that would break the list.
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class DLList
{
private:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* current;
	int size;
public:
	DLList() : head(nullptr), tail(nullptr), size(0) {}
	~DLList() {
		//iterates through the entire list to delete each node
		Node<T>* temp = head;
		while (temp != nullptr) {
			Node<T>* next = temp->next;
			delete temp;
			temp = next;
		}
	}

	//insertion operations

	//relative to list

	/// <summary>
	/// Adds a node to the end of the list.
	/// </summary>
	/// <param name="data"></param>
	void Append(T data) {
		//make sure head is not null
		if (head == nullptr) {
			head = new Node<T>{ data, nullptr, nullptr };
			tail = head;
		}
		else {
			tail->next = new Node<T>{ data, nullptr, tail };
			tail = tail->next;
		}
		size++;
	}

	/// <summary>
	/// Adds a node to the beginning of the list.
	/// </summary>
	/// <param name="data"></param>
	void Prepend(T data) {
		//make sure head is not null
		if (head == nullptr) {
			head = new Node<T>{ data, nullptr, nullptr };
			tail = head;
		}
		else {
			head->prev = new Node<T>{ data, head, nullptr };
			head = head->prev;
		}
		size++;
	}

	//relative to current

	/// <summary>
	/// Advances current node x steps, default 1.
	/// </summary>
	/// <param name="steps"></param>
	void Forward(int steps = 1) {
		for (int i = 0; i < steps; i++) {
			//if the next step is null, go to head
			if (current->next == nullptr) {
				current = head;
			}
			else {
				current = current->next;
			}
		}
	}

	/// <summary>
	/// Back up current node x steps, default 1.
	/// </summary>
	/// <param name="steps"></param>
	void Back(int steps = 1) {
		//if the previous step is null, go to tail
		for (int i = 0; i < steps; i++) {
			if (current->prev == nullptr) {
				current = tail;
			}
			else {
				current = current->prev;
			}
		}
	}

	/// <summary>
	/// insert a node after the current node.
	/// </summary>
	/// <param name="data"></param>
	void Insert_After(T data) {
		//if the current node is the tail, append
		if (current == tail) {
			Append(data);
		}
		else {
			Node<T>* temp = current->next;
			current->next = new Node<T>{ data, temp, current };
			temp->prev = current->next;
			size++;
		}
	}

	/// <summary>
	/// Insert a ndoe before the current node.
	/// </summary>
	/// <param name="data"></param>
	void Insert_Before(T data) {
		//if the current node is the head, prepend
		if (current == head) {
			Prepend(data);
		}
		else {
			Node<T>* temp = current->prev;
			current->prev = new Node<T>{ data, current, temp };
			temp->next = current->prev;
			size++;
		}
	}

	void Head() {
		current = head;
	}

	void Tail() {
		current = tail;
	}


	/// <summary>
	/// Set the current node to the index
	/// </summary>
	/// <param name="index"></param>
	/// <returns>Returns false if operation failed due to out of bounds.</returns>
	bool Set_Current_To_Index(int index) {
		//start from the head
		current = head;
		//iterate through the list until the index is reached
		for (int i = 0; i < index; i++) {
			if (current->next == nullptr) {
				return false;
			}
			current = current->next;
		}
	}

	/// <summary>
	/// reverse the list.
	/// </summary>
	void Reverse() {
		Node<T>* temp = head;
		head = tail;
		tail = temp;
		current = head;
		while (temp != nullptr) {
			Node<T>* next = temp->next;
			temp->next = temp->prev;
			temp->prev = next;
			temp = next;
		}
	}

	/// <summary>
	/// Counts the number of nodes in the list
	/// </summary>
	int Count() {
		Node<T>* temp = head;
		int count = 0;
		while (temp != nullptr) {
			count++;
			temp = temp->next;
		}

		return count;
	}


	/// <summary>
	/// Finds the index of the data in the list. Returns -1 if not found.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int Find(T data) {
		Node<T>* temp = head;
		int index = 0;
		while (temp != nullptr) { //ensure the node is not null
			if (temp->data == data) { //compare the data
				return index; //return the index if found
			}
			temp = temp->next; //move to the next node
			index++; //increment the index
		}
		return -1; //return -1 if not found
	}

	/// <summary>
	/// Finds the data of the index in the list. Returns -1 if not found.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int Find_And_Set_Current(T data) {
		Node<T>* temp = head;
		int index = 0;
		while (temp != nullptr) {
			if (temp->data == data) {
				current = temp;
				return index;
			}
			temp = temp->next;
			index++;
		}
		return -1;
	}

	/// <summary>
	/// Inserts data at the index. Returns false if out of bounds.
	/// </summary>
	/// <param name="index"></param>
	/// <param name="data"></param>
	/// <returns></returns>

	bool Insert_At(int index, T data){
		if (index < 0 || index > size) {
			return false;
		}
		if (index == 0) {
			Prepend(data);
		}
		else if (index == size) {
			Append(data);
		}
		else {
			Node<T>* temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			Node<T>* newNode = new Node<T>{ data, temp, temp->prev };
			temp->prev->next = newNode;
			temp->prev = newNode;
			size++;
		}
		return true;
	}

	/// <summary>
	/// Remove the head node.
	/// </summary>
	/// <returns></returns>

	bool Remove_First() {
		if (size == 0) {
			return false;
		}
		if (size == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
			size--;
			return true;
		}
		Node<T>* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
		size--;
		return true;
	}

	/// <summary>
	/// remove the tail node.
	/// </summary>
	/// <returns></returns>

	bool Remove_Last() {
		if (size == 0) {
			return false;
		}
		if (size == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
			size--;
			return true;
		}
		Node<T>* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
		size--;
		return true;
	}

	/// <summary>
	/// remove node at index. Returns false if out of bounds.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	bool Remove_At(int index) {
		if (index < 0 || index >= size) {
			return false;
		}
		if (index == 0) {
			Remove_First();
		}
		else if (index == size - 1) {
			Remove_Last();
		}
		else {
			Node<T>* temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			size--;
		}
		return true;
	}

	/// <summary>
	/// Removes the current node and set the current node to the next node
	/// </summary>
	/// <returns></returns>
	bool Remove_Current() {
		if (current == nullptr) {
			return false;
		}
		if (current == head) {
			Remove_First();
		}
		else if (current == tail) {
			Remove_Last();
		}
		else {
			Node<T>* temp = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;
			delete temp;
			size--;
		}
		return true;
	}

	/// <summary>
	/// Get the data from a node x steps from head and sets the node as the current node.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	T At(int index) {
		Node<T>* temp = head;
		for (int i = 0; i < index; i++) {
			//null check
			if (temp->next == nullptr) {
				return nullptr;
			}
			temp = temp->next;
		}
		current = temp;
		return temp->data;
	}

	/// <summary>
	/// Get the index of the current node.
	/// </summary>
	int Current_Index() {
		Node<T>* temp = head;
		int index = 0;
		while (temp != current) {
			temp = temp->next;
			index++;
		}
		return index;
	}

	T Current() {
		// null check for current
		if (current == nullptr) {
			// null check for head
			current = head;
		}
		return current->data;
	}
};

/*

////relative to list

	/// <summary>
	/// Adds a node to the end of the list.
	/// </summary>
	/// <param name="data"></param>
	void Append(T data);

	/// <summary>
	/// Adds a node to the beginning of the list.
	/// </summary>
	/// <param name="data"></param>
	void Prepend(T data);

	////navigation


	/// <summary>
	/// insert a node after the current node.
	/// </summary>
	/// <param name="data"></param>
	void Insert_After(T data);

	/// <summary>
	/// Insert a ndoe before the current node.
	/// </summary>
	/// <param name="data"></param>
	void Insert_Before(T data);

	void Head();

	void Tail();

	/// <summary>
	/// Advances current node x steps, default 1.
	/// </summary>
	/// <param name="steps"></param>
	void Forward(int steps = 1);

	/// <summary>
	/// Back up current node x steps, default 1.
	/// </summary>
	/// <param name="steps"></param>
	void Back(int steps = 1);

	///////Modification Operations

	/// <summary>
	/// Inserts data at the index. Returns false if out of bounds.
	/// </summary>
	/// <param name="index"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	bool Insert_At(int index, T data);

	/// <summary>
	/// Remove the head node.
	/// </summary>
	/// <returns></returns>
	bool Remove_First();

	/// <summary>
	/// remove the tail node.
	/// </summary>
	/// <returns></returns>
	bool Remove_Last();

	/// <summary>
	/// remove node at index. Returns false if out of bounds.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	bool Remove_At(int index);

	/// <summary>
	/// Removes the current node and set the current node to the next node
	/// </summary>
	/// <returns></returns>
	bool Remove_Current();


	///////Utility Operations
	/// <summary>
	/// Set the current node to the index
	/// </summary>
	/// <param name="index"></param>
	/// <returns>Returns false if operation failed due to out of bounds.</returns>
	bool Set_Current_To_Index(int index);

	/// <summary>
	/// reverse the list.
	/// </summary>
	void Reverse();

	/// <summary>
	/// Counts the number of nodes in the list
	/// </summary>
	int Count();

	/// <summary>
	/// Finds the index of the data in the list. Returns -1 if not found.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int Find(T data);

	/// <summary>
	/// Finds the data of the index in the list. Returns -1 if not found.
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int Find_And_Set_Current(T data);

	/// <summary>
	/// Get the data from a node x steps from head and sets the node as the current node.
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	T At(int index);

	/// <summary>
	/// Get the index of the current node.
	/// </summary>
	int Current_Index();

	T Current();
*/