#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
using namespace std;

class Element
{
private:
	string name;
	float R, U, I;
	vector<Element*> connection;

public:
	Element() {}
	~Element() {}

	Element(float r, string val)
	{
		R = r;
		name = val;
	}

	Element(float r) 
	{
		R = r;
	}

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

	float getR()
	{
		return R;
	}

	void setR(float r)
	{
		R = r;
	}

	float getU() 
	{
		return U;
	}

	void setU(float u)
	{
		U = u;
	}

	float getI()
	{
		return I;
	}

	void setI(float i)
	{
		I = i;
	}

	void operator >> (Element &val)
	{
		this->connection.emplace_back(&val);
		val.connection.emplace_back(this);

		for (int i = 0; i < val.connection.size(); i++)
		{
			this->connection.emplace_back(val.connection[i]);
			val.connection[i]->connection.emplace_back(this);
		}
		for (int i = 0; i < this->connection.size(); i++)
		{
			val.connection.emplace_back(this->connection[i]);
			this->connection[i]->connection.emplace_back(&val);
		}
	}

	void connect(Element &val)
	{
		connection.emplace_back(&val);
	}

	void disConnect(Element &val)
	{
		connection.erase(std::remove(connection.begin(), connection.end(), &val), connection.end());
	}

	vector<Element*> *getConnection()
	{
		return &connection;
	}

	friend void getAllPath(Element &fromTo)
	{
		string path;
		Element *cur = NULL;
		stack<Element*> Stack;
		set<Element*> wasThere;

		for (int i = 0; i < fromTo.connection.size(); i++)
		{
			Stack.push(fromTo.connection[i]);
			wasThere.emplace(fromTo.connection[i]);
		}

		do {
		path = fromTo.name;

			while (1)
			{
				cur = Stack.top();
				Stack.pop();
				path.append(" -> " + cur->name);
				if (cur == &fromTo) break;

				for (int i = 0; i < cur->connection.size(); i++)
				{
					if (!wasThere.count(cur->connection[i]))
					{
						Stack.push(cur->connection[i]);
						wasThere.emplace(cur->connection[i]);
					}
				}
			} 

			cout << path << endl;
			path.clear();

		} while (!Stack.empty());
	}
};

int main()
{
	vector<Element> El(6);
	
	for(int i = 0; i < 6; i++)
	{
		El[i] = Element("Res" + to_string(i));
	}

	El[0] >> El[1];
	El[0] >> El[4];

	El[1] >> El[2];
	El[2] >> El[3];
	El[3] >> El[0];

	El[4] >> El[5];
	El[5] >> El[0];

	getAllPath(El[0]);
	

	system("pause");
}