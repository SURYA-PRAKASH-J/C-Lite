// C-Lite Basics Example
// Shows variable declarations, type checking, operators, and output.

// 1. Variable Declarations and Initialization
int count = 10;
bool active = true;
char grade = 'A';
string welcome = "Welcome to C-Lite!";

// 2. Printing Output
// The `echo` statement prints values. You can chain expressions.
// Use `endl` to print newlines.
echo "--- Basic Output ---" endl;
echo welcome endl;
echo "Initial count: " + count endl;
echo "Is active: " + active endl;
echo "Grade received: " + grade endl;
echo "";

// 3. Arithmetic Operations
echo "--- Arithmetic ---" endl;
int a = 20;
int b = 3;
int sum = a + b;
int diff = a - b;
int prod = a * b;
int quot = a / b; // Integer division

echo "a = " + a + ", b = " + b endl;
echo "a + b = " + sum endl;
echo "a - b = " + diff endl;
echo "a * b = " + prod endl;
echo "a / b = " + quot endl;
echo "";

// 4. Comparison and Logical Operations
echo "--- Comparison & Logic ---" endl;
bool isGreater = a > b;
bool isEqual = a == 20;
bool complexLogical = (a > b) && !active;

echo "a > b: " + isGreater endl;
echo "a == 20: " + isEqual endl;
echo "complex logical ((a > b) && !active): " + complexLogical endl;

echo "";
echo "=== Done with Basics ===" endl;
