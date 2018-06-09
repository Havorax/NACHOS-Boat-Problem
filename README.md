# NACHOS-Boat-Problem
C++ solution to the "Boat problem" for NACHOS, along with Java translation. (For Operating Systems course)

---
## Boat.cpp
Prototyped solution to the [NACHOS](https://en.wikipedia.org/wiki/Not_Another_Completely_Heuristic_Operating_System) boat problem task. 

The task is in Java and uses NACHOS threads, but I programmed a solution in C++ (preferred language) and C++ 11 standard library threads. After confirming that the program worked, I translated it into Java, switching C++ thread calls to NACHOS thread calls.

## The Boat Problem:

Boat Problem, Project 1 PDF:
>"A number of Hawaiian adults and children are trying to get from Oahu to
>Molokai. Unfortunately, they have only one boat which can carry maximally two
>children or one adult (but not one child and one adult). The boat can be rowed
>back to Oahu, but it requires a pilot to do so.
>
>Arrange a solution to transfer everyone from Oahu to Molokai. You may assume
>that there are at least two children.
>
>Your solution must have no busy waiting, and it must eventually end. Note that it
>is not necessary to terminate all the threads -- you can leave them blocked waiting
>for a condition variable. The threads representing the adults and children cannot
>have access to the numbers of threads that were created
>
>The idea behind this task is to use independent threads to solve a problem. You
>are to program the logic that a child or an adult would follow if that person were
>in this situation. For example, it is reasonable to allow a person to see how many
>children or adults are on the same island they are on. A person could see whether
>the boat is at their island. A person can know which island they are on. All of this
>information may be stored with each individual thread or in shared variables. So a
>counter that holds the number of children on Oahu would be allowed, so long as
>only threads that represent people on Oahu could access it.
>
>What is not allowed is a thread which executes a "top-down" strategy for the
>simulation. For example, you may not create threads for children and adults, then
>have a controller thread simply send commands to them through communicators.
>The threads must act as if they were individuals.
>
>Information which is not possible in the real world is also not allowed. For
>example, a child on Molokai cannot magically see all of the people on Oahu. That
>child may remember the number of people that he or she has seen leaving, but the
>child may not view people on Oahu as if it were there. (Assume that the people do
>not have any technology other than a boat!)
>
>You will reach a point in your simulation where the adult and child threads
>believe that everyone is across on Molokai."
