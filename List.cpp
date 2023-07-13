//-----------------------------------------------------------------------------
// Brian Huang
// bryhuang@ucsc.edu
// 2023 Winter CSE101 PA5
// List.cpp
// Implement file for List ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include "List.h"

using namespace std;

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    
    frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;
    
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    
    frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;
    
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    
    pos_cursor = 0;
    num_elements = 0;
        
    Node* N = L.frontDummy->next;
    
    while(N != L.backDummy){
        insertAfter(N -> data);
        N = N -> next;
    }
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    return frontDummy -> next -> data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    return backDummy -> prev -> data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(num_elements == 0){
        cerr << "List Error: calling peekNext() on NULL List reference" << endl;
        exit(EXIT_FAILURE);
    }
    
    return afterCursor -> data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if (pos_cursor <= 0) {
        throw std::range_error("List Error: peekPrev() called on first element or empty list");
    }
    
    return beforeCursor -> data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    Node* N = frontDummy -> next;
    while(N != backDummy) {
        Node* temp = N -> next;
        delete N;
        N = temp;
    }
    frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    if(num_elements == 0){
        cerr << "List Error: calling moveFront() on NULL List reference" << endl;
        exit(EXIT_FAILURE);
    }
    
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy -> next;
}


// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy -> prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext(){
    if(position() < length()){
        beforeCursor = afterCursor;
        afterCursor = afterCursor -> next;
        pos_cursor++;

        return beforeCursor -> data;
    }
    else{
        cerr << "List Error: calling moveNext() on NULL List reference" << endl;
        exit(EXIT_FAILURE);
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev(){
    if (pos_cursor <= 0) {
        throw std::range_error("List Error: movePrev() called on first element or empty list");
    }

    if(position() > 0){
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor -> prev;
        pos_cursor--;

        return afterCursor -> data;
    }
    else{
        cerr << "List Error: calling moveNext() on NULL List reference" << endl;
        exit(EXIT_FAILURE);
    }
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    N -> prev = beforeCursor;
    N -> next = beforeCursor -> next;
    beforeCursor -> next -> prev = N;
    beforeCursor -> next = N;
    afterCursor = beforeCursor -> next;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N = new Node(x);

    if(num_elements == 0){
        // Insert as the first element in the list
        frontDummy -> next = N;
        backDummy -> prev = N;
        N -> prev = frontDummy;
        N -> next = backDummy;
        beforeCursor = N;
        afterCursor = backDummy;
    }
    else{
        N -> prev = beforeCursor;
        N -> next = beforeCursor -> next;
        beforeCursor -> next -> prev = N;
        beforeCursor -> next = N;
        beforeCursor = N;
    }

    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if (pos_cursor <= 0) {
        throw std::range_error("List Error: setAfter() called on first element or empty list");
    }
    
    if(position() < length()){
        afterCursor -> data = x;
    }
    else{
        cerr << "List Error: setAfter() called on last element or empty list" << endl;
        exit(EXIT_FAILURE);
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if (pos_cursor <= 0) {
        throw std::range_error("List Error: setBefore() called on first element or empty list");
    }
    
    if(position() > 0){
        beforeCursor -> data = x;
    }
    else{
        cerr << "List Error: setAfter() called on first element or empty list" << endl;
        exit(EXIT_FAILURE);
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    
    if(position() < length()){
        if (afterCursor != backDummy) {
            Node* temp = afterCursor;
            afterCursor = afterCursor -> next;
            beforeCursor -> next = afterCursor;
            afterCursor -> prev = beforeCursor;
            
            delete temp;
            num_elements--;
        }
    }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if (pos_cursor <= 0) {
        throw std::range_error("List Error: eraseBefore() called on first element or empty list");
    }
    if(position() > 0){
        if (beforeCursor != frontDummy) {
            Node* temp = beforeCursor;
            beforeCursor = beforeCursor -> prev;
            afterCursor -> prev = beforeCursor;
            beforeCursor -> next = afterCursor;
            
            delete temp;
            pos_cursor--;
            num_elements--;
        }
    }
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x){
    while (afterCursor != backDummy) {
        
        if (afterCursor -> data == x) {
            beforeCursor = afterCursor;
            afterCursor = afterCursor->next;
            pos_cursor++;
            
            return pos_cursor;
        }
        
        afterCursor = afterCursor->next;
        pos_cursor++;
    }
    pos_cursor = num_elements;
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x){
    while(beforeCursor != frontDummy){
        if(beforeCursor -> data == x){
            afterCursor = beforeCursor;
            beforeCursor = beforeCursor -> prev;
            pos_cursor--;
            
            return pos_cursor;
        }
        
        beforeCursor = beforeCursor -> prev;
        pos_cursor--;
    }
    
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    Node* N = frontDummy -> next;
    
    while(N != backDummy){
        Node* M = N -> next;
        
        while(M != backDummy){
            if(M -> data == N -> data){
                Node* temp = M;
                M -> prev -> next = M -> next;
                M -> next -> prev = M -> prev;
                
                M = M -> next;
                delete temp;
                num_elements--;
            }
            else{
                M = M -> next;
            }
        }
        
        N = N -> next;
    }
    
    if(pos_cursor >= num_elements){
        moveBack();
    }
    else{
        moveFront();
        for(int i = 0; i < pos_cursor; i++){
            moveNext();
        }
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List M;

    for (Node* N = frontDummy -> next; N != backDummy; N = N -> next){
        M.insertBefore(N -> data);
    }

    for (Node* N = L.frontDummy -> next; N != L.backDummy; N = N -> next) {
        M.insertBefore(N -> data);
    }

    M.moveFront();
    return M;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    if(num_elements == 0){
        cerr << "List Error: calling to_string() on NULL List reference" << endl;
        exit(EXIT_FAILURE);
    }
    
    string s = "(";
    Node* N = frontDummy -> next;
    
    while(N != backDummy){
        s += std::to_string(N -> data);
        
        if(N -> next != backDummy){
            s += ", ";
        }
        
        N = N -> next;
    }
    
    s += ")";
    return s;
}


// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (num_elements == R.num_elements);

    if(eq){
        N = frontDummy -> next;
        M = R.frontDummy -> next;
        
        while(eq && N != backDummy){
            eq = (N -> data == M -> data);
            N = N -> next;
            M = M -> next;
        }
    }
    
    return eq;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L) {
    if(this != &L){
        List temp = L;
        
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    
    return *this;
}

