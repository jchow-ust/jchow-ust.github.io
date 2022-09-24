#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

//Checks whether a given string contains only math operators
bool is_operator(const string &str) {
    return str.find_first_not_of("+-*/") == string::npos;
}
 
//Checks whether a given string contains only digits
bool is_digits(const string &str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

//TODO: Returns a vector storing the numbers and operators of the input formula
vector<string> store_the_formula(const string &formula) {
    vector<string> f;
    std::stringstream ss(formula);
    string s;
    while (getline(ss, s, ' ')){
    	f.push_back(s);
    }

    /*
    string temp="";
    for (const char &c: formula){
    	if (c!=' '){
    		temp += c;
    		cout << c << endl;
    	}
    	else{
    		f.push_back(temp);
    		temp="";
    	}
    }
    */

    //f.push_back("+"); f.push_back("+"); f.push_back("2"); f.push_back("*"); f.push_back("3"); f.push_back("-"); f.push_back("10"); f.push_back("4"); f.push_back("/"); f.push_back("8"); f.push_back("4");
    //f.push_back("5"); f.push_back("2"); f.push_back("1"); f.push_back("/"); f.push_back("4"); f.push_back("*"); f.push_back("+"); f.push_back("3"); f.push_back("-");

    // (8/4)+(10-4)*3+2 = 22
    // 5+(2/1)*4-3 = 10
    return f;
}

//TODO: Print the calulation steps of the given formula. You must use iterators to traverse the formula 
//vector and a stack and to evaluate the formula, as explained in the lab description. First you need to determine 
//whether a formula is in Polish or Reverse Polish notation.
//Hint: You may use is_digits and is_operators to tell apart Polish Notation and Reverse Polish Notation.
void calculation_steps(vector<string> sequence) {
    stack<int> stk;
    //vector<string>::const_iterator begin;
    //vector<string>::const_iterator end;


    if (is_digits(*sequence.begin())){// left-right traversal (reverse Polish)
    	for (vector<string>::const_iterator it = sequence.begin(); it != sequence.end(); ++it){
    		if (is_digits(*it)){
    			try{
    				stk.push(stoi(*it)); // cant be nullptr
    				cout << "push " << *it << " to the stack." << endl;
    			}
    			catch(exception &err){
    				// can't "stoi" the end of the string
    			}
    		}
    		else{// must be operator
    			int a = stk.top(); stk.pop();
    			cout << "pop " << a << " from the stack." << endl;
    			int b = stk.top(); stk.pop();
    			cout << "pop " << b << " from the stack." << endl;
    			int c = -2931934;
    			if (*it=="+"){
    				c = b+a;
    			}
    			else if (*it=="-"){
    				c = b-a;
    			}
    			else if (*it=="*"){
    				c = b*a;
    			}
    			else if (*it=="/"){
    				c = b/a;
    			}
    			cout << b << *it << a << "=" << c << endl;
    			cout << "push " << c << " to the stack." << endl;
    			stk.push(c);
    		}
    	}
    }
    else{// Polish order
    	for (vector<string>::const_reverse_iterator it = sequence.rbegin(); it != sequence.rend(); ++it){
    		if (is_digits(*it)){
    			try{
    				stk.push(stoi(*it)); // cant be nullptr
    				cout << "push " << *it << " to the stack." << endl;
    			}
    			catch(exception &err){
    				// can't "stoi" the end of the string
    			}
    		}
    		else{// must be operator
    			int a = stk.top(); stk.pop();
    			cout << "pop " << a << " from the stack." << endl;
    			int b = stk.top(); stk.pop();
    			cout << "pop " << b << " from the stack." << endl;
    			int c = -2931934;
    			if (*it=="+"){
    				c = a+b;
    			}
    			else if (*it=="-"){
    				c = a-b;
    			}
    			else if (*it=="*"){
    				c = a*b;
    			}
    			else if (*it=="/"){
    				c = a/b;
    			}
    			cout << a << *it << b << "=" << c << endl;
    			cout << "push " << c << " to the stack." << endl;
    			stk.push(c);
    		}
    	}
    }
    cout << "Result: " << stk.top() << endl;
}

//Calculates and prints the result of evaluating a formula in Polish or Inverse Polish format. The formula may contain +-*/ operators
void calculation_result(const string &formula) {
    // transform the input string into the one with format of the corresponding notation 
    // and store it in a vector
    vector<string> sequence = store_the_formula(formula);

    // print the notation stored in the vector
    cout << "Formula:"<< " ";
    for(vector<string>::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        cout << *it << " ";
    }
    // calculate the result and print it out
    cout << endl << "Calculation steps: " << endl;
    calculation_steps(sequence);
}

int main() {
    cout << "Test 1:" << endl;
    string formula1 = "+ + 2 * 3 - 10 4 / 8 4";
    calculation_result(formula1);
    cout << endl << "Test 2:" << endl;
    string formula2 = "5 2 1 / 4 * + 3 -";
    calculation_result(formula2);
    return 0;
}
