/**
 * @brief p & v operations
 * 		Semaphore operations to control shared resources
 * 		2 Atomic operations, wait(P) and signal(V)
 * 		Also known as P(proberen - 'to test')
 * 					  V(verhogen - 'to increment')
 * 
 * @author Mitchel King
 * @date 17/11/2021
 * */

/**
 * @brief create, initialize and return semID
 * @param key - key used to create semaphore
 * @param semVal - value to initialize 'val' to
 * */
int getSem(int key, int semVal);

/**
 * @brief remove Sem
 * @param semId ID of semaphore to remove
 * */
void rmSem(int semId);

/**
 * @brief 'semWait - to test'
 *      SEM_UNDO version
 *      SEM_UNDO, semaphores adjust on exit value
 *      is decremented by sem_op's value.
 * 
 *      A positive value for sem_op generally corresponds
 *      to a process releasing a resource associated with the
 *      semaphore
 * 
 * @param semId
 * */
void p(int semId);

/**
 * @brief 'semSignal - to increment'
 *      SEM_UNDO version
 *      SEM_UNDO, semaphores adjust on exit value
 *      is decremented by sem_op's value.
 * 
 *      A positive value for sem_op generally corresponds
 *      to a process releasing a resource associated with the
 *      semaphore
 * 
 * @param semId
 * */
void v(int semId);

/**
 * @brief 'semWait - to test'
 *      No SEM_UNDO version
 * 
 * @param semId
 * */
void p0(int semId);

/**
 * @brief
 *      No SEM_UNDO version
 * 
 * @param semId
 * */
void v0(int semId);