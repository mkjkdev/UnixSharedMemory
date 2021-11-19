# UnixSharedMemory
Unix shared memory example. Sharing a memory address between 2 processes.
Access is controlled using Semaphores, and the 2 atomic operations associated with them.
P(to test) and V(to increment)

The producer prompts the user for input, sends the input to the shared pointer until user enters 'end'.
The consumer collects all input from the shared pointer, and displays these to the user.
Once the producer has finished, the consumer calculates the average of all 'marks' produced.
