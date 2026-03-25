#pragma once
#include "LinkedList.hpp"

struct LinkedListSerializer {
	static void serialize(std::ofstream& out, ListNode* root);
	static ListNode* deserialize(std::ifstream& in);
};