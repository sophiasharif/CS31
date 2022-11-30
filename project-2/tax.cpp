//
//  main.cpp
//  project-2
//
//  Created by Sophia Sharif on 10/9/22.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // declare variables
    string name;
    double income;
    string occupation;
    int numChildren;

    double totalTax = 0;
    
    const double FIRST_BRACKET_TAX = .04;
    const int FIRST_BRACKET_CUTOFF = 55000;
    double SECOND_BRACKET_TAX = .07;
    const double SECOND_BRACKET_SPECIAL_TAX = .05;
    const int SECOND_BRACKET_CUTOFF = 70000;
    const double THIRD_BRACKET_TAX = .093;
    const int CHILD_TAX_BREAK = 200;
    
    // get inputs
    cout << "Name: ";
    getline(cin, name);
    cout << "Taxable income: ";
    cin >> income;
    cin.ignore(10000, '\n');
    cout << "Occupation: ";
    getline(cin, occupation);
    cout << "Number of children: ";
    cin >> numChildren;
    cout << "---" << endl;
    
    // check inputs are valid
    if (name == "")
        cout << "You must enter a name" << endl;
    else if (income < 0)
        cout << "The taxable income must not be negative" << endl;
    else if (occupation == "")
        cout << "You must enter an occupation" << endl;
    else if (numChildren < 0)
        cout << "The number of children must not be negative" << endl;
    
    // input are valid -- calculate tax
    else {
        // if occupation is nurse or teacher, adjust tax for second bracket
        if (occupation == "nurse" || occupation == "teacher")
            SECOND_BRACKET_TAX = SECOND_BRACKET_SPECIAL_TAX;
        
        // calculate child tax breaks
        double totalTaxBreak = 0;
        if (income < FIRST_BRACKET_CUTOFF + SECOND_BRACKET_CUTOFF)
            totalTaxBreak = numChildren * CHILD_TAX_BREAK;
        
        // TAX CALCULATION
        // first tax bracket
        if (income < FIRST_BRACKET_CUTOFF) {
            totalTax = income * FIRST_BRACKET_TAX;
        }
        else {
            totalTax += FIRST_BRACKET_CUTOFF * FIRST_BRACKET_TAX;
            income -= FIRST_BRACKET_CUTOFF;
            // second tax bracket
            if (income < SECOND_BRACKET_CUTOFF)
                totalTax += income * SECOND_BRACKET_TAX;
            else {
                totalTax += SECOND_BRACKET_CUTOFF * SECOND_BRACKET_TAX;
                income -= SECOND_BRACKET_CUTOFF;
                // third tax bracket
                totalTax += income * THIRD_BRACKET_TAX;
            }
        }
        
        // adjust for child tax breaks
        totalTax -= totalTaxBreak;
        if (totalTax < 0)
            totalTax = 0;
        
        cout << name << " would pay $" << fixed << setprecision(2) << totalTax << endl;
    }
    return 0;
}
