#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "List.h"

#define MAX_LEN 300

using namespace std;

void shuffle(List& D) {
    int n = D.length();
    int mid = n / 2;
    List left, right;
    
    D.moveFront();

    for (int i = 0; i < mid; i++) {
        left.moveBack();
        left.insertBefore(D.peekNext());
        D.moveNext();
    }
    while(D.position() < n) {
        right.moveBack();
        right.insertBefore(D.peekNext());
        D.moveNext();
    }

    D.clear();
    left.moveFront();
    right.moveFront();
    
    while (left.position() < left.length() && right.position() < right.length()) {
        D.insertBefore(right.peekNext());
        right.moveNext();
        D.insertBefore(left.peekNext());
        left.moveNext();
    }
    while (left.position() < left.length()) {
        D.insertBefore(left.peekNext());
        left.moveNext();
    }
    while (right.position() < right.length()) {
        D.insertBefore(right.peekNext());
        right.moveNext();
    }
}

int main(int argc, char* argv[]) {
    FILE* in, * out;

    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int max_n = stoi(argv[1]);

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    
    for (int n = 1; n <= max_n; n++) {
        List D;
        
        for (int i = 0; i < n; i++) {
            D.insertBefore(i);
        }
        
        int count = 0;
        List original = D;
        
        do {
            shuffle(D);
            count++;
        } while (!D.equals(original));
        
        fprintf(out, "%d        %d", n, count);
        fprintf(out, "\n");
    }
    
    fclose(in);
    fclose(out);
       
    return 0;
}
