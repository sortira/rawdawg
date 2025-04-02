echo Compiling the test suite
gcc -o test_suite.exe  -Ialg -Iexec -Imath test/test.c -O3 -Wall
