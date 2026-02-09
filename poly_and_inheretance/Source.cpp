#include <iostream>
#include <string>

//in proggres of developing classes that contain root functions that you will want to use more than once will inevitebly appear, while working like that you have some self restrictions for developers that will
//help to ease the workload later, with the help of inheretence from the base class we only extending it's functional, classes inhereters are most often change the behavior of the parent class
//
class Base
{
public:
	void Sayword()const
	{
		std::cout << "word\n";
	}
	virtual void Sayhi()const
	{
		std::cout << "hi\n";
	}
	virtual void Talk()const
	{
		Printphrase();
	}
	void Setheme(const std::string& phrase)
	{
		phrase_ = phrase;
	}
protected://if inhereted fully available to the inhereter
	void Printphrase()const
	{
		std::cout << phrase_ << std::endl;
	}
private://if inhereted transitions to the inhereter, but itsn't available
	std::string phrase_;
};

//a class that publically inherets class base is created
class Derived:public Base
{
public:
	void Sayword()const
	{
		std::cout << "E\n";
	}
	virtual void Sayhi()const override
	{
		std::cout << "WAZZUUUUP!\n";
	}
	virtual void Talk()const override
	{
		std::cout << "Topic: ";
		Printphrase();
	}
};

class Imposter
{

};

void Printobj(Base obj)
{
	obj.Sayhi();
	obj.Sayword();
	obj.Setheme("new topic!");
	obj.Talk();
}

void Printtrowref(Base& obj)
{
	obj.Sayhi();
	obj.Sayword();
	obj.Setheme("new topic!");
	obj.Talk();
}

void main1()
{
	Base obj_parrent;
	obj_parrent.Sayhi();
	obj_parrent.Sayword();
	obj_parrent.Talk();
	obj_parrent.Setheme("polymorfism is great!");
	obj_parrent.Talk();
	Printobj(obj_parrent);
	//obj_parrent.Printphrase();
	//obj_parrent.prase_;
	//the lines commented above are unavailable outside the class

	Derived obj_derived;
	obj_derived.Sayhi();
	obj_derived.Sayword();
	obj_derived.Talk();
	obj_derived.Setheme("polymorfism is great!");
	obj_derived.Talk();
	Printobj(obj_derived);
	

}