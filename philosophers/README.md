# Philosophers

A C implementation of the **Dining Philosophers problem**, developed as part of the 42 Common Core learning path.

The program simulates philosophers sharing forks while eating, sleeping and thinking. Each philosopher runs in a separate thread; POSIX mutexes synchronize access to forks and shared state. The implementation uses a consistent fork-lock order to prevent circular deadlocks and a monitoring loop to detect starvation.


## Concepts covered

- Thread creation and lifecycle management with `pthread`.
- Mutex synchronization and the prevention of data races.
- Deadlocks, starvation and concurrent resource access.
- Time-sensitive monitoring and careful memory cleanup.
