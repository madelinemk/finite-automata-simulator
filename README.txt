Theory of Computing Project 1
Madeline Kusters

Compilation:
To compile my dfa.cpp program, run make in this directory.  The
executable produced is called dfa.exe.

Execution:
dfa.exe can be run with 2 command line arguments, the first is the
filename for the machine defintion, and the second it the filename for
the test strings.  If these arguments are not provided at the command
line, then the program will prompt the user for the filenames.

Output:
It will print out the name of the machine followed by all transition
rules for the machine, and print out each test string followed by each
step taken through the machine and then "Accepted" or "Rejected."

Test Cases:
All of Professor Kogge's test machine files are in the directory ./TestCases.

The test machine that I created is called
./TestCases/MadelineMachine.txt The test strings for this machine are
in files called ./TestCases/Madeline-Accept.txt and
./TestCases/Madeline-Reject.txt
