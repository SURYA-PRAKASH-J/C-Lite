// C-Lite Functions Example
// Shows how to define and call functions/procedures with parameters.
// Note: C-Lite does not currently support return statements. Functions act as procedures.

// 1. Defining functions
// Function definitions start with the identifier name, followed by arguments,
// and the body. Return types are not specified.
greet() {
    echo "Hello, welcome to C-Lite functions!" endl;
}

printSquare(int n) {
    int square = n * n;
    echo "The square of " + n + " is " + square endl;
}

calculateSum(int valA, int valB) {
    int sum = valA + valB;
    echo "Sum of " + valA + " and " + valB + " is: " + sum endl;
}

// 2. Calling functions
echo "--- Function Execution ---" endl;
greet();
printSquare(7);
calculateSum(15, 27);
echo "";

// 3. Understanding Function Parameter Scoping Quirks
//
// In C-Lite's current interpreter implementation, function parameters are 
// evaluated and added to the CALLER'S scope level, rather than a new stack frame.
//
// This leads to two critical behaviors/quirks:
// 1. Parameter names must NOT conflict with existing variables in the caller's scope
//    (otherwise, a "Redeclared in same scope!" error occurs).
// 2. Parameters "leak" into the caller's scope and remain accessible after the call.
//
echo "--- Parameter Leakage & Scoping Showcase ---" endl;

// Let's call a function with a parameter name that doesn't exist in the global scope.
testScope(int tempParam) {
    echo "Inside testScope, tempParam = " + tempParam endl;
    tempParam = tempParam + 10;
    echo "Inside testScope, modified tempParam = " + tempParam endl;
}

testScope(5);

// Due to the scoping quirk, 'tempParam' was added to the global scope during the call,
// and it persists after the function finishes!
echo "Post-call: tempParam still exists globally and is: " + tempParam endl;

echo "";
echo "=== Done with Functions ===" endl;
