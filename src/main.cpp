#include <iostream>

template<class T>
class Auto_ptr3
{
private:
	T* m_ptr;
public:
	Auto_ptr3(T *ptr = nullptr) : m_ptr{ptr}
	{}

	~Auto_ptr3()
	{
		delete m_ptr;
	}

	Auto_ptr3(const Auto_ptr3& a) = delete;
	// {
	// 	m_ptr = new T;
	// 	*m_ptr = *a.m_ptr;
	// }

	Auto_ptr3(Auto_ptr3&& a) noexcept : m_ptr{a.m_ptr}
	{
		a.m_ptr = nullptr;
	}

	Auto_ptr3& operator=(const Auto_ptr3& a) = delete;
	// {
	// 	if(this == &a)
	// 	{
	// 		return *this;
	// 	}
	// 	delete m_ptr;
	// 	m_ptr = new T;
	// 	*m_ptr = *a.m_ptr;
	// 	return *this;
	// }

	Auto_ptr3& operator=(Auto_ptr3&& a) noexcept
	{
		if(&a == this)
		{
			return *this;
		}
		delete m_ptr;
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const {return m_ptr == nullptr;}
};

class Resource
{
public:
	Resource()
	{
		std::cout << "Resource aquired\n";
	}

	~Resource()
	{
		std::cout << "Resource destroyed\n";
	}
};

Auto_ptr3<Resource> generateResource()
{
	Auto_ptr3<Resource> res{new Resource};
	return res;
}

int main()
{
	Auto_ptr3<Resource> mainRes;
	mainRes = generateResource();
	return 0;
}
