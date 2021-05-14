#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <string>

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

int main()
{
	Timer t;

	std::srand(std::time(nullptr));
	std::string s;
	s.reserve(64);
	for(int i{0}; i < 64; ++i)
	{
		s += 'a' + std::rand() % 26;
	}
	std::cout << s << std::endl;

	std::cout << "Time remaining is " << t.elapse() << " second\n";

	return 0;
}
