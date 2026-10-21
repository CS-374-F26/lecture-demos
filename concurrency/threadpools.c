// A very common strategy in multithreading is to create a thread pool
// at the start of the application. All of these N threads simply do the
// following:
//
// 1. Wait until a) a shared queue of tasks is NOT empty, or b) the queue
// 	is said to be "closed". A closed queue is a queue which will have
// 	no more tasks added to it, ever.
// 2. If the queue is not empty, dequeue a task from the queue, and carry it out
//    Else, we terminate
// 3. Repeat from step 1
//
// At the same time, the main thread will occasionally add tasks to the queue,
// representing work that needs to be done.
//
// There are very good reasons to decouple your tasks from your threads.
// 1. Creating threads is particularly expensive.
// 2. System calls are somewhat expensive. In particular, pthread_mutex_lock()
// 	and pthread_mutex_unlock() are going to be called a lot by every
// 	thread.
// 3. The more threads you have competing for the same shared resource,
// 	the more resource contention you have.
// 4. The more threads you have, the more time the CPU scheduler will spend
//    rotating them in and out of the CPU. These context switches are
//    expensive.

