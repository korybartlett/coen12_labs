/*FILE: Creates functions that can be called upon by other main files in C++. The deque is a doubly linked list. In this file it has functions that will create the contents of a node, create the deque list, destory the deque, add a node to the beginning of a deque, add a node to the end of the deque, remove a node at the front of the deque, remove a node at the end of a deque, return the first deque, return the last deque, and return the size of the deque.
 */
# include <cassert>
# include "deque.h"

/*
*Creates the content of the nodes for use in the deque.
* O(1)
*/
class Node
{
    public://makes the pointers and data usable by the later functions
    int data;
    Node *next;
    Node *prev;
};

/*
 * Creates the deque. Intializes the values and pointers in the main deque.
 * O(1)
 */
Deque::Deque()
{
    count = 0;
    head = new Node;
    head->next = head;
    head->prev = head;
}

/*
 *Deletes every node in the the deque.
 *O(1)
 */
Deque::~Deque()
{
    Node *np, *next;
    
    np = head;
    //starts at the head and delets the nodes that follow
    do
    {
        next = np->next;
        delete np;
        np = next;
    }
    while (np != head);
}

/*
 * Adds a node in the first spot after the head node. Switches the pointers so that the list is kept as a circular doubly linked list.
 *O(1)
 */
void Deque::addFirst(int x)
{
    Node *np;
    
    
    
    np = new Node;
    np->data = x;
    
    count ++;
    
    //reassigns np pointers to be first in the list
    np->prev = head;
    np->next = head->next;
    
    //reassigns the pointers of the list to point at np as first
    head->next->prev = np;
    head->next = np;
}

/*
 * Adds a ndoe in the last spot before the dummy node. Switches the pointers so that the nodes are kept in circular doubly linked list.
 *O(1)
 */
void Deque::addLast(int x)
{
    Node *np;
    
    np = new Node;
    np->data = x;
    
    count ++;
    
    //reassigns the pointers of np so it is last in the list
    np->prev = head->prev;
    np->next = head;
    
    //reassigns the pointers of the list to point at np last
    head->prev->next = np;
    head->prev = np;
}

/*
 * removes the first node after the head node.
 *O(1)
 */
int Deque::removeFirst()
{
    assert(count > 0);
    int x;
    Node *np;
    count --;
    
    //arranges pointers to skip the fist node in the listso it can be deleted
    np = head->next;
    head->next = np->next;
    np->next->prev = head;
    
    x = np->data;
    delete np;
    return x;
}

/*
 * Removes the last node which is the node before the head node.
 *O(1)
 */
int Deque::removeLast()
{
    assert(count > 0);
    int x;
    Node *np, *sentinel;
    
    count --;
    
    //arranges pointers to skip the last node in the list so it can be deleted
    np = head->prev;
    head->prev = np->prev;
    np->prev->next = head;
    
    x = np->data;
    delete np;
    return x;
}


/*
 *Gets the first node that is after the head node.
 *O(1)
 */
int Deque::getFirst()
{
    assert(count > 0);
    return head->next->data;
}


/*
 *Gets the last node in the list which is the node before the head node.
 *O(1)
 */
int Deque::getLast()
{
    assert(count > 0);
    return head->prev->data;
}

/*
 *Returns the size of the deque by returning the count.
 *O(1)
 */
int Deque::size()
{
    return count;
}

