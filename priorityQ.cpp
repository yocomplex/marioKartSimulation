// Using 1 library and linked 1 header file for implementation
#include "priorityQ.h"
#include <cstdlib>

// Using namespace standard
using namespace std;

// Default constructor priorityQ that sets up an empty priority queue
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ() {
    capacity = 1; // Set capacity to 1
    size = 0; // Set size to 0
    heapArray = new priorityType[capacity]; // create a heapArray with the given capacity
}

// Copy Constructor priorityQ that deep copies the provided param
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(const priorityQ<t1, t2> &copy) {
    capacity = copy.capacity; // set capacity to copy capacity
    size = copy.size; // set size to copy size
    itemToPQ = copy.itemToPQ; // set item to priority queue to copy item to priorityQ
    heapArray = new priorityType[capacity]; // create a heapArray with the given capacity

    // For loop used to copy the elements of copy heapArray into heapArray
    for (size_t i = 0; i < size; ++i) {
        heapArray[i] = copy.heapArray[i];
    }
}

// Deep copy assignment operator overload
template <class t1, class t2>
const priorityQ <t1, t2> &priorityQ<t1, t2>::operator = (const priorityQ<t1, t2> &rhs) {
    if (this != &rhs) { 
        delete[] heapArray; // Delete the heap array

        capacity = rhs.capacity; // set capacity to rhs capacity
        size = rhs.size; // set size to rhs size
        heapArray = new priorityType[capacity]; // create heapArray with the size of the given capacity
        itemToPQ = rhs.itemToPQ; // set itemToPriorityQ to rhs itemToPriorityQ

        // For loop used to copy the elements of rhs heapArray into heapArray
        for (size_t i = 0; i < size; ++i) {
            heapArray[i] = rhs.heapArray[i];
        }
    }

    return *this; // Return *this
}

// Destructor
template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ() {
    delete[] heapArray; // Deletes the heap array
}

/* push_back function inserts a new priotityType object to the back of
   heapArray, maps this key to the last index of the heapArray and then
    calls bubbleUp(), resize heapArray by doubling its capacity */
template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1 &key, const t2 &priority) {
    if (size == capacity) { // If the size hits the max capacity
        capacity *= 2; // Doubling capacity
        // Creating a priorityType pointer newHeap array with the size of the given capacity
        priorityType *newHeap = new priorityType[capacity];
        
        // For loop used to copy the elements in heapArray into the newHeap array
        for (size_t i = 0; i < size; ++i) {
            newHeap[i] = heapArray[i];
        }

        delete[] heapArray; // Delete the old heapArray
        heapArray = newHeap; // Set the heapArray to the newHeap array
    }

    heapArray[size].priority = priority; // Set heapArray priority to priority
    heapArray[size].key = key; // Set heapArray key to key
    itemToPQ[key] = size; // Set the key to size;
    bubbleUp(size); // Call bubbleUp function
    ++size; // Pre-increment size
}

/* pop_front function assigns the last element of heapArray and assigns it to 
   the root position, updates the itemToPQ map accordingly, then call bubbleDown(0) */
template <class t1, class t2>
void priorityQ<t1, t2>::pop_front() {
    if (size == 0) { // If size of elements are empty
        return; // Exit out of the function
    }
    itemToPQ.erase(heapArray[0].key); // Erase the key in the heapArray
    --size; // Pre-decrement size
    if (size > 0) { // If size is greater than 0
        heapArray[0] = heapArray[size]; // Set heapArray at root 0 to heapArray
        itemToPQ[heapArray[0].key] = 0;  // Set heapArray key to 0 
        bubbleDown(0); // Call bubbleDown at root 0
    }
}

/* While using the decrease_priority function with the itemToPQ map, you update
   the value field of the element in the heapArray and then call bubbleUp
   using the index of where key parameter is in heapArray */
template <class t1, class t2>
void priorityQ<t1, t2>::decrease_priority(const t1 &key, const t2 &priority) {
    size_t i = itemToPQ[key]; // Set index to key
    heapArray[i].priority = priority; // Set heapArrays priority to priority
    bubbleUp(i); // Calling bubbleUp at index
}

// get_front_priority function returns the priority field of the root element
template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const {
    return heapArray[0].priority; // Returns priority of the root
}

// get_front_key returns the key field of the root element
template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const {
    return heapArray[0].key; // Return key of the root
}

/* isEmpty is a bool return function that returns true if 
   there is nothing in the priority queue and false otherwise */
template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const {
    if (size == 0) { // If amount of elements is empty
        return true; // Return true
    }
    return false; // Else by default return false
}

/* bubbleUp function performs the standard bubble up procedure by computing
   the parent index and compare the parent and child’s value fields, swap if 
   necessary, and continue up the tree until you can't bubble up anymore */
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(size_t index) {
    // Creating a parentIndex variable and setting it to (index - 1) / 2
    size_t parentIndex = (index - 1) / 2;

    /* While loop is for when index is greater than 0 AND the childs value
       is less than the parents value. If condition is met, swap the 
       element with the parent, update the key map, and move up the index. */
    while (index > 0 && heapArray[index].priority < heapArray[parentIndex].priority) {
        // Manually swap the current element with its parent
        priorityType temp = heapArray[index]; // Temp variable created to set to the child
        heapArray[index] = heapArray[parentIndex]; // Set the child to the parent
        heapArray[parentIndex] = temp; // Set the parent to the child

        // Update itemToPQ map
        // Set the childs index to the current index of child
        itemToPQ[heapArray[index].key] = index;
        // Set the parents index to the current index of parent
        itemToPQ[heapArray[parentIndex].key] = parentIndex;

        // Move up the index and update parentIndex
        index = parentIndex; // Set the childs index to parent
        parentIndex = (index - 1) / 2; // Go up to the next index
    }
}

/* bubbleDown function performs the standard bubble down procedure,
   using the parameter index, compute the left and right children indices
   and compare their value fields and swap the parent with the correct
   child and continue until you cannot bubble down any further */
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index) {
    while (true) { // While the condition is true
        // Create left, right, and smallest child variables
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;
        size_t smallestChild = index;

        // Find the index of the smallest left child
        if (leftChild < size && heapArray[leftChild].priority < heapArray[smallestChild].priority) {
            smallestChild = leftChild;
        }
        // Find the index of the smallest right child
        if (rightChild < size && heapArray[rightChild].priority < heapArray[smallestChild].priority) {
            smallestChild = rightChild;
        }

        // If the current node is the smallest
        if (smallestChild == index) {
            break; // Don't swap and break out of the loop
        }

        // Manually swap the current element with the smallest child
        // Create a temp variable and set it to the index of the value
        priorityType temp = heapArray[index];
        heapArray[index] = heapArray[smallestChild]; // Set the value to smallestChild
        heapArray[smallestChild] = temp; // Set smallestChild's value to temp

        // Update the item to priorityQ map
        // Set the values index to the current index
        itemToPQ[heapArray[index].key] = index;
        // Set the smallest childs value to the smallestChild
        itemToPQ[heapArray[smallestChild].key] = smallestChild;

        index = smallestChild; // Move down to the next index
    }
}
