#include "LinkedListSerializer.hpp"
#include "LinkedList.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

void LinkedListSerializer::serialize(std::ofstream& out, ListNode* root) {
	if (!out.is_open())
	{
		std::cerr << "Unable to open file." << std::endl;
		return;
	}

	if (!root)
	{
		return;
	}

	std::unordered_map<ListNode*, size_t> nodes_to_id;
	std::vector<ListNode*> nodes;
	ListNode* current= root;
	while (current)
	{
		nodes.push_back(current);
		nodes_to_id.emplace(current, nodes.size() - 1);
		current= current->next;
		if (current == root)
		{
			break;
		}
	}

	size_t number_of_nodes= nodes.size();
	out.write((char*)(&number_of_nodes), sizeof(number_of_nodes));

	current= root;
	while (current)
	{

		size_t data_size= current->data.size();
		out.write((char*)(&data_size), sizeof(data_size));// !!
		out.write(current->data.c_str(), current->data.size());

		bool has_prev= (current->prev != nullptr);
		bool has_next= (current->next != nullptr);
		bool has_rand= (current->rand != nullptr);

		out.write((char*)(&has_prev), sizeof(has_prev));
		if (has_prev)
		{
			size_t prev= nodes_to_id.at(current->prev);
			out.write((char*)(&prev), sizeof(prev));
		}
		out.write((char*)(&has_next), sizeof(has_next));
		if (has_next)
		{
			size_t next= nodes_to_id.at(current->next);
			out.write((char*)(&next), sizeof(next));
		}
		out.write((char*)(&has_rand), sizeof(has_rand));
		if (has_rand)
		{
			size_t rand= nodes_to_id.at(current->rand);
			out.write((char*)(&rand), sizeof(rand));
		}
		current= current->next;
		if (current == root)
		{
			break;
		}
	}
}

ListNode* LinkedListSerializer::deserialize(std::ifstream& in) {
	if (!in.is_open())
	{
		std::cerr << "Unable to open file." << std::endl;
		return nullptr;
	}

	std::vector<ListNode*> nodes;
	std::unordered_map<size_t, std::array<size_t, 3>> unique_nodes_relatives;
	std::unordered_map<size_t, std::array<bool, 3>> node_has_relatives;

	size_t number_of_nodes= 0;
	in.read((char*)&number_of_nodes, sizeof(number_of_nodes));
	if (number_of_nodes == 0)
	{
		return nullptr;
	}

	nodes.resize(number_of_nodes);
	for (size_t node_id= 0; node_id < number_of_nodes; ++node_id)
	{
		size_t data_size= 0;
		in.read((char*)&data_size, sizeof(data_size));
		std::string data;
		data.resize(data_size);
		in.read(&data[0], data_size);

		size_t prev= 0, next= 0, rand= 0;
		bool has_prev, has_next, has_rand;

		in.read((char*)(&has_prev), sizeof(has_prev));
		if (has_prev)
		{
			in.read((char*)&prev, sizeof(prev));
		}
		in.read((char*)(&has_next), sizeof(has_next));
		if (has_next)
		{
			in.read((char*)&next, sizeof(next));
		}
		in.read((char*)(&has_rand), sizeof(has_rand));
		if (has_rand)
		{
			in.read((char*)&rand, sizeof(rand));
		}

		ListNode* node= new ListNode;
		node->data= data;
		nodes[node_id]= node;
		node_has_relatives.emplace(node_id, std::array<bool, 3>{has_prev, has_next, has_rand});
		unique_nodes_relatives.emplace(node_id, std::array<size_t, 3>{prev, next, rand});
	}

	for (size_t node_id= 0; node_id < number_of_nodes; ++node_id)
	{
		auto relatives= unique_nodes_relatives.at(node_id);
		auto has_relatives= node_has_relatives.at(node_id);
		ListNode* node= nodes.at(node_id);
		if (has_relatives[0])
		{
			size_t prev= relatives[0];
			node->prev= nodes.at(prev);
		}
		if (has_relatives[1])
		{
			size_t next= relatives[1];
			node->next= nodes.at(next);
		}
		if (has_relatives[2])
		{
			size_t rand= relatives[2];
			node->rand= nodes.at(rand);
		}
	}

	return nodes.at(0);
}