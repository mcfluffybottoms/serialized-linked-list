#include <string>

struct ListNode {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr;
    std::string data;
};

void serialize(std::ofstream& out, const ListNode& node);
ListNode* deserialize(std::ifstream& in);