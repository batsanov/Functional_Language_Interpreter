#pragma once

#include <vector>
#include <forward_list>

#include "Parser.h"
#include "BuiltInFunctions.h"

const size_t    DEFAULT_BUCKET_COUNT = 8;
const float     DEFAULT_MAX_LOAD_FACTOR = 1;

class UserGeneratedFunctions {
private:
	 struct Pair
	{
		std::string funcName;
		ASTNode* body;

		Pair(std::string funcName, ASTNode* body) : funcName(funcName), body(body) {};

		ASTNode* getCopy(ASTNode* root) const {
			if (root)
				return new ASTNode(root->expr->getCopy(), getCopy(root->child), getCopy(root->brother));
			else
				return root;
		};

		void clearPair(ASTNode* root) {
			if (!root)
				return;

			clearPair(root->child);
			clearPair(root->brother);

			delete root;
		}

		~Pair() {
			body = nullptr;
		};
	};
	
	 std::vector<std::forward_list<Pair>> table;
	 std::hash<std::string> hashFunc;
	 size_t size;
	 float maxLoadFactor;

	 size_t hash(const std::string& word)
	{
		return hashFunc(word) % table.size();
	}
	 void reHash(const size_t bucketCount) {
		std::vector<std::forward_list<Pair>> newTable(bucketCount);
		std::swap(table, newTable);
		size = 0;

		for (std::forward_list<Pair>& list : newTable)
			for (const Pair& elem : list)
				add(elem.funcName, elem.body);
	}
	 void clear()
	{
		 for (std::forward_list<Pair>& list : table)
			 for (Pair& pair : list)
				 pair.clearPair(pair.body);
	};

	

public:

	UserGeneratedFunctions() : table(DEFAULT_BUCKET_COUNT), size(0), maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR) {};
	~UserGeneratedFunctions() { clear(); }

	 void print() {

		for (std::forward_list<Pair>& list : table)
			for (const Pair& elem : list)
				std::cout << "(" << elem.funcName << ") ";
		std::cout << "\n";
	};

	 int add(const std::string funcName, ASTNode* body)
	{
		size_t index = hash(funcName);
		for (Pair& elem : table[index])
		{
			if (elem.funcName == funcName)
			{
				delete elem.body;
				elem.body = body;
				return 1;
			}
		}

		if ((float)(size + 1) / table.size() > maxLoadFactor)
			reHash(table.size() * 2);

		table[index].push_front(Pair(funcName, body));
		size++;
		return 0;
	};

	 ASTNode* call(const std::string funcName)
	{
		size_t index = hash(funcName);

		for (const Pair& elem : table[index])
		{
			if (elem.funcName == funcName)
			{
				return elem.getCopy(elem.body);
			}
		}
	}
	 
	 bool isFunction(const std::string funcName) {
		size_t index = hash(funcName);

		for (const Pair& elem : table[index])
		{
			if (elem.funcName == funcName)
			{
				return true;
			}
		}

		return false;
	}
};