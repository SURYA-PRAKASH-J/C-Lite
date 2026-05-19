echo "=== IMPLICIT CONVERSION TEST ===" endl;

string s = "Hello";
string empty = "";

int n = 42;
int zero = 0;

bool t = true;
bool f = false;

char c = 'A';



echo "" endl;
echo "=== STRING TO OTHERS ===" endl;

int si = s;
echo si endl;

bool sb = s;
echo sb endl;

char sc = s;
echo sc endl;



echo "" endl;
echo "=== EMPTY STRING ===" endl;

int esi = empty;
echo esi endl;

bool esb = empty;
echo esb endl;



echo "" endl;
echo "=== INT TO OTHERS ===" endl;

string ns = n;
echo ns endl;

bool nb = n;
echo nb endl;

char nc = n;
echo nc endl;



echo "" endl;
echo "=== ZERO INT ===" endl;

bool zb = zero;
echo zb endl;

string zs = zero;
echo zs endl;



echo "" endl;
echo "=== BOOL TO OTHERS ===" endl;

int ti = t;
echo ti endl;

string ts = t;
echo ts endl;

char tc = t;
echo tc endl;



echo "" endl;
echo "=== FALSE BOOL ===" endl;

int fi = f;
echo fi endl;

string fs = f;
echo fs endl;



echo "" endl;
echo "=== CHAR TO OTHERS ===" endl;

int ci = c;
echo ci endl;

string cs = c;
echo cs endl;

bool cb = c;
echo cb endl;



echo "" endl;
echo "=== OPERATION MIXING ===" endl;

echo "string + int = " + ("X" + 5) endl;

echo "string + bool = " + ("X" + true) endl;

echo "string + char = " + ("X" + 'A') endl;

echo "int + bool = ";
echo 5 + true endl;

echo "char + int = ";
echo 'A' + 1 endl;



echo "" endl;
echo "=== ASSIGNMENT ROUNDTRIP ===" endl;

string a = "Test";

int b = a;
echo b endl;

string c2 = b;
echo c2 endl;



echo "" endl;
echo "=== NESTED MADNESS ===" endl;

echo "Result: " + (("A" + 5) + true) endl;

echo "Check: " + ((5 > 2) + "OK") endl;



echo "" endl;
echo "=== DONE ===" endl;