#include <iostream>
#include <string>
#include <memory>

class Person
{
private:
	std::string m_name;
	std::weak_ptr<Person> m_partner;
public:
	Person(std::string name) : m_name{name}
	{
		std::cout << m_name << " is created\n";
	}

	~Person()
	{
		std::cout << m_name << " is destroyed\n";
	}

	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
	{
		if(!p1 || !p2)
		{
			return false;
		}
		p1->m_partner = p2;
		p2->m_partner = p1;
		std::cout << p1->m_name << " is now a partner of " << p2->m_name << '\n';
		return true;
	}

	const std::shared_ptr<Person> getPartner() const
	{
		return m_partner.lock();
	}

	const std::string getName() const
	{
		return m_name;
	}
};

int main()
{
	auto lucy{std::make_shared<Person>("Lucy")};
	auto ricky{std::make_shared<Person>("Ricky")};

	partnerUp(lucy, ricky);

	auto partner = ricky->getPartner();
	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';

	return 0;
}
