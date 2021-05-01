#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <string_view>

class MoveClass
{
private:
	int* m_resource{};
public:
	MoveClass() = default;

	MoveClass(int resource)
	: m_resource{new int{resource}}
	{}

	//Copy constructor
	MoveClass(const MoveClass& that)
	{
		//deep copy
		if(that.m_resource != nullptr)
		{
			m_resource = new int{*that.m_resource};
		}
	}

	//Move constructor
	MoveClass(MoveClass&& that) noexcept
	: m_resource{that.m_resource}
	{
			that.m_resource = nullptr;
	}

	~MoveClass()
	{
		std::cout << "destroying " << *this << '\n';
		delete m_resource;
	}

	friend std::ostream& operator<<(std::ostream &out, const MoveClass& moveClass)
	{
		out << "MoveClass(";
		if(moveClass.m_resource == nullptr)
		{
			out << "empty";
		}
		else
		{
			out << *moveClass.m_resource;
		}
		out << ')';
		return out;
	}
};

class CopyClass
{
public:
	bool m_throw{};

	CopyClass() = default;

	//Copy constructor throws an exception when copying from a CopyClass object where its m_throw is "true"
	CopyClass(const CopyClass& that) : m_throw{that.m_throw}
	{
		if(m_throw == true)
		{
			throw std::runtime_error("abort!");
		}
	}
};


int main()
{
	std::pair<MoveClass, CopyClass> mypair{MoveClass{13}, CopyClass{}};
	std::cout << "mypair.first: " << mypair.first << '\n';
	try
	{
		mypair.second.m_throw = true;
		// std::pair<MoveClass, CopyClass> moved_pair{std::move(mypair)};
		std::pair<MoveClass, CopyClass> moved_pair{std::move_if_noexcept(mypair)};
		std::cout << "moved_pair exits\n";
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Error found: " << ex.what() << '\n';
	}

	std::cout << "mypair.first " << mypair.first << '\n';

	return 0;
}
