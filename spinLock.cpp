//copyright (c) 2020 by chrono

#ifndef _SPIN_LOCK_HPP_
#define _SPIN_LOCK_HPP_

#include "cpplang.hpp"

BEGIN_NAMESPACE(esbookshop)

class SpinLock final // final is used to prevent inheritance
{
    public:
    using this_type = SpinLock;
    using atomic_type = std::atomic_flag;

    public:
     SpinLock() = default; // default constructor
    ~SpinLock() = default; // destructor 

    SpinLock(const this_type&) = delete;   // disable copy constructor
    SpinLock& operator=(const this_type&) = delete; // disable copy assignment

    public:
        void lock() noexcept // noexcept is used to prevent exception 
        {
            for(;;){  // infinite loop
                if(!m_lock.test_and_set()){ // test_and_set is atomic operation,TAS
                    return;  // return if success
                }
                std::this_thread::yield(); // yield to other thread, fail
            }
        }
    bool try_lock() noexcept
    {
        return !m_lock.test_and_set(); // return true if lock is free
    } 
    void unlock() noexcept // unlock and prevent exception
    {
        m_lock.clear(); // release lock
    }

    private:
        atomic_type m_lock {false}; // member variable initialized to false
};  

    class SpinLockGuard final // RAII implementation to prevent deadlock ,lock when cosntructing , and unlock when necesary 
    {
        public:
            using this_type = SpinLockGuard; // alias
            using lock_type = SpinLock;
        public:
        SpinLockGuard(spin_lock_type& lock) noexcept// noexcept is used to prevent exception from being thrown in constructor , improve efficiency

            : m_lock(lock)
        {
            m_lock.lock();// lock in constructor
        }
        ~SpinLockGuard() noexcept
        {
            m_lock.unlock();// unlock in destructor
        }
    
    public:
        SpinLockGuard(const this_type&) = delete; // disable copy constructor
        SpinLockGuard& operator=(const this_type&) = delete; // disable copy assignment

    private:
      spin_lock_type& m_lock;
    }

END_NAMESPACE(esbookshop)

#endif // _SPIN_LOCK_HPP_