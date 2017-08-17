#pragma once
#include <vector>
#include <set>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Element
{
protected:
	string name;
	vector<Element*> connection;

public:
	Element() {}
	~Element() {}

	Element(string val)
	{
		name = val;
	}

	void setName(string val)
	{
		name = val;
	}

	string getName()
	{
		return name;
	}

	void operator >> (Element &val)
	{
		this->connection.emplace_back(&val);
		val.connection.emplace_back(this);
	}

	void addConnection(Element &val)
	{
		this->connection.emplace_back(&val);
		val.connection.emplace_back(this);
	}

	void delConnection(Element &val)
	{
		connection.erase(std::remove(connection.begin(), connection.end(), &val), connection.end());
	}

	vector<Element*> getConnection()
	{
		return connection;
	}

	friend void getAllPath(Element &from, Element &to)
	{
		stack<Element*> Stack;
		set<Element*> wasThere;
		Element *cur = NULL;
		string path;

		for (int i = 0; i < from.connection.size(); i++)
		{
			Stack.push(from.connection[i]);
			wasThere.emplace(from.connection[i]);
		}

		while (!Stack.empty())
		{
			path = from.name;
			while (cur != &to)
			{
				if(Stack.empty()) break;
				cur = Stack.top();
				Stack.pop();

				path += " -> " + cur->name;

				for (int i = 0; i < cur->connection.size(); i++)
				{
					if (!wasThere.count(cur->connection[i]) || cur->connection[i] == &to)
					{
						Stack.push(cur->connection[i]);
						wasThere.emplace(cur->connection[i]);
					}
				}
			}
			cout << path << endl;
			path.clear();
			cur = &from;
		}

		
	}
};

