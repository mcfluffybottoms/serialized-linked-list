#include "../include/TestFramework.h"
#include "../src/LinkedListSerializer.hpp"
#include "TestUtils.hpp"
#include <filesystem>
#include <fstream>

void check_serializer(ListNode* to_serialize) {
	auto& runner= TestRunner::getInstance();

	if (std::filesystem::exists("outlet.out"))
	{
		std::remove("outlet.out");
	}

	std::ofstream out("outlet.out", std::ios::out);
	LinkedListSerializer::serialize(out, to_serialize);
	out.close();

	std::ifstream in("outlet.out", std::ios::in);
	ListNode* deserialized= LinkedListSerializer::deserialize(in);

	runner.assertTrue(compare_lists(to_serialize, deserialized),
					  "Before: " + print_list(to_serialize) + ", " + "After: " + print_list(deserialized));

	delete_list(to_serialize);
	delete_list(deserialized);
	std::remove("outlet.out");
}

void test_one_node() {
	ListNode* node= new ListNode;
	node->data= "Hello World";

	check_serializer(node);
}

void test_two_nodes() {
	ListNode* root= new ListNode;
	ListNode* next= new ListNode;

	root->data= "Root node";
	root->next= next;

	next->data= "Next node";
	next->prev= root;

	check_serializer(root);
}

void test_three_nodes() {
	ListNode* node1= new ListNode;
	ListNode* node2= new ListNode;
	ListNode* node3= new ListNode;

	node1->data= "apple";
	node2->data= "banana";
	node3->data= "carrot";

	node1->next= node2;
	node2->prev= node1;
	node2->next= node3;
	node3->prev= node2;

	node1->rand= node3;
	node2->rand= nullptr;
	node3->rand= node2;

	check_serializer(node1);
}


void test_four_nodes() {
	ListNode* node1= new ListNode;
	ListNode* node2= new ListNode;
	ListNode* node3= new ListNode;
	ListNode* node4= new ListNode;

	node1->data= "Node 1";
	node2->data= "Node 2";
	node3->data= "Node 3";
	node4->data= "Node 4";

	node1->next= node2;
	node2->prev= node1;
	node2->next= node3;
	node3->prev= node2;
	node3->next= node4;
	node4->prev= node3;

	check_serializer(node1);
}

void test_with_rand() {
	ListNode* node1= new ListNode;
	ListNode* node2= new ListNode;
	ListNode* node3= new ListNode;

	node1->data= "Alpha";
	node2->data= "Beta";
	node3->data= "Gamma";

	node1->next= node2;
	node2->prev= node1;
	node2->next= node3;
	node3->prev= node2;

	node1->rand= node3;
	node2->rand= node2;
	node3->rand= node1;

	check_serializer(node1);
}

void test_with_rand_big_cycle() {
	ListNode* node1= new ListNode;
	ListNode* node2= new ListNode;
	ListNode* node3= new ListNode;
	ListNode* node4= new ListNode;

	node1->data= "Node 1";
	node2->data= "Node 2";
	node3->data= "Node 3";
	node4->data= "Node 4";

	node1->next= node2;
	node2->prev= node1;
	node2->next= node3;
	node3->prev= node2;
	node3->next= node4;
	node4->prev= node3;

	node1->rand= node2;
	node2->rand= node3;
	node3->rand= node4;
	node4->rand= node1;

	check_serializer(node1);
}

void test_four_nodes_cycles_back() {
	ListNode* node1= new ListNode;
	ListNode* node2= new ListNode;
	ListNode* node3= new ListNode;
	ListNode* node4= new ListNode;

	node1->data= "Node 1";
	node2->data= "Node 2";
	node3->data= "Node 3";
	node4->data= "Node 4";

	node1->next= node2;
	node2->prev= node1;
	node2->next= node3;
	node3->prev= node2;
	node3->next= node4;
	node4->prev= node3;
	node4->next= node1;

	check_serializer(node1);
}

void test_with_non_ascii() {
	ListNode* node1= new ListNode;
	ListNode* node2= new ListNode;
	ListNode* node3= new ListNode;
	ListNode* node4= new ListNode;

	node1->data= "แผ่นดินฮั่นเสื่อ안녕하세요มโทรมแสนสังเวช";
	node2->data= "в Майнце в Германии";
	node3->data= "პროგრამებში ghb привет ghbdtn";
	node4->data= "Tiếng Việt có dấu";

	node1->next= node2;
	node2->prev= node1;
	node2->next= node3;
	node3->prev= node2;
	node3->next= node4;
	node4->prev= node3;

	node1->rand= node2;
	node2->rand= node3;
	node3->rand= node4;
	node4->rand= node1;
	std::string input= "แผ่นดินฮั่นเสื่อ안녕하세요มโทรมแสนสังเวช; 1 \nв Майнце в Германии; 2 \nპროგრამებში ghb привет ghbdtn; 3 \nTiếng Việt có dấu; 0 \n";
	check_serializer(node1);
}

int main() {
	auto& runner= TestRunner::getInstance();
	runner.runTest("test_one_node", []() { test_one_node(); });
	runner.runTest("test_two_nodes", []() { test_two_nodes(); });
	runner.runTest("test_three_nodes", []() { test_three_nodes(); });
	runner.runTest("test_four_nodes", []() { test_four_nodes(); });
	runner.runTest("test_with_rand", []() { test_with_rand(); });
	runner.runTest("test_with_rand_big_cycle", []() { test_with_rand_big_cycle(); });
	runner.runTest("test_four_nodes_cycles_back", []() { test_four_nodes_cycles_back(); });
	runner.runTest("test_with_non_ascii", []() { test_with_non_ascii(); });

	runner.printSummary();
}