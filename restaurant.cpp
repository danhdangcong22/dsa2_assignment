#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

class RESTAURANT_Gojo
{
	class Tree_BST;

private:
	vector<Tree_BST> areaTable;

public:
	RESTAURANT_Gojo() : areaTable(MAXSIZE + 1) {}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}
	void remove_KOKUSEN()
	{
		for (int i = 1; i < MAXSIZE + 1; i++)
			areaTable[i].remove();
	}

	void print_LIMITLESS(int number)
	{
		if (number <= 0 || number > MAXSIZE)
			return;
		areaTable[number].print();
	}

private:
	class Tree_BST
	{
		class Node;

	private:
		Node *root;
		queue<int> queueTime;

	public:
		Tree_BST() : root(nullptr) {}
		~Tree_BST()
		{
			while (!queueTime.empty())
			{
				int temp = queueTime.front();
				queueTime.pop();
				root = remove_recursive(root, temp);
			}
		}
		int size()
		{
			return queueTime.size();
		}
		Node *insert_recursive(Node *node, int result)
		{
			if (node == nullptr)
			{
				return new Node(result);
			}
			if (result < node->result)
				node->left = insert_recursive(node->left, result);
			else
				node->right = insert_recursive(node->right, result);
			return node;
		}
		void insert(int result)
		{
			root = insert_recursive(root, result);
			queueTime.push(result);
		}
		Node *remove_recursive(Node *node, int result)
		{
			if (node == nullptr)
				return nullptr;
			else if (result < node->result)
				node->left = remove_recursive(node->left, result);
			else if (result > node->result)
				node->right = remove_recursive(node->right, result);
			else if (result == node->result)
			{
				Node *deleteNode = node;
				if (node->left == nullptr && node->right == nullptr)
				{
					node = nullptr;
				}
				else if (node->left == nullptr)
				{
					node = node->right;
				}
				else if (node->right == nullptr)
				{
					node = node->left;
				}
				else
				{
					Node *tmp = node->right;
					while (tmp->left != nullptr)
						tmp = tmp->left;
					swap(node->result, tmp->result);
					node->right = remove_recursive(node->right, result);
					return node;
				}
				delete deleteNode;
			}
			return node;
		}

		int CountNode(Node *node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}

		unsigned long long permutationFormula(int x, int n)
		{
			vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(x + 1, 0));
			for (int i = 0; i <= n; i++)
			{
				for (int j = 0; j <= x && j <= i; j++)
				{
					if (j == 0 || j == i)
					{
						dp[i][j] = 1;
					}
					else
						dp[i][j] = (dp[i - 1][j - 1] % MAXSIZE + dp[i - 1][j] % MAXSIZE) % MAXSIZE;
				}
			}
			return dp[n][x];
		}

		unsigned long long DFS(Node *node)
		{
			if (node == NULL)
				return 1;

			int leftSize = CountNode(node->left);
			int rightSize = CountNode(node->right);
			return (DFS(node->left) % MAXSIZE * DFS(node->right) % MAXSIZE * permutationFormula(leftSize, leftSize + rightSize) % MAXSIZE) % MAXSIZE;
		}
		void remove()
		{
			if (queueTime.empty())
				return;

			unsigned long long number = DFS(root) % MAXSIZE;

			while (number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();
				queueTime.pop();
				root = remove_recursive(root, temp);
				number--;
			}
		}
		void print_recursive(Node *node)
		{
			if (node != NULL)
			{
				print_recursive(node->left);
				cout << node->result << "\n";
				print_recursive(node->right);
			}
		}
		void print() { print_recursive(root); }

	private:
		class Node
		{
		private:
			int result;
			Node *left;
			Node *right;
			friend class Tree_BST;

		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};

	public:
	};
};

class RESTAURANT_Sukuna
{
	class Node;

private:
	vector<Node *> areaTable;
	list<Node *> LRU;

private:
	bool compare(int index, int min)
	{
		if (distanceLRU(areaTable[index]) > distanceLRU(areaTable[min]))
			return true;
		return false;
	}
	int distanceLRU(Node *node)
	{
		int dis = 0;
		for (Node *lruNode : LRU)
		{
			if (lruNode == node)
				break;
			dis++;
		}
		return dis;
	}
	void ReHeap_down(int index)
	{
		int size = areaTable.size();
		int smallest = index;
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		if (leftChild < size)
		{
			if (areaTable[leftChild]->size() < areaTable[smallest]->size())
				smallest = leftChild;
			else if (areaTable[leftChild]->size() == areaTable[smallest]->size())
			{
				if (compare(leftChild, smallest))
					smallest = leftChild;
			}
		}
		if (rightChild < size)
		{
			if (areaTable[rightChild]->size() < areaTable[smallest]->size())
				smallest = rightChild;
			else if (areaTable[rightChild]->size() == areaTable[smallest]->size())
			{
				if (compare(rightChild, smallest))
					smallest = rightChild;
			}
		}
		if (smallest != index)
		{
			swap(areaTable[index], areaTable[smallest]);
			ReHeap_down(smallest);
		}
	}
	void ReHeap_up(int index)
	{
		while (index > 0)
		{
			int parent = (index - 1) / 2;
			if (areaTable[index]->size() < areaTable[parent]->size())
			{
				swap(areaTable[index], areaTable[parent]);
				index = parent;
			}
			else
				break;
		}
	}
	void moveTop(Node *node)
	{
		list<Node *>::iterator it = find(LRU.begin(), LRU.end(), node);
		if (it != LRU.end())
		{
			LRU.erase(it);
		}
		LRU.push_front(node);
	}
	void removeNode(Node *node)
	{
		list<Node *>::iterator it = find(LRU.begin(), LRU.end(), node);
		if (it != LRU.end())
		{
			LRU.erase(it);
		}
	}

public:
	RESTAURANT_Sukuna() {}
	~RESTAURANT_Sukuna()
	{
		for (size_t i = 0; i < areaTable.size(); i++)
		{
			delete areaTable[i];
		}
	}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		int index = -1;
		for (vector<Node *>::iterator it = areaTable.begin(); it != areaTable.end(); it++)
		{
			if ((*it)->ID == ID)
			{
				index = distance(areaTable.begin(), it);
				break;
			}
		}

		if (index == -1)
		{
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}

		else
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}
	void remove_KEITEIKEN(int number)
	{
		if (areaTable.size() <= 0)
			return;

		vector<Node *> areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node *> listDelete;
		for (int i = 0; areaTable.size() && i < number; i++)
		{
			Node *nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[areaTable.size() - 1]);
			areaTable.pop_back();
			this->ReHeap_down(0);

			listDelete.push(nodeDelete);
		}

		areaTable = areaTableNew;

		while (listDelete.size())
		{
			Node *nodeDelete = listDelete.front();
			listDelete.pop();

			nodeDelete->remove(number);

			int index = 0;
			while (areaTable[index] != nodeDelete)
				index++;

			if (nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[areaTable.size() - 1]);
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];
				areaTable.pop_back();
			}
			this->ReHeap_down(index);
		}
	}

	void print_pre_order(int index, int number)
	{
		int size = areaTable.size();
		if (index >= size || number <= 0)
			return;
		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number) { print_pre_order(0, number); }

private:
	class Node
	{
	private:
		int ID;
		list<int> head;
		friend class RESTAURANT_Sukuna;

	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result) { head.push_front(result); }
		void remove(int number)
		{
			while (number != 0 && !head.empty())
			{
				cout << head.back() << "-" << ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				cout << ID << "-" << *it << "\n";
			}
		}
	};
};

class HuffTree_AVL
{
	class Node;

private:
	Node *root = nullptr;

public:
	~HuffTree_AVL() { clear(root); }
	void clear(Node *node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
	static bool freqCompare(pair<char, int> a, pair<char, int> b)
	{
		if (a.second == b.second)
		{
			if ((islower(a.first) && islower(b.first)) || (isupper(a.first) && isupper(b.first)))
			{
				return a.first > b.first;
			}
			return a.first < b.first;
		}
		return a.second > b.second;
	}

	vector<pair<char, int>> string_Processing(string &name)
	{
		vector<pair<char, int>> freq_prev;
		for (char c : name)
		{
			bool found = false;
			for (pair<char, int> &p : freq_prev)
			{
				if (c == p.first)
				{
					p.second++;
					found = true;
					break;
				}
			}
			if (!found)
			{
				freq_prev.push_back({c, 1});
			}
		}

		if (freq_prev.size() < 3)
			return {};

		for (char &c : name)
		{
			int shift = 0;
			for (pair<char, int> &p : freq_prev)
			{
				if (c == p.first)
				{
					shift = p.second;
					break;
				}
			}
			if (isalpha(c))
			{
				char base = islower(c) ? 'a' : 'A';
				c = ((c - base + shift) % 26 + 26) % 26 + base;
			}
		}
		for (pair<char, int> &p : freq_prev)
		{
			if (isalpha(p.first))
			{
				char base = islower(p.first) ? 'a' : 'A';
				p.first = ((p.first - base + p.second) % 26 + 26) % 26 + base;
			}
		}

		vector<pair<char, int>> freq;
		for (pair<char, int> p : freq_prev)
		{
			bool found = false;
			for (pair<char, int> &q : freq)
			{
				if (p.first == q.first)
				{
					q.second += p.second;
					found = true;
					break;
				}
			}
			if (!found)
			{
				freq.push_back({p.first, p.second});
			}
		}
		sort(freq.begin(), freq.end(), freqCompare);

		return freq;
	}
	int height(Node *node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return 1 + max(height(node->left), height(node->right));
	}
	int getBalance(Node *node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return height(node->left) - height(node->right);
	}
	Node *rotateRight(Node *root)
	{
		Node *Node_B = root->left;
		Node *Node_E = Node_B->right;

		Node_B->right = root;
		root->left = Node_E;

		return Node_B;
	}

	Node *rotateLeft(Node *root)
	{
		Node *Node_C = root->right;
		Node *Node_D = Node_C->left;

		Node_C->left = root;
		root->right = Node_D;
		return Node_C;
	}

	Node *balanceNode(Node *node, int &count)
	{
		int balance = getBalance(node);

		if (balance > 1)
		{
			if (getBalance(node->left) >= 0)
			{
				node = rotateRight(node);
				count++;
			}
			else
			{
				if (count == 2)
				{
					node->left = rotateLeft(node->left);
					count++;
				}
				else
				{
					node->left = rotateLeft(node->left);
					node = rotateRight(node);
					count++;
				}
			}
		}
		else if (balance < -1)
		{
			if (getBalance(node->right) <= 0)
			{
				node = rotateLeft(node);
				count++;
			}
			else
			{
				if (count == 2)
				{
					node->right = rotateRight(node->right);
					count++;
				}
				else
				{
					node->right = rotateRight(node->right);
					node = rotateLeft(node);
					count++;
				}
			}
		}

		return node;
	}
	Node *balanceTree(Node *node, int count = 0)
	{
		if (node == nullptr || count == 1)
			return node;
		node = balanceNode(node, count);
		node->left = balanceTree(node->left, count);
		node->right = balanceTree(node->right, count);
		return node;
	}
	Node *buildHuff(vector<pair<char, int>> freq)
	{
		vector<Node *> build;
		for (const pair<char, int> &p : freq)
		{
			build.push_back(new Node(p.second, p.first));
		}

		while (build.size() > 1)
		{
			Node *newNode = nullptr;

			Node *min1 = build.back();
			build.pop_back();
			Node *min2 = build.back();
			build.pop_back();
			newNode = new Node(min1->weight + min2->weight, '\0', min1, min2);

			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);

			vector<Node *>::iterator it = build.begin();
			while (it != build.end() && (*it)->weight > newNode->weight)
			{
				it++;
			}
			build.insert(it, newNode);
		}
		return build[0];
	}
	int binaryStringToInteger(const string &binaryString)
	{
		int result = 0;

		for (char bit : binaryString)
		{
			if (bit == '0')
			{
				result = (result << 1) | 0;
			}
			else if (bit == '1')
			{
				result = (result << 1) | 1;
			}
		}

		return result;
	}
	void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
	{
		if (node == nullptr)
			return;
		if (node->isChar())
		{
			encoding[node->c] = s;
			return;
		}
		encodingHuffman_rec(encoding, node->left, s + '0');
		encodingHuffman_rec(encoding, node->right, s + '1');
	}
	int encodingHuffman(Node *root, string nameCaesar)
	{
		if (root->left == nullptr && root->right == nullptr)
			return 0;

		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);

		string binary;
		for (const char &c : nameCaesar)
		{
			binary += encoding[c];
		}
		reverse(binary.begin(), binary.end());
		string binary10 = binary.substr(0, 10);

		int result = 0;
		result = binaryStringToInteger(binary10);

		return result;
	}

	int encode(string name)
	{

		vector<pair<char, int>> freq = this->string_Processing(name);
		if (freq.size() == 0)
			return -1;

		this->clear(root);
		root = this->buildHuff(freq);
		if (root->left == nullptr && root->right == nullptr)
			return 0;

		int result = this->encodingHuffman(root, name);

		return result;
	}

	void print_recursive(Node *node)
	{
		if (node == nullptr)
			return;
		print_recursive(node->left);
		if (node->c == '\0')
			cout << node->weight << "\n";
		else
			cout << node->c << "\n";
		print_recursive(node->right);
	}
	void print_HAND() { print_recursive(root); }

private:
	class Node
	{
	public:
		int weight;
		char c;
		Node *left;
		Node *right;
		friend class HuffTree_AVL;

	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), left(left), right(right) {}
		bool isChar() const { return c != '\0'; }
	};
};

class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;

public:
	void LAPSE(string name)
	{
		if (name[0] >= '0' && name[0] <= '9')
		{
			int result = stoi(name);
			if (result % 2 == 1)
				hash.insertAreaTable(result);
			else
				heap.insertAreaTable(result);
			return;
		}

		int result = New_customers_arrive.encode(name);
		if (result == -1)
			return;

		if (result % 2 == 1)
			hash.insertAreaTable(result);
		else
			heap.insertAreaTable(result);
	}

	//* xử lí nhà hàng gojo
	void KOKUSEN()
	{
		hash.remove_KOKUSEN();
	}
	void LIMITLESS(int num)
	{
		hash.print_LIMITLESS(num);
	}

	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num)
	{
		heap.remove_KEITEIKEN(num);
	}
	void CLEAVE(int num)
	{
		heap.print_LIMITLESS(num);
	}

	//* in ra HuffTree_AVL
	void HAND()
	{
		New_customers_arrive.print_HAND();
	}
};

void simulate(string filename)
{

	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str;
	ss >> MAXSIZE;

	JJK_RESTAURANT_OPERATIONS *jjk = new JJK_RESTAURANT_OPERATIONS();

	while (ss >> str)
	{
		if (str == "LAPSE")
		{
			ss >> name;
			jjk->LAPSE(name);
		}
		else if (str == "KOKUSEN")
		{
			jjk->KOKUSEN();
		}
		else if (str == "KEITEIKEN")
		{
			ss >> num;
			jjk->KEITEIKEN(num);
		}
		else if (str == "HAND")
		{
			jjk->HAND();
		}
		else if (str == "LIMITLESS")
		{
			ss >> num;
			jjk->LIMITLESS(num);
		}
		else if (str == "CLEAVE")
		{
			ss >> num;
			jjk->CLEAVE(num);
		}
	}
	delete jjk;
}
