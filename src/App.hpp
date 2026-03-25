#pragma once

#include "LinkedList.hpp"

enum AppFunction {
	ParseAndSerialize,
	Deserialize
};

struct App {
	void run(AppFunction func);

	ListNode* parse();

	void serialize(ListNode* node);

	ListNode* deserialize();

private:
	void delete_list(ListNode* head);
	std::string write_list_to_string(ListNode* head);
};