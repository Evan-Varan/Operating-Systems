Run CompareProcesses.py in python to run the code

The page requests list is created with a random length chosen from 10-20 elements.
Each elements is chosen randomly to be either 1,2,3,4 or 5. This is all printed upon program start
The user is then prompted to enter a frame size which determines how many elements your physical memory list can hold.
For testing I used mainly frame size of 3 and 4.

Implementation of the code is done in two parts.
The first section runs the LRU algorithm and shows the physical memory and order of pages used after each page read in the requests list.
The second section runs the Optimal algorithm and also shows the physical memory after each page read in the requests list.

If the optimal algorithm reaches the end of the page requests list and cannot find a future occurence of multiple items in physical memory,
it will automatically replace the first element in the physical memory array that cannot be found in the future of the page requests list.

After both algorithms have been run, the code will display the number of page faults found using each algorithm.