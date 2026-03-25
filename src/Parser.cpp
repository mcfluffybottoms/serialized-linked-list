#include "Parser.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
ParserError::ParserError(const std::string& message)
	: std::runtime_error(message) {}

bool is_number(const std::string& str) {
	if (str.empty())
		return false;
	for (char c: str)
	{
		if (!std::isdigit(c))
			return false;
	}
	return true;
}

std::string ltrim(const std::string& s) {
	auto it= std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	});
	return std::string(it, s.end());
}

std::string rtrim(const std::string& s) {
	auto it= std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	});
	return std::string(s.begin(), it.base());
}

std::string trim(const std::string& s) {
	return ltrim(rtrim(s));
}

Parser::Parser() {}

ListNode* Parser::parse(std::ifstream& reader) {
	if (!reader.is_open())
	{
		std::cerr << "Unable to open file." << std::endl;
		return nullptr;
	}

	ListNode* head= nullptr;
	ListNode* tail= nullptr;
	std::string line;

	std::vector<long long> rand_indices;
	std::vector<ListNode*> nodes;
	size_t line_num= 0;
	while (std::getline(reader, line))
	{
		++line_num;
		if (line.empty())
			continue;

		size_t del_pos= line.find(';');
		if (del_pos == std::string::npos)
		{
			throw ParserError("Parsing exception on line " + std::to_string(line_num) + ": wrong format.");
		}

		std::string fst= line.substr(0, del_pos);
		std::string snd= trim(line.substr(del_pos + 1));

		if (!is_number(snd) && snd != "-1")
		{
			throw ParserError("Parsing exception on line " + std::to_string(line_num) + ": rand index should be a positive number or -1.");
		}

		size_t rand_index= std::stoi(snd);
		rand_indices.push_back(rand_index);

		ListNode* new_node= new ListNode;
		new_node->data= fst;
		if (!head)
		{
			head= new_node;
			head->prev= nullptr;
			tail= new_node;
		} else
		{
			tail->next= new_node;
			new_node->prev= tail;
			tail= new_node;
		}
		nodes.push_back(new_node);
	}

	size_t number_of_nodes= rand_indices.size();
	for (size_t node_id= 0; node_id < number_of_nodes; ++node_id)
	{
		long long rand_index= rand_indices[node_id];
		nodes[node_id]->rand= rand_index != -1 && rand_index < (long long)number_of_nodes
			? nodes[rand_index]
			: nullptr;
	}

	return head;
}