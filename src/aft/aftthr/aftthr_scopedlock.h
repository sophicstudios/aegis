#ifndef INCLUDE_AEGIS_AFTTHR_SCOPEDLOCK_H
#define INCLUDE_AEGIS_AFTTHR_SCOPEDLOCK_H

namespace aftthr {

template<typename T>
class ScopedLock
{
public:
    ScopedLock(T& mutex);

    ~ScopedLock();
    
private:
    T& m_mutex;
};

template<typename T>
inline ScopedLock<T>::ScopedLock(T& mutex)
: m_mutex(mutex)
{
    m_mutex.lock();
}

template<typename T>
inline ScopedLock<T>::~ScopedLock()
{
    m_mutex.unlock();
}

template<typename T>
ScopedLock<T> make_scoped(T& mutex)
{
    return ScopedLock<T>(mutex);
}

} // namespace

#endif // INCLUDE
