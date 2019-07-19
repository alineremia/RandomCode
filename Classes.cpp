#include <string>
#include <algorithm>
#include <iostream>
#include <vector>


//Alin Gabriel Eremia

using namespace std;

class Customer
{
protected:

	string name;
	string phoneNumber;
	long long balance;
	double totalCallDuration;
	string type;

public:
	Customer() = default;
	Customer(string t, string n, string p, long long b, double d)
	{
		type = t;
		name = n;
		phoneNumber = p;
		balance = b;
		totalCallDuration = d;
	}

	virtual ~Customer() {}


	void setName(string n) {
		name = n;
	}
	void setPhoneNumber(string p) {
		phoneNumber = p;
	}
	virtual void setBalance(long long b) {
		balance = b;
	}
	void updateTotalCallDuration(double t) {
		totalCallDuration += t;
	}

	double getTotalCallDuration()
	{
		return totalCallDuration;
	}

	string getType()
	{
		return type;
	}

	string getName()
	{
		return name;
	}

	string getPhoneNumber()
	{
		return phoneNumber;
	}

	void credit(long long credit)
	{
		balance += credit;
	}

	long long enquireBalance() 
	{
		return balance;
	}
};

class PrepaidCustomer : public Customer
{
	int unique_id = 0;
	void setBalance(long long b) 
	{
		balance += b;
	}


public:
	PrepaidCustomer() = default;
	PrepaidCustomer(string type, string name, string number, long long  balance, double callD) : Customer(type, name, number, balance, callD)
	{
		unique_id = unique_id + 1;
	}

	virtual ~PrepaidCustomer() {}

	int getId() {
		return unique_id;
	}
};

class PostpaidCustomer : public Customer
{
	int unique_id = 0;
public:
	PostpaidCustomer() = default ;
	PostpaidCustomer(string type, string name, string number, long long  balance, double callD) : Customer(type, name, number, INT_MAX, callD)
	{
		unique_id = unique_id + 1;
	}

	virtual ~PostpaidCustomer() {}

	int getId() {
		return unique_id;
	}
};

class MobileBilling : public PostpaidCustomer, public PrepaidCustomer
{
public:
	MobileBilling() = default;
	~MobileBilling() {}

	void addCustomer(string type, string name, string number, long long  balance, double callD) {

		if (type == "post") {
			Customer* newCust = new PostpaidCustomer(type, name, number, balance, callD);
			customers.push_back(newCust);
		}
		else if (type == "pre")
		{
			Customer* newCust = new PrepaidCustomer(type, name, number, balance, callD);
			customers.push_back(newCust);
		}
		
	}

	void deleteCustomer(string name) {
		
		std::vector<Customer*>::iterator it;
		int index;
		for (std::vector<Customer*>::iterator it = customers.begin(); it != customers.end(); it++)
		{

			string type = (*it)->getType();
			string n = (*it)->getName();

			if (n == name)
			{
				index = std::distance(customers.begin(), it);
				
			}

		}
		customers.erase(customers.begin() + index);
		cout << "Removed Customer " << name << "\n";

	}
	void searchById(string id)
	{
	
	}
	void searchByName(string name)
	{

		auto it = find_if(customers.begin(), customers.end(), [&name](Customer* obj)
		{
			return obj->getName() == name;
		});

		if(it != customers.end())
		{
			cout << "Found name " << name << "\n";
		}
		else {
			cout << "Cannot find name " << name << "\n";
		}
	
	}

	void searchByNumber(string number)
	{
		auto it = find_if(customers.begin(), customers.end(), [&number](Customer* obj)
		{
			return obj->getPhoneNumber() == number;
		});

		if (it != customers.end())
		{
			cout << "Found Number " << number << "\n";
		}
	}
	void getAveragePostPaidCallDuration()
	{

		std::vector<Customer*>::iterator it;
		double sum = 0.0;
		int count = 0;

		for (std::vector<Customer*>::iterator it = customers.begin(); it != customers.end(); it++)
		{

			string type = (*it)->getType();
			double duration = (*it)->getTotalCallDuration();

			if (type == "post")
			{
				sum += duration;
				count++;

			}

		}

		cout << "Average PostPaid Call Duration " << sum / count << "\n";

	}
	void queryPostpaidCustomers()
	{
		
		std::vector<Customer*>::iterator it;

		for (std::vector<Customer*>::iterator it = customers.begin(); it != customers.end(); it++)
		{

			string type = (*it)->getType();
			string name = (*it)->getName();
			
			if (type == "post") 
			{
				cout << "Found Postpaid Customer " << name << "\n";
			}		
 
		}

	}
	void getAveragePrePaidBalance()
	{
		std::vector<Customer*>::iterator it;
		long long sum = 0;
		int count = 0;

		for (std::vector<Customer*>::iterator it = customers.begin(); it != customers.end(); it++)
		{

			string type = (*it)->getType();
			long long balance = (*it)->enquireBalance();
			
			if (type == "pre")
			{
				sum += balance;
				count++;
				
			}

		}
		
		cout << "Average PrePaid Balance " << sum / count << "\n";

	}
	void queryPrepaidCustomers()
	{
		
		std::vector<Customer*>::iterator it;

		for (std::vector<Customer*>::iterator it = customers.begin(); it != customers.end(); it++)
		{

			string type = (*it)->getType();
			string name = (*it)->getName();

			if (type == "pre")
			{
				cout << "Found Prepaid Customer " << name << "\n";
			}

		}
	}



private:

	
	vector<Customer*> customers;
	
};

int main()
{


	MobileBilling* bill = new MobileBilling();;
	bill->addCustomer("post", "Alin", "3214151", 0, 234.32);
	bill->addCustomer("post", "Gina", "532135", 0, 320.0);
	bill->addCustomer("pre", "Jack", "5045266", 50, 0.10);
	bill->addCustomer("post", "Maria", "51312531", 0, 50);
	bill->addCustomer("pre", "Sara", "5045266", 200, 19353.32);

	bill->searchByName("Silviu");
	bill->searchByNumber("5045266");
	bill->searchByName("Jack");

	bill->queryPrepaidCustomers();
	bill->queryPostpaidCustomers();
	bill->getAveragePrePaidBalance();
	bill->getAveragePostPaidCallDuration();

	bill->searchById("1");

	bill->deleteCustomer("Alin");

	return 0;
}

