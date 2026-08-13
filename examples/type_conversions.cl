// C-Lite Type Conversions Example
// Shows what implicit type coercions work and documents limitations.

echo "--- Working Implicit Conversions ---" endl;

// 1. String to Int Coercion
// Assigning a string to an integer variable assigns the LENGTH of the string.
string word = "Antigravity";
int len = word;
echo "String: " + word endl;
echo "Assigned to int (yields length): " + len endl;
echo "";

// 2. String to Char Coercion
// Assigning a string to a char variable assigns the FIRST CHARACTER of the string.
char firstChar = word;
echo "Assigned to char (yields first char): '" + firstChar + "'" endl;
echo "";

// 3. Char + Char Concatenation
// Adding two characters together yields a string containing both characters!
char x = 'C';
char y = 'L';
string both = x + y;
echo "Adding char 'C' and char 'L' yields string: " + both endl;
echo "";

// 4. Mixed-Type Concatenation in Expressions
// String concatenation automatically converts non-strings to strings.
int val = 42;
bool status = true;
char unit = 'm';
echo "Concatenation: " + val + " - " + status + " - " + unit endl;
echo "";

// === IMPORTANT LIMITATION / WARNING ===
// Assigning a non-string directly to a string variable is NOT supported and 
// will cause a segmentation fault in the current interpreter implementation.
//
// Unsupported/Crashes:
//   string s = 10;
//   string s = true;
//
// Instead, if you need to convert an int or bool to a string, concatenate it 
// with an empty string first:
//
// Supported Conversion via Concatenation:
int num = 123;
string numStr = "" + num;
echo "Converted int to string using concatenation: " + numStr endl;

echo "";
echo "=== Done with Type Conversions ===" endl;
