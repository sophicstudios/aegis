#ifndef INCLUDED_AEGIS_AFTU_NULLABLE_H
#define INCLUDED_AEGIS_AFTU_NULLABLE_H

#include <aftu_exception.h>
#include <aftu_typedbuffer.h>
#include <afts_compiler.h>
#include <boost/cstdint.hpp>
#include <exception>

namespace aftu {

template<typename T>
class Nullable
{
public:
    /**
     * Creates an instance of an object that is by default null
     */
    Nullable();
    
    /**
     * Creates an Nullable instance that is initialized
     * with a copy of the supplied value
     */
    explicit Nullable(T const& value);

    /**
     * Copy constructor
     */
	Nullable(Nullable<T> const& nullable);

    /**
     * Destructor
     */
	~Nullable();

    /**
     * Assignment operator using Nullable<T>
     */
	Nullable<T>& operator=(Nullable<T> const& nullable);

    /**
     * Assignment operator using type T
     */
    Nullable<T>& operator=(T const& value);
    
    /**
     * Makes the instance not null by assigning it a copy
     * of the supplied value
     */
	void makeValue(T const& value);

    /**
     * Destroys any existing value in the object and makes
     * the instance null
     */
    void makeNull();

    /**
     * Returns true if the instance is considered to be null
     */
	bool isNull() const;

    /**
     * Returns a read-only reference to the encapsulated value.
     * If the instance is null, an exception is thrown.
     */
    const T& value() const throw(std::exception);

    /**
     * Returns a writable reference to the encapsulated value.
     * If the instance is null, an exception is thrown.
     */
	T& value() throw(std::exception);

private:
    aftu::TypedBuffer<T> m_buffer;
	T* m_ptr;
};

template<typename T>
Nullable<T>::Nullable()
: m_ptr(0)
{}

template<typename T>
Nullable<T>::Nullable(const T& value)
: m_ptr(0)
{
	makeValue(value);
}

template<typename T>
Nullable<T>::Nullable(Nullable<T> const& nullable)
: m_ptr(0)
{
	*this = nullable;
}

template<typename T>
Nullable<T>::~Nullable()
{
	makeNull();
}

template<typename T>
Nullable<T>& Nullable<T>::operator=(Nullable<T> const& nullable)
{
	nullable.isNull() ? makeNull() : makeValue(nullable.value());

	return *this;
}

template<typename T>
Nullable<T>& Nullable<T>::operator=(T const& value)
{
    makeValue(value);

    return *this;
}

template<typename T>
void Nullable<T>::makeValue(T const& value)
{
    if (m_ptr) {
        m_ptr->~T();
    }

	m_ptr = new(m_buffer.data()) T(value);
}

template<typename T>
void Nullable<T>::makeNull()
{
	if (m_ptr) {
		m_ptr->~T();
		m_ptr = 0;
	}
}

template<typename T>
bool Nullable<T>::isNull() const
{
	return (m_ptr ? false : true);
}

template<typename T>
const T& Nullable<T>::value() const throw (std::exception)
{
	if (!m_ptr) {
		throw aftu::Exception("Nullable instance is null!");
	}

	return *m_ptr;
}

template<typename T>
T& Nullable<T>::value() throw (std::exception)
{
	if (!m_ptr) {
		throw aftu::Exception("Nullable instance is null!");
	}

	return *m_ptr;
}

} // namespace

#endif // INCLUDED
