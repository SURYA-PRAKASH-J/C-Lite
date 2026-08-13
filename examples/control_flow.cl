// C-Lite Control Flow Example
// Shows if-else statements, block scopes, variable shadowing, and loops.

// 1. Conditionals (if, else if, else)
echo "--- Conditionals ---" endl;
int score = 85;

if score >= 90 {
    echo "Excellent!" endl;
} else if score >= 80 {
    echo "Very Good!" endl;
} else {
    echo "Needs Improvement." endl;
}
echo "";

// 2. Block Scoping & Variable Shadowing
// Variables defined in inner blocks ({ }) shadow outer variables.
// They are cleaned up when the block exits.
echo "--- Scoping & Shadowing ---" endl;
int x = 100;
echo "Outer x before block: " + x endl;

if true {
    int x = 50; // Shadows the outer 'x'
    int y = 200; // Local variable inside block
    echo "Inner block x: " + x endl;
    echo "Inner block y: " + y endl;
}

echo "Outer x after block: " + x endl;
// echo y; // Error: y is undefined here
echo "";

// 3. While Loops
echo "--- While Loops ---" endl;
int count = 1;
int limit = 5;

while count <= limit {
    echo "Iteration " + count endl;
    count = count + 1;
}

echo "";
echo "=== Done with Control Flow ===" endl;
