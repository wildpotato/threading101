# Threading 101
---
## Synchronization
### Primitives
[condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)

[uniquie_lock](https://en.cppreference.com/w/cpp/thread/unique_lock)

[lock_guard](https://en.cppreference.com/w/cpp/thread/lock_guard)

### Common Pattern
[monitor](https://web.stanford.edu/~ouster/cgi-bin/cs140-spring14/lecture.php?topic=locks)

### FAQs
[std::unique_lock VS std::lock_guard](https://stackoverflow.com/questions/20516773/stdunique-lockstdmutex-or-stdlock-guardstdmutex)

### Examples
    SimpleTimeAndCount

    threadWithClassObj

    twoThreadsWaiting

    waitCounterNotify
