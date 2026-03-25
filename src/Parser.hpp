#pragma once

#include "LinkedList.hpp"
#include <stdexcept>
#include <string>

class ParserError : public std::runtime_error {
public:
	explicit ParserError(const std::string& message);
};

struct Parser {
	Parser();
	static ListNode* parse(std::ifstream& reader);
};