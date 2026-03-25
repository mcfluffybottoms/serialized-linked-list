#include "App.hpp"
#include "../src/LinkedListSerializer.hpp"
#include "Parser.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

void App::run(AppFunction func) {
	if (func == ParseAndSerialize)
	{
		ListNode* parsed_list= parse();
		serialize(parsed_list);
		delete_list(parsed_list);
	} else
	{
		ListNode* deserialized_list= deserialize();
		std::ofstream out("outlet_deserialized.out", std::ios::out);
		if (!out.is_open())
		{
			std::cout << "outlet_deserialized.out could not be open." << std::endl;
		}
		out << write_list_to_string(deserialized_list);
		delete_list(deserialized_list);
	}
}

ListNode* App::parse() {
	std::ifstream in("inlet.in", std::ios::in);
	if (!in.is_open())
	{
		std::cout << "inlet.in could not be open." << std::endl;
	}
	ListNode* parsed_value= Parser::parse(in);
	return parsed_value;
}

void App::serialize(ListNode* node) {
	std::ofstream out("outlet.out", std::ios::out);
	if (!out.is_open())
	{
		std::cout << "outlet.out could not be open." << std::endl;
		return;
	}
	LinkedListSerializer::serialize(out, node);
}

ListNode* App::deserialize() {
	std::ifstream in("outlet.out", std::ios::in);
	if (!in.is_open())
	{
		std::cout << "outlet.out could not be open." << std::endl;
		return nullptr;
	}
	ListNode* deserialized= LinkedListSerializer::deserialize(in);
	return deserialized;
}

std::string App::write_list_to_string(ListNode* root) {
	if (!root)
		return "";

	std::string file_data;
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

	current= root;
	while (current)
	{
		file_data+= current->data + ";";
		if (current->rand)
		{
			file_data+= std::to_string(nodes_to_id.at(current->rand));
		} else
		{
			file_data+= "-1";
		}
		file_data+= "\n";
		current= current->next;
		if (current == root)
		{
			break;
		}
	}

	return file_data;
}

void App::delete_list(ListNode* head) {
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
