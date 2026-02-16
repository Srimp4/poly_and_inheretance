#include <iostream>
#include <string>
#include <vector>
#include <random>

//task:
//	for demonstration purposes create a program generating beasts in a bestiary
//	while proccesing beasts you have to figure out is a beast hungry and feed it if it is
//

class Beast
{
public:
	virtual bool Ishungry()const
	{
		return calories_ < limit_;
	}
	virtual void Feed(int calories)
	{
		calories_ += calories;
	}
	std::string Getname()const
	{
		return name_;
	}
	void Setname(const std::string& new_name)
	{
		name_ = new_name;
	}

protected:
	void Setlimit(int limit)
	{
		limit_ = limit;
	}

private:
	int calories_;
	std::string name_;
	int limit_;
};

class Car : public Beast
{
public:
	Car() = default;
	virtual bool Ishungry()const override
	{

	}
};

class Dog : public Beast
{

};

class Beastiary
{
public:
	Beastiary()
	{
		int count = 10;
		std::mt19937 gen(std::random_device().entropy());
		std::uniform_int_distribution<int> distr(1, 2);
		data_.reserve(count);
		for (size_t i = 0; i < count; i++)
		{
			int key = distr(gen);
			if (1 == key)
			{
				//data_.push_back(new Car);
				//to-do: replace the beast with a inhereter class, do as much bracnches as you have diffirent inhereters
			}
			else if (2 == key)
			{
				data_.push_back(new Dog);
			}
		}
	}
	int size()const
	{
		return data_.size();
	}

	Beast& operator[](int i)
	{
		return *(data_[i]);
	}

	Beast& operator[](int i) const
	{
		return *(data_[i]);
	}

private:
	std::vector<Beast*> data_;
};

void Feedbeast(Beast& beast)
{

}

int main2()
{
	Beastiary den;

	return 0;
}

//do: constructors for both inhereters, override methods for both inhereters, Feedbeast() function
