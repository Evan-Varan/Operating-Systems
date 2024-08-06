Evan Varan 7/9/24

A linked list c and header file are included as well as a vector c and header file to help with program flow.

1. pre.c:
Upon running pre.c it will prompt you to enter student names and GPAs. To do this enter a name and then a space and then a double after the space.
Press enter to go to the next line and enter another input if needed. Press CTRL + D on a new line to end input. Note that error checking is not included and if input is done incorrectly you will need to rerun the program.

Example input:
Evan 3.4
James 2.7
John 4.0
Amanda 3.1
Jessica 2.9
[CTRL+D]

Expected Output:
Evan
John
Amanda

2. sort.c:
Upon running sort.c it will prompt you to enter student names. To do this enter a name and then press enter to go to the next line and enter another input if needed. Press CTRL + D on a new line to end input. Note that error checking is not included and if input is done incorrectly you will need to rerun the program.

Example input:
Evan
John
Amanda
[CTRL+D]

Expected Output:
Amanda
Evan
John

3. pipe.c:
Input for pipe.c is the same as for pre.c in step 1.

Example input:
Evan 3.4
James 2.7
John 4.0
Amanda 3.1
Jessica 2.9
[CTRL+D]

Expected Output:
Amanda
Evan
John

4. parent.c:
Runs like a normal executable with parameters.

Example cmd line:
./parent.exe ls -l

Expected Output:
Printing current directory.
