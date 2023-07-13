//-----------------------------------------------------------------------------
// Brian Huang
// bryhuang@ucsc.edu
// 2023 Winter CSE101 PA5
// ListTest.cpp
// Test client for List ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include "List.h"

using namespace std;

int main(){

    // Create a new List
    List L;
    
    // Test length() on empty List
    cout << "Testing length() on empty List..." << endl;
    cout << "Expected: 0" << endl;
    cout << "Actual: " << L.length() << endl << endl;
    
    // Test moveFront() on empty List
    cout << "Testing moveFront() on empty List..." << endl;
    L.moveFront();
    cout << "Expected: List Error: calling moveFront() on NULL List reference" << endl;
    cout << "Actual: ";
    try{
        L.moveFront();
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    cout << endl;
    
    // Test moveBack() on empty List
    cout << "Testing moveBack() on empty List..." << endl;
    L.moveBack();
    cout << "Expected: List Error: calling moveBack() on NULL List reference" << endl;
    cout << "Actual: ";
    try{
        L.moveBack();
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    cout << endl;
    
    // Insert some elements
    L.insertBefore(10);
    L.insertBefore(20);
    L.insertAfter(30);
    
    // Test length() on non-empty List
    cout << "Testing length() on non-empty List..." << endl;
    cout << "Expected: 3" << endl;
    cout << "Actual: " << L.length() << endl << endl;
    
    // Test front() on non-empty List
    cout << "Testing front() on non-empty List..." << endl;
    cout << "Expected: 20" << endl;
    cout << "Actual: " << L.front() << endl << endl;
    
    // Test back() on non-empty List
    cout << "Testing back() on non-empty List..." << endl;
    cout << "Expected: 30" << endl;
    cout << "Actual: " << L.back() << endl << endl;
    
    // Test moveFront() on non-empty List
    cout << "Testing moveFront() on non-empty List..." << endl;
    L.moveFront();
    cout << "Expected: 20" << endl;
    cout << "Actual: " << L.peekNext() << endl << endl;
    
    // Test moveBack() on non-empty List
    cout << "Testing moveBack() on non-empty List..." << endl;
    L.moveBack();
    cout << "Expected: 30" << endl;
    cout << "Actual: " << L.peekPrev() << endl << endl;
    
    // Test moveNext() on non-empty List
    cout << "Testing moveNext() on non-empty List..." << endl;
    cout << "Expected: 30" << endl;
    cout << "Actual: " << L.moveNext() << endl << endl;
    
    // Test movePrev() on non-empty List
    cout << "Testing movePrev() on non-empty List..." << endl;
    cout << "Expected: 20" << endl;
    cout << "Actual: " << L.movePrev() << endl << endl;
    
    // Test insertBefore() on non-empty List
    cout << "Testing insertBefore() on non-empty List..." << endl;
    L.insertBefore(40);
    L.movePrev();
    cout << "Expected: 40" << endl;
    cout << "Actual: " << L
