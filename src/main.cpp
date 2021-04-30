#include <iostream>
#include <cassert>
#include <chrono>

template<class T>
class DynamicArray
{
private:
	T* m_array;
	int m_length;
public:
	DynamicArray(int length)
	: m_array{new T[length]}, m_length{length}
		{
			assert(length > 0);
		}
	~DynamicArray()
	{
		delete m_array;
	}

	//Copy semantic with deep copying
	DynamicArray(const DynamicArray &d) = delete;
	// {
	// 	m_array = new T[d.m_length];
	// 	m_length = d.m_length;
	// 	for(int index{0}; index < m_length; ++index)
	// 	{
	// 		m_array[index] = d.m_array[index];
	// 	}
	// }

	DynamicArray& operator=(const DynamicArray& d) = delete;
	// {
	// 	if(this == &d)
	// 	{
	// 		return *this;
	// 	}
	// 	delete[] m_array;
	// 	m_array = new T[d.m_length];
	// 	m_length = d.m_length;
	// 	for(int index{0}; index < m_length; ++index)
	// 	{
	// 		m_array[index] = d.m_array[index];
	// 	}
	// 	return *this;
	// }

   //Move semantic
   DynamicArray(DynamicArray &&d) noexcept
   : m_array{d.m_array}, m_length{d.m_length}
   {
      d.m_length = 0;
      d.m_array = nullptr;
   }

   DynamicArray& operator=(DynamicArray &&d) noexcept
   {
      if(this == &d)
      {
         return *this;
      }
      delete[] m_array;
      m_array = d.m_array;
      m_length = d.m_length;
      d.m_length = 0;
      d.m_array = nullptr;
      return *this;
   }

	int getLength() const
	{
		return m_length;
	}
	T& operator[](int index)
	{
		return m_array[index];
	}
	const T& operator[](int index) const
	{
		return m_array[index];
	}
};

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
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
{
	DynamicArray<int> dbl{arr.getLength()};
	for(int index{}; index < arr.getLength(); ++index)
	{
		dbl[index] = arr[index] * 2;
	}
	return dbl;
}

int main()
{
	Timer t;
	DynamicArray<int> arr{1000000};
	for(int index{}; index < 1000000; ++index)
	{
		arr[index] = index;
	}

	DynamicArray<int> dbl = cloneArrayAndDouble(arr);
	std::cout << t.elapsed();

	return 0;
}
