#include <iostream>
#include <chrono>

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::chrono::time_point<clock_t> m_beg;
public:
	Timer() : m_beg{clock_t::now()}
	{}
	void reset()
	{
		m_beg = clock_t::now();
	}
	double elapse() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

template<class T>
class DynamicArray
{
private:
	T* m_array;
	int m_length;
public:
	DynamicArray(int length = 0)
	: m_array{new T[length]}, m_length{length}
	{
	}

	~DynamicArray()
	{
		delete[] m_array;
	}

	DynamicArray(const DynamicArray& a) : m_length{a.m_length}
	{
		m_array = new T[m_length];
		for(int i{0}; i < m_length; ++i)
		{
			m_array[i] = a.m_array[i];
		}
	}

	DynamicArray(DynamicArray&& a) noexcept
	: m_array{a.m_array}, m_length{a.m_length}
	{
		a.m_array = nullptr;
		a.m_length = 0;
	}

	DynamicArray& operator=(const DynamicArray& a)
	{
		if(&a == this)
		{
			return *this;
		}
		delete[] m_array;
		m_length = a.m_length;
		m_array = new T[m_length];
		for(int i{0}; i < m_length; ++i)
		{
			m_array[i] = a.m_array[i];
		}
		return *this;
	}

	DynamicArray& operator=(DynamicArray&& a) noexcept
	{
		if(&a == this)
		{
			return *this;
		}
		delete[] m_array;
		m_array = a.m_array;
		m_length = a.m_length;
		a.m_array = nullptr;
		a.m_length = 0;
		return *this;
	}

	int getLength() const { return m_length; }
	T& operator[](int index) { return m_array[index]; }
	const T& operator[](int index) const { return m_array[index]; }
};

DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int>& a)
{
	DynamicArray<int> dbl{a.getLength()};
	for(int i{0}; i < a.getLength(); ++i)
	{
		dbl[i] = a[i] * 2;
	}
	return dbl;
}

int main()
{
	Timer t;
	DynamicArray<int> arr(1000000);
	for(int i{0}; i < arr.getLength(); ++i)
	{
		arr[i] = i;
	}
	arr = cloneArrayAndDouble(arr);
	std::cout << t.elapse();

	return 0;
}
