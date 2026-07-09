char start = 'A';

foo(){

    echo "foo executed";
}

while(start != 'Z'){
    echo start;
    start = start+1;
}
foo();