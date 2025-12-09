// evaluate_expressions.cpp
#include <bits/stdc++.h>
using namespace std;

class Stack {
private:
    vector<long long> data;
public:
    void push(long long v){ data.push_back(v); }
    long long pop(){ long long v = data.back(); data.pop_back(); return v; }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

bool isOperator(const string& s) {
    return s=="+" || s=="-" || s=="*" || s=="/" || s=="^";
}

long long applyOp(const string& op, long long a, long long b) {
    if (op=="+") return a + b;
    if (op=="-") return a - b;
    if (op=="*") return a * b;
    if (op=="/") {
        if (b==0) throw runtime_error("Division by zero");
        return a / b;
    }
    if (op=="^") return (long long) pow((double)a, (double)b);
    throw runtime_error("Unknown operator");
}

// Evaluate postfix: tokens separated by spaces
long long evalPostfix(const string& expr) {
    istringstream iss(expr);
    string tok;
    Stack st;
    while (iss >> tok) {
        if (!isOperator(tok)) {
            st.push(stoll(tok));
        } else {
            if (st.size() < 2) throw runtime_error("Invalid postfix expression");
            long long b = st.pop();
            long long a = st.pop();
            st.push(applyOp(tok, a, b));
        }
    }
    if (st.size() != 1) throw runtime_error("Invalid postfix expression");
    return st.pop();
}

// Evaluate prefix: tokens separated by spaces
long long evalPrefix(const string& expr) {
    vector<string> tokens;
    istringstream iss(expr);
    string tok;
    while (iss >> tok) tokens.push_back(tok);
    Stack st;
    for (int i = (int)tokens.size()-1; i >= 0; --i) {
        tok = tokens[i];
        if (!isOperator(tok)) {
            st.push(stoll(tok));
        } else {
            if (st.size() < 2) throw runtime_error("Invalid prefix expression");
            long long a = st.pop();
            long long b = st.pop();
            st.push(applyOp(tok, a, b));
        }
    }
    if (st.size() != 1) throw runtime_error("Invalid prefix expression");
    return st.pop();
}

int main() {
    string postfix = "2 3 1 * + 9 -"; // (2 + (3*1)) - 9 = -4
    string prefix = "- + 2 * 3 1 9";  // same expression in prefix

    try {
        cout << "Postfix: " << postfix << " = " << evalPostfix(postfix) << "\n";
        cout << "Prefix: " << prefix << " = " << evalPrefix(prefix) << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
    // You can test more:
    cout << "Postfix example (5 1 2 + 4 * + 3 -) = " << evalPostfix("5 1 2 + 4 * + 3 -") << "\n";
    cout << "Prefix example (- + 5 * 4 3 2) = " << evalPrefix("- + 5 * 4 3 2") << "\n";
    return 0;
}
