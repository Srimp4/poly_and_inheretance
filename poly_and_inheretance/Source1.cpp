#include <iostream>
#include <string>
#include <vector>
#include <memory>

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

//features and problems of polymorf proccessing and inheretance
// inheretence problem - general category (base class) has to have info on that a an action exists, but there's not a clear defenition of the general view of the action
//						 in this situation the program that calls in those methods might not compile, the program waits that proccessor might recieve an object of a class without realization,
//						 and you need to know how to call in it's code
// polymorf storage problem - in most cases gathering elements of in a collection we want the collection to posses stored objects and external user couldn't access and control it
//							  in this case we need either a link or a pointer to the stored object, but standart collections can't store links,
//							  and in case of the pointer the collection has to learn how ot control lifetime of a stored object,
//							  compiler can't generate unavailable (in case of links) or not described by the programmer (in case of the pointer) code
// 
// for solving these problems we have several methods to control proccesses directly
//
// solving the problem of uninformed inheretance - abstract methods (pure virtual function)
//		what these function provide in a class:
//			- existance of at least one turns the class into an abstract class
//			- we directly forbid to create objects of that abstract class
//			- inhereters can have their own objects, but only if this method is realized
//			* if a class contains only abstract methods and none other components it's called an interface
//			** in other C languages there's a category of user types - interfaces, under wich there are keywords and rules of working in c++ it's only on the level of agreement
// code example:
class Aclass
{
public:
	Aclass() = default;
	Aclass(const std::string& name) :name_(name) {}
	std::string Getname() const { return name_; }
	void Setname(std::string name) { name_ = name; }
	virtual void Dojob() = 0;//abstract method syntax
private:
	std::string name_;
};
// class above will be abstract beacause there's a Dojob method in it that can't be defined
class Iprintable
{
public:
	virtual void Print() = 0;
	virtual std::string Tostring()const = 0;
};
//class above can be called an interface because it only has abstract methods
// 
// usually abstract classes use prefix A AB in capital or lowercase outlinem and for interfaces I is also available in the outline 
// 
// storage problem
void Example()
{
	std::vector<Base>		coll1;//collection of base class objects
	std::vector<Derived>	coll2;//collection of objects from the derived class
	//objects from the first collection can't be passed over to the second, you can do it the other way around but it will delete all data from the inhereter fields and forgetting the behavior of the inhereter

	std::vector<Base*> coll3;//collection of pointers to the Base family objects
	//std::vector<Base&> coll4;//collection of links to the Base family objects
	//both can accept any object that is a part of the base class or it's inhereters, order of inheretance directly or through several steps doesn't matter,
	//but std::vector<Base&> coll4; will cause compilation errors tied to link features in c++
}
// to solve the problem of polymorf storage without unneccesary code people usually use smart pointers
// smart pointers are class objects that behave like pointers to a stored object and automate interaction with class object life time 
//		in simple termsit's a template class with a pointer on an object and overclocking of operators 
//
//smart pointer example
template<typename Type>
class Smartpointer
{
public:
	Smartpointer():raw_data_(nullptr){}
	~Smartpointer()
	{
		if (raw_data_)
		{
			delete raw_data_;
		}
	}

	Smartpointer(Type * raw_data):raw_data_(raw_data){}
	Smartpointer(const Type& raw_data)
	{
		raw_data_ = new Type{ raw_data };
	}

	void clear()
	{
		if (raw_data_)
		{
			delete raw_data_;
		}
		raw_data_ = nullptr;
	}

	Type* release()
	{
		auto result = raw_data_;
		raw_data_ = nullptr;
		return result;
	}

	Type& operator*()
	{
		return *raw_data_;
	}

	const Type& operator*()const
	{
		return *raw_data_;
	}

	Type* operator->()
	{
		return raw_data_;
	}

	const Type* operator->() const
	{
		return raw_data_;
	}

private:
	Type* raw_data_;
};

void Smartptrexample()
{
	Smartpointer<int> int_ptr{ 8 };
	int* raw_ptr;
	int var = 7;
	raw_ptr = &var;

	std::cout << *raw_ptr << "\n";
	std::cout << *int_ptr << "\n";

	Smartpointer<Base> base_ptr = new Derived;
	base_ptr->Sayhi();// this method is virtual and polymorf, hence it allows to use virtual realization of the inhereter

	std::unique_ptr<Base> u_ptr_base(new Derived);//could work but not recomended because manual memory control

	// any smart ptr has a make function

	std::unique_ptr<Base> Base_PTR = std::make_unique<Derived>();
	// for unique and shared arenthasies are used to transfer arguments for the class constructor
}
//this is basically auto_ptr - simple possesing smart pointer without protection from copying and external use
//	unique_ptr - possesing pointer with protection from copying and guaranteeing access to the object only through itself, when destroyed destroyes the object
//	shared_ptr - possesing pointer allowing creating copies and guaranteeing that time of life of the object will end only when the lasst copy of the pointer will
//	weak_ptr - viewing instrument not possesing information, most often used for creating copies of the object in memory or conduct count of objects in unique_ptr
// 
// 
// object plaement in a collection with a smart ptr example
void Placement()
{
	std::vector<std::unique_ptr<Base>> spc;
	spc.reserve(20);
	for (size_t i = 0; i < spc.capacity(); i++)
	{
		if (rand() % 2)
		{
			spc.emplace_back(std::make_unique<Base>());
		}
		else
		{
			spc.emplace_back(std::make_unique<Derived>());
		}
	}
	for (auto& ptr : spc)
	{
		ptr->Sayhi();
	}
}

int main()
{
	Placement();
}
