// Variable declaration
int a = 10;
echo a;  //print statement

a = a + 30 - (2 * 12); //Expression Handling
echo a; 

int b = 10 + a;
echo b;

//if statement example
if a < b {
    echo 1;
}

//if-else statment with nested if solution
int age = 17;

if age >= 18 {
    echo 1;
}else{
    echo 0;
    if(age==17){
        echo 11;
    }
}

//gloabl scope
int y = 10;

if 1 {
    int y = 20; //scoped variable - only works within the block
    echo y; //first look up y=20 if not exists goes to global scope for searching
}

echo y; //global y 10 gets printed


//while loop - iykyk
int i = 0;

while i < 5 {
    echo i;
    i = i + 1;
}