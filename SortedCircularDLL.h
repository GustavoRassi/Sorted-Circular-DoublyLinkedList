/*===============================================
*   Project: Sorted Circular Doubly Linked List
*   Author: Gustavo A. Rassi
*   Course: Data Structures and Algorithms
===============================================*/

#include <iostream>
#include "ListADT.h"
using namespace std;

// Node and its properties
template <class Type>
struct nodeType
{
	Type info;
	nodeType *next, *prev;
};

/*  
    This is a subclass, meaning that it inherits from a superclass. 
    In this case, the public part of ListADT.
*/
template <class Type>
class SortedCircularDLL : public ListADT<Type> 
{
    template <class T>
	friend std::ostream& operator<<(std::ostream&, const SortedCircularDLL<T>&); // Operator overload '<<'
    
    public: 
        SortedCircularDLL(); // Contructor: Creates dummy node and use pointer head to access the list
        SortedCircularDLL(const SortedCircularDLL<Type>&); // Copy constructor: Creates dummy node for the other list.
        ~SortedCircularDLL(); // Destructor: All nodes are removed and head pointer is deleted.

        const SortedCircularDLL<Type>& operator=(const SortedCircularDLL<Type>&); // Operator overload '='

        void add(const Type&); // Add a node to the list.
        void addAt(int, const Type&); // Add at position.
        bool remove(const Type&); // Remove node.
        bool removeAt(int); // Remove node at a position.
        int removeAll(const Type&); // Remove all copies of an element.
        Type getAt(int) const; // Retrieve element at a position.
        void setAt(int, const Type&); // Replace node at a position.
        Type getFirst() const; // Retrieve the first node.
        Type getLast() const; // Retrieve the last node.
        int firstIndex(const Type&) const; // Retrieves the first position where the element is found.
        int lastIndex(const Type&) const; // Retrieves the last position where the element is found.
        int count(const Type&) const; // Retrieves # of copies of an element.
        void clear(); // Emptys the list.
        void printReverse(); // Prints the list in reverse.

    private:
        nodeType<Type> *head;

        void copyList(const SortedCircularDLL<Type>&); // Copies the list to a new list.
};

/*************************************************
   CONSTRUCTOR - Creates head pointer that is 
   pointed at a "dummy head node" by default.

   Since it's a Circular DLL, tail won't exist.
   We will rely on the head, therefore, a dummy head node 
   is created, but not considered as part of the list.
   This means that the dummy head node will act
   like a door for us to access the list.
*/
template <class Type>
SortedCircularDLL<Type>::SortedCircularDLL()
{
    nodeType<Type> *dummyHead = new nodeType<Type>;
    head = dummyHead;
    dummyHead->next = head;
    dummyHead->prev = head;
    this->currentSize = 0;
}

/***************************
    COPY CONSTRUCTOR 
*/
template <class Type>
SortedCircularDLL<Type>::SortedCircularDLL(const SortedCircularDLL<Type>& secondList)
{
    // Creates copied list's dummy head node by default.
    // Node will point to itself to indicate that the list is empty.
    nodeType<Type> *dummyHead = new nodeType<Type>;
    head = dummyHead;
    dummyHead->next = head;
    dummyHead->prev = head;
    this->currentSize = 0;

    copyList(secondList);
}

/******************************************
   DESTRUCTOR
   
    Emptys the list and deletes head pointer.
*/
template <class Type>
SortedCircularDLL<Type>::~SortedCircularDLL()
{
    clear();
}


/******************************************
   COPYLIST - Creates a copy of the list.
*/
template <class Type>
void SortedCircularDLL<Type>::copyList(const SortedCircularDLL<Type>& secondList)
{
    int pos = 0;
    
    /* For every node the pointer points to, its content 
           will be added to the new/copied list. */
    while (pos < secondList.currentSize)
    {
        this->add(secondList.getAt(pos));
        pos++;
    }
}

/****************************************************
   OPERATOR OVERLOAD '<<'
   
   Modifies the output operator to print an object
   in main by looping thorugh the list and printing 
   every node and returning the output stream in the end.
*/
template <class Type>
std::ostream& operator<<(std::ostream& print, const SortedCircularDLL<Type>& list)
{
    // Takes the output stream and the object as parameters.
    // Check if the list is empty, to perform the execution.
    if(!list.isEmpty())
    {
        nodeType<Type> *currentptr = list.head->next;
        while(currentptr != list.head)
        {
            print << currentptr->info << " ";
            currentptr = currentptr->next;
        }
        cout << endl;
    }
    return print;
}

/******************************************
   OPERATOR OVERLOAD '='
   
   Modifies assignment operator to assign an object's 
   content to another object.
*/
template <class Type>
const SortedCircularDLL<Type>& SortedCircularDLL<Type>::operator=(const SortedCircularDLL<Type>& secondList)
{
    // To avoid self copying.
    if(this != &secondList)
        copyList(secondList);
    return *this;
}

/******************************************
   ADD - Adds a new node to the list.
   
   Since it's a sorted list, the node
   will be place in a smallest-to-biggest
   sequence
*/
template <class Type>
void SortedCircularDLL<Type>::add(const Type& value)
{
    nodeType<Type> *newNode = new nodeType<Type>;
    nodeType<Type> *currentptr; // Pointer to traverse the list
    newNode->info = value; // Have the new node ready beforehand

    // First, check if the list is empty
    if(this->isEmpty())
    {
        newNode->prev = head;
        head->next = newNode;
        newNode->next = head;
        head->prev = newNode;
    }
    else
    {
        currentptr = head->next;
        while(currentptr != head)
        {
            // New node is compared to all the other nodes.
            if(value <= currentptr->info)
            {
                newNode->next = currentptr;
                newNode->prev = currentptr->prev;
                currentptr->prev->next = newNode;
                currentptr->prev = newNode;
                break;
            }
            // New node is the biggest one, so it will be placed at the end of the list or before head.
            if(value > currentptr->info && currentptr->next == head) 
            {
                newNode->next = currentptr->next;
                newNode->prev = currentptr;
                currentptr->next->prev = newNode;
                currentptr->next = newNode;
                break;
            }
            currentptr = currentptr->next;
        }
    }
    // Node is added in the list, so its size increments by 1.
    this->currentSize++;
}

/******************************************
   ADDAT - Adds a new node at a certain 
           position in the list.
   
   Due to being a sorted list, the position
   won't matter, avoiding the list to break
   its order.
*/
template <class Type>
void SortedCircularDLL<Type>::addAt(int pos, const Type& value)
{
    // No position needed, so just add the value and add() will do the job.
    add(value);
}


/******************************************
   FIRSTINDEX - Finds the position where
                the element is first found.
   
   Returns: Retrieves the position where
            the element is found If not,
            returns -1.
*/
template <class Type>
int SortedCircularDLL<Type>::firstIndex(const Type& value) const
{
    nodeType<Type> *currentptr = head->next; // Pointer to traverse the list.
    int pos = 0;
    
    while(currentptr != head)
    {
        if(currentptr->info == value) // Found it.
            return pos;
        // Not there, so go to the next node.
        currentptr = currentptr->next;
        pos++;
    }
    return -1; // If not found
}

/******************************************
   LASTINDEX - Finds the position where
            the element is first found.
   
   Since it's a sorted list, the node
   will be place in a smallest-to-biggest
   sequence
*/
template <class Type>
int SortedCircularDLL<Type>::lastIndex(const Type& value) const
{
    nodeType<Type> *currentptr = head->prev; // Pointer to traverse the list.
    int pos = this->currentSize - 1; // Start iteration at the end of the list.

    while(currentptr != head)
    {
        if(currentptr->info == value) // Found the node!
            return pos;
        else // Wasn't there, so go to the next node (->prev)
        {
            currentptr = currentptr->prev;
            pos--;
        }
    }
    return -1; // Never found it
}

/******************************************
   COUNT - Counts how many copies of are of
           an element
   
   Returns: # of copies of an element
*/
template <class Type>
int SortedCircularDLL<Type>::count(const Type& value) const
{
    nodeType<Type> *currentptr = head->next; // Pointer to traverse the list
    int found = 0;

    while (currentptr != head)
    {
        // Found one! But keep looking if there are more
        if(currentptr->info == value)
            found++;
        
        currentptr = currentptr->next;
    }

    return found;
}


/******************************************
   GETAT - Retrieves the element at a cretain
           position.
   
   Returns the element at position 'pos'
*/template <class Type>
Type SortedCircularDLL<Type>::getAt(int pos) const
{
    nodeType<Type> *currentptr = head->next;

    // Exception
    if(pos < 0 || pos > this->size() - 1)
        throw std::out_of_range("Out of range.");
    
    // Traverse the list until you get to the node you want.
    for(int i = 0; i < pos; i++)
        currentptr = currentptr->next;

    return currentptr->info;
}

/******************************************
   SETAT - Replaces a node with a position
           and the element to be replaced with.
   
   We use the position to remove a node and
   adding a new one. The add() will do its job
   of putting it in order.
*/
template <class Type>
void SortedCircularDLL<Type>::setAt(int pos, const Type& value)
{
    removeAt(pos);
    add(value);
}

/************************************************************
    GETFIRST - Retrieves first node.
*/
template <class Type>
Type SortedCircularDLL<Type>::getFirst() const
{
    return head->next->info; // Returns first node
}

/************************************************************
    GETLAST - Retrieves last node.
*/
template <class Type>
Type SortedCircularDLL<Type>::getLast() const
{
    return head->prev->info; // Returns last node
}


/************************************************************
    REMOVE - Searches for the node and removes it.
    
    If the node is found, it will get removed.
    Returns: true if found, false if not found.
*/
template <class Type>
bool SortedCircularDLL<Type>::remove(const Type& value)
{
    // Check if it's empty
    if(this->isEmpty())
        return false;
    else
    {

        nodeType<Type> *currentptr = head->next;
        while (currentptr != head)
        {
            if(currentptr->info == value) // Node found!
            {
                currentptr->prev->next = currentptr->next;
                currentptr->next->prev = currentptr->prev;
                this->currentSize--;
                return true;
            }
            else // Not in current node, so go to the next one
                currentptr = currentptr->next;
        }
        return false; // Node never found
    }
}

/************************************************************
    REMOVEAT - Removes element/node at a "position".
    
    If the node is found, it will get removed.
    Returns: true if found, false if not found.
*/
template <class Type>
bool SortedCircularDLL<Type>::removeAt(int pos)
{
    // Catch exception
    if(pos < 0 || pos > this->size())
        return false;
    else
    {
        nodeType<Type> *currentptr = head->next;

        for(int i = 0; i <= pos; i++) 
            currentptr = currentptr->next;

        // Arrived at the node to be removed

        currentptr->prev->next = currentptr->next;
        currentptr->next->prev = currentptr->prev;

        delete currentptr;
        this->currentSize--;

        return true;
    }
}

/************************************************************
    REMOVEALL - Removes all copies of the element.
    
    If the element is found, node will be removed.
    Returns: true if found, false if not found.
*/
template <class Type>
int SortedCircularDLL<Type>::removeAll(const Type& value)
{
    int counter = 0;

    // Counts how many times a copy of the element was found and removed
    while(remove(value)) 
        counter++;

    return counter; // If no node was removed, return 0
}

/************************************************************
    CLEAR - Emptys the list
    
    Traverse the list and removes every node, until
    "dummy head node" is the only node left.
*/
template <class Type>
void SortedCircularDLL<Type>::clear()
{
    nodeType<Type> *remvptr; // Pointer to remove the nodes
    nodeType<Type> *currentptr = head->next; // Pointer to traverse the list
    
    // remvptr uses currentptr to move to the next node after deleting one.
    while(currentptr != head)
    {
        remvptr = currentptr;
        currentptr = currentptr->next;

        remvptr->prev->next = currentptr;
        currentptr->prev = remvptr->prev;
        delete remvptr;

        this->currentSize--;
    }
    // List is now empty.
    if(currentptr == head)
        head->next = head->prev = head;
}

/***************************************************************
    PRINTREVERSE - Prints the list from last tp first node.
    
    A pointer will start at previous of head and stops at the
    beginning of the list.
*/
template <class Type>
void SortedCircularDLL<Type>::printReverse()
{
    nodeType<Type> *currentptr;

    // Start printing from the last node to the first one using prev pointers.
    for(currentptr = head->prev; currentptr != head; currentptr = currentptr->prev)
        cout << currentptr->info << " ";
    cout << endl;
}