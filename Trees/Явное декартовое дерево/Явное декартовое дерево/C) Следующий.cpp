#include <iostream>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

int const mod = 1000000000;

class Treap {
private:
	static minstd_rand generator;

	struct Node {
		int key, priority;
		Node* l = nullptr, * r = nullptr;
		Node(int key) : key(key), priority(generator()) {}
	} *root = nullptr;

	static Node* merge(Node* a, Node* b) {
		if (!a || !b) {
			return a ? a : b;
		}

		if (a->priority > b->priority) {
			a->r = merge(a->r, b);
			return a;
		}
		else {
			b->l = merge(a, b->l);
			return b;
		}
	}

	void split(Node* n, int key, Node*& a, Node*& b) {
		if (!n) {
			a = b = nullptr;
			return;
		}

		if (n->key < key) {
			split(n->r, key, n->r, b); //
			a = n;
		}
		else {
			split(n->l, key, a, n->l);
			b = n;
		}
	}
public:
	bool find(int key) {
		Node* greater, * equal, * less;
		split(root, key, less, greater);
		split(greater, key + 1, equal, greater);
		bool rezult = equal;
		root = merge(merge(less, equal), greater);
		return rezult;
	}

	void insert(int key) {
		Node* greater, * less;
		split(root, key, less, greater);
		less = merge(less, new Node(key));
		root = merge(less, greater);
	}

	void erase(int key) {
		Node* greater, * equal, * less;
		split(root, key, less, greater);
		split(greater, key + 1, equal, greater);
		root = merge(less, greater);
	}

	int min(Node* n) const {
		if (!n) {
			return -1;
		}

		while (n->l) {
			n = n->l;
		}

		return n->key;
	}

	int next(int key) {
		Node* greater, * less;
		split(root, key, less, greater);
		int ans = min(greater);
		root = merge(less, greater);
		return ans;
	}
};

minstd_rand Treap::generator;

int main() {
	ifstream inFile("next.in");
	ofstream outFile("next.out");
	int n;
	inFile >> n;
	char oper, last_oper = '+';
	Treap tree;
	int dig, last_rezult;
	for (int i = 0; i < n; i++) {
		inFile >> oper;
		inFile >> dig;
		if (oper == '+') {
			if (last_oper == '+') {
				if (!tree.find(dig)) {
					tree.insert(dig);
				}
			}
			else {
				int in_dig = (dig + last_rezult) % mod;
				if (!tree.find(in_dig)) {
					tree.insert(in_dig);
				}
			}
		}
		else {
			int out_dig = tree.next(dig);
			outFile << out_dig << "\n";
			last_rezult = out_dig;
		}
		last_oper = oper;
	}
	return 0;
}