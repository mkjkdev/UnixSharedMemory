# UnixSharedMemory
Unix shared memory example. Sharing a memory address between 2 processes.
Access is controlled using Semaphores, and the 2 atomic operations associated with them.
P(to test) and V(to increment)

The producer prompts the user for input, sends the input to the shared pointer until user enters 'end'.
The consumer collects all input from the shared pointer, and displays these to the user.
Once the producer has finished, the consumer calculates the average of all 'marks' produced.

<img width="480" alt="image" src="https://user-images.githubusercontent.com/24711964/142520167-eb521ab0-8b3e-438c-a831-78ed80197114.png">
<img width="297" alt="image" src="https://user-images.githubusercontent.com/24711964/142520194-60e10b5d-a3bd-4442-9ccd-b8dcbf73b4b2.png">
