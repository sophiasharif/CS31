
#include <iostream>
#include <cassert>
using namespace std;

// helper function to check if two arrays are equal
bool checkEqual(string arr1[], int n1, string arr2[], int n2){
    if (n1 != n2)
        return false;
    
    for (int i = 0; i < n1; i++){
        if (arr1[i] != arr2[i])
            return false;
    }
    
    return true;
}

// appends value to the end of each of the n elements of the array
// returns n
int appendToAll(string a[], int n, string value) {
    
    // check for invalid inputs
    if (n < 0)
        return -1;
    
    // append value to each elem in array
    for (int i = 0; i < n; i++)
        a[i] += value;
    
    return n;
}

// returns smallest position of elem in array that is equal to target
// returns -1 if no matches
int lookup(const string a[], int n, string target) {
    
    // check for invalid inputs
    if (n < 0)
        return -1;
    
    // look for matches
    for (int i = 0; i < n; i++) {
        if (a[i] == target)
            return i;
    }
    
    // no matches - return -1
    return -1;
}

// returns smallest position of the greatest (>=) string in the array.
// returns -1 if array has no interesting elems
int positionOfMax(const string a[], int n) {
    
    // check for invalid inputs & array of length 0
    if (n <= 0)
        return -1;
    
    int greatest = 0;
    
    for (int i = 0; i < n; i++){
        if (a[i] > a[greatest])
            greatest = i;
    }
    
    return greatest;
}

// eliminates item at position pos; copies all elements after it one places to the left
// eliminated item is put at the end of the array
// returns original position of item
int rotateLeft(string a[], int n, int pos){
    
    // check for invalid inputs & array of length 0
    if (n <= 0 || pos >= n || pos < 0)
        return -1;
    
    string itemToDelete = a[pos];
    for (int i = pos; i < n-1; i++){
        a[i] = a[i+1];
    }
    a[n-1] = itemToDelete;
    
    return pos;
}

// returns the number of sequences of one or more consecutive identical items in a.
int countRuns(const string a[], int n){
    
    // check for invalid inputs
    if (n < 0)
        return -1;
    
    // edge cases
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    
    int numRuns = 0;
    string last = a[0];
    
    // iterate through array items & compare to last item
    for (int i = 1; i < n; i++){
        string current = a[i];
        
        if (current == last)
            continue;
        
        numRuns += 1;
        last = current;
    }
    
    // account for last run
    numRuns++;
    
    return numRuns;
}

// reverses the order of the elements of the array and returns n.
int flip(string a[], int n) {
    
    // check for invalid inputs
    if (n < 0)
        return -1;
    
    int numFlips = n / 2;
    
    // iterate through first half of array and flip each set of elem
    for (int i=0; i<numFlips; i++){
        int j = n - 1 - i;
        string temp = a[i];
        
        a[i] = a[j];
        a[j] = temp;
    }
    
    return n;
}

// Returns pos of first corresponding elements of a1 and a2 that are not equal
// n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2
// If the arrays are equal up to the point where one or both runs out, returns whichever value of n1 and n2 is less than or equal to the other.
int differ(const string a1[], int n1, const string a2[], int n2){
    
    // check invalid inputs
    if (n1 < 0 || n2 < 0 || (n1 == 0 && n2 == 0))
        return -1;
    
    int smallerN = min(n1, n2);
    
    for (int i = 0; i < smallerN; i++){
        if (a1[i] != a2[i])
            return i;
    }
    
    return smallerN;
}

// if a2 is a subsequence of a1, returns starting index of subsequence in a1
// if a1 is not a subsequence, return -1
// sequency of 0 elems is a subsequence of any sequence.
int subsequence(const string a1[], int n1, const string a2[], int n2){
    
    // check valid inputs
    if (n1 < 0 || n2 < 0 || n1 < n2)
        return -1;
    
    // edge case: n2 is the empty array; return 0 index
    if (n2 == 0 || (n1 == 0 && n2 == 0))
        return 0;
    
    for (int i = 0; i < n1 -1 ; i++) {
        // if elems do not match, continue
        if (a1[i] != a2[0])
            continue;
        
        // if elems match, check if it is a subsequence
        for (int j = 0; j < n2; j++){
            if (a1[i+j] != a2[j])
                break;
            if (j == n2-1)
                // if we have made it here, we have found a subsequence
                return i;
        }
    }
    
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    
    // invalid inputs or empty arrays
    if (n1 <= 0 || n2 <= 0)
        return -1;
    
    // loop through elems in a1
    for (int i = 0; i < n1; i++) {
        // check if elem is in a2
        if (lookup(a2, n2, a1[i]) != -1)
            return i;
    }
    
    return -1;
    
}

int split(string a[], int n, string splitter){
    
    // check for invalid inputs
    if (n < 0)
        return -1;

  
    // start at the end of the array
    // if a element is >= the splitter, send the element to the back
    // track index where the splitter would be if it were in the array
    int splitterIndex = 0;
    for (int i = n-1; i >= 0; i-- ){
        if (a[i] >= splitter)
            rotateLeft(a, n, i);
        else
            splitterIndex++;
    }
    
    // now, starting at the splitterIndex, send any elems greater than the splitter to the back
    for (int i = 0 ; i < n; i++ ){
        // if we encounter an elem == splitter, bring it to splitterIndex
        if (a[i] == splitter) {
            string temp = a[splitterIndex];
            a[splitterIndex] = a[i];
            a[i] = temp;
            splitterIndex++;
        }
    }
    
    // find the first element not less than splitter
    for (int i = 0; i < n; i++) {
        if ( a[i] >= splitter)
            return i;
    }
    
    return n;
}


int main() {
    string test0[0] = {};
    string test1[1] = {"test"};
    string test2[2] = {"test", "tester"};
    
    // appendToAll Tests
    string a[6] = {"hi", "hello", "this", "is", "a", "test"};
    assert(appendToAll(a, -3, "wow!") == -1); // negative array size
    assert(appendToAll(a, 6, "wow!") == 6); // check return value
    
    // lookUp Tests
    string b[6] = {"hi", "hello", "this", "is", "a", "test"};
    assert(lookup(b, -3, "this") == -1); // negative array size
    assert(lookup(b, 6, "this") == 2); // success case
    assert(lookup(b, 6, "yo") == -1); // fail case
    assert(lookup(b, 6, "test") == 5); // edge case: looking up last elem
    
    // positionOfMax Tests
    string pm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
    assert(positionOfMax(pm, -6) == -1); // negative array size

    assert(positionOfMax(pm, 6) == 3); // success case
    assert(positionOfMax(pm, 0) == -1); // edge case: array is empty
    assert(positionOfMax(pm, 1) == 0); // edge case: array is of length 1
    assert(positionOfMax(pm, 4) == 3); // edge case: last elem is greatest
    
    // rotateLeft Tests
    string mp[5] = { "john", "david", "liz", "theresa", "margaret" };
    string rotatedmp[5] = {"john", "liz", "theresa", "margaret", "david"};
    assert(rotateLeft(mp, 5, 1) == 1); // success
    assert(checkEqual(mp, 5, rotatedmp, 5));
    assert(rotateLeft(mp, 0, 0) == -1); // array of length 0
    assert(rotateLeft(mp, 5, 5) == -1); // invalid position
    assert(rotateLeft(mp, 5, 6) == -1); // invalid position
    
    // countRuns Tests
    assert(countRuns(test0, -1) == -1); // invalid input
    assert(countRuns(test0, 0) == 0); // empty array
    assert(countRuns(test1, 1) == 1); // array of length 1
    assert(countRuns(test2, 2) == 2); // normal case
    string d[9] = {
        "tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"
    };
    assert(countRuns(d, 9) == 5);
    string boris[5] = {"boris", "boris", "boris", "boris", "boris"};
    assert(countRuns(boris, 5) == 1); // only one sequency

    // flip tests
    assert(flip(test0, -1) == -1); // invalid input
    assert(flip(test0, 0) == 0);
    assert(flip(test1, 1) == 1);
    assert(test1[0] == "test");
    assert(flip(test2, 2) == 2); // even number of elements
    assert(test2[0] == "tester" && test2[1] == "test"); // check it flipped
    string leaders[5] = { "boris", "", "tony", "theresa", "david" };
    string reversedLeaders[5] = {"david", "theresa", "tony", "", "boris"};
    assert(flip(leaders, 5) == 5);
    assert(checkEqual(leaders, 5, reversedLeaders, 5));
    
    // differ tests
    string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
    string politician[5] = { "boris", "rishi", "david", "", "tony" };
    assert(differ(leader, 6, politician, 5) == 2);
    assert(differ(leader, 2, politician, 1) == 1);
    assert(differ(test0, 0, politician, 5) == 0); // empty array
    assert(differ(test0, 0, politician, -5)); // invalid input
    assert(differ(test1, 1, leader, 6) == 0);
    
    // subsequence tests
    string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string names1[10] = { "margaret", "theresa", "rishi" };
    assert(subsequence(names, 6, names1, 3) == 1);
    string names2[10] = { "john", "rishi" };
    assert(subsequence(names, 5, names2, 2) == -1);
    
    // lookup any tests
    string names0[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string set1[10] = { "david", "boris", "rishi", "margaret" };
    assert(lookupAny(names0, 6, set1, 4) == 1);  // returns 1 (a1 has "margaret" there)
    string set2[10] = { "tony", "gordon" };
    assert(lookupAny(names0, 6, set2, 2) == -1);  // returns -1 (a1 has none)
    assert(lookupAny(names0, -5, set2, 2) == -1 ); // invalid inputs
    assert(lookupAny(test0, 0, set2, 2) == -1 ); // empty array
    
    // split tests
    string pam[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
    assert(split(pam, 6, "john") == 3);
    string pam2[4] = { "margaret", "theresa", "liz", "rishi" };
    assert(split(pam2, 4, "rishi") == 2);  //  returns 2
    assert(split(test0, 0, "a") == 0); // edge case: empty array
    assert(split(test1, 1, "a") == 0); // edge case: array of 1
    assert(split(test1, 1, "z") == 1); // edge case: array of 1
    assert(split(pam, 6, "zoe") == 6); // splitter is greater than all

    
    cout << "success!" << endl;
    
    return 0;
}
