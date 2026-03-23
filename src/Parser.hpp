#include <stdexcept>
#include <string>
#include "LinkedList.hpp"

class ParserError : public std::runtime_error {
public:
    explicit ParserError(const std::string& message);
};

struct Parser {
    Parser();
    static ListNode* parse(const std::string& file);
};