#include "rwlock.h"

RWLock::RWLock()
{
	if (pthread_rwlock_init(&this->_Lock, nullptr)) {
		LOG(ERROR) << "failed init read/write lock.";
	}
}

RWLock::~RWLock()
{
	if (pthread_rwlock_destroy(&this->_Lock)) {
		LOG(ERROR) << "failed destroy read/write lock.";
	}
}

bool RWLock::LockR()
{
	return pthread_rwlock_rdlock(&this->_Lock) == 0 ? true : false;
}

bool RWLock::TryLockR()
{
	return pthread_rwlock_tryrdlock(&this->_Lock) == 0 ? true : false;
}

bool RWLock::LockW()
{
	return pthread_rwlock_wrlock(&this->_Lock) == 0 ? true : false;
}

bool RWLock::TryLockW()
{
	return pthread_rwlock_trywrlock(&this->_Lock) == 0 ? true : false;
}

bool RWLock::UNLock()
{
	return pthread_rwlock_unlock(&this->_Lock) == 0 ? true : false;
}

