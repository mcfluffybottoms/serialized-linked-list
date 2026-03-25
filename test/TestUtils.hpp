#include "../src/LinkedList.hpp"
#include <queue>
#include <set>
#include <unordered_set>

inline bool compare_lists(ListNode* fst, ListNode* snd) {
	if (!fst && !snd)
		return true;
	if (!fst || !snd)
		return false;

	std::queue<std::pair<ListNode*, ListNode*>> q;
	std::set<std::pair<ListNode*, ListNode*>> visited;
	q.push({fst, snd});
	visited.insert({fst, snd});
	while (!q.empty())
	{
		auto [node1, node2]= q.front();
		q.pop();

		if (!node1 && !node2)
			continue;
		if (!node1 || !node2)
			return false;
		if (node1->data != node2->data)
			return false;

		if (!visited.count({node1->prev, node2->prev}))
		{
			q.push({node1->prev, node2->prev});
			visited.insert({node1->prev, node2->prev});
		}
		if (!visited.count({node1->rand, node2->rand}))
		{
			q.push({node1->rand, node2->rand});
			visited.insert({node1->rand, node2->rand});
		}
		if (!visited.count({node1->next, node2->next}))
		{
			q.push({node1->next, node2->next});
			visited.insert({node1->next, node2->next});
		}
	}

	return true;
}

inline std::string print_list(ListNode* head) {
	if (!head)
	{
		return "";
	}

	std::string result;
	std::unordered_set<ListNode*> visited;
	ListNode* current= head;

	while (current && visited.find(current) == visited.end())
	{
		visited.insert(current);

		result+= "[" + current->data + "]";

		if (current->rand)
		{
			result+= "->[" + current->rand->data + "]";
		} else
		{
			result+= "->[]";
		}

		current= current->next;

		if (current && visited.find(current) == visited.end())
		{
			result+= " -> ";
		}
	}

	if (current && visited.find(current) != visited.end())
	{
		result+= " -> (cycles to " + current->data + ")";
	}

	return result;
}

inline void delete_list(ListNode* head) {
	ListNode* current= head;
	while (current)
	{
		ListNode* next= current->next;
		delete current;
		current= next;
		if (current == head)
		{
			break;
		}
	}
}