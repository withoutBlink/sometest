#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

class RWLock
{
public:
	RWLock();
	~RWLock();

	bool LockR();
	bool TryLockR();

	bool LockW();
	bool TryLockW();

	bool UNLock();

private:
	pthread_rwlock_t _Lock;
};

#endif // RWLOCK_H
