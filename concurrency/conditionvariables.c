// The last access control mechanism is condition variables.

// A condition variable is a thing that supports two operations:
// 1. Wait on the condition variable until signaled
// 	Any time a condition variable is waited on, the mutex is
// 	automatically unlocked. Implication, the mutex MUST be locked
// 	at the time that you call pthread_cond_wait(). Whenever
// 	pthread_cond_wait() wakes up, it automatically relocks the mutex.
// 2. Signal waiter(s) on the condition variable.
// 	2.a. Signal ONE waiter
// 	2.b. Signal ALL waiters (broadcasting)
// 
// You MUST pair a condition variable with a mutex.
//
// The general pattern for using a condition variable is as follows:
//
// In the waiting thread:
// lock the mutex associated with the condition variable
// while (some condition is occurring) {
//     wait on the condition variable
// }
// unlock the mutex
//
// In some other thread:
// 
// lock the mutex associated with the condition variable
// modify one or more shared resources that change the
// 	current state of the condition that the waiting
// 	thread is waiting on
// unlock the mutex
// signal the condition variable (or broadcast)
