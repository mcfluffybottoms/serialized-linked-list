#include "../include/TestFramework.h"
#include "../src/LinkedList.hpp"
#include "../src/Parser.hpp"
#include "TestUtils.hpp"
#include <filesystem>
#include <fstream>

void check_parser(const std::string& input, ListNode* expected) {
	auto& runner= TestRunner::getInstance();

	if (std::filesystem::exists("inlet.in"))
	{
		std::remove("inlet.in");
	}
	std::ofstream out("inlet.in", std::ios::out);
	out << input;
	out.close();

	std::ifstream in("inlet.in", std::ios::in);
	ListNode* actual= Parser::parse(in);

	runner.assertTrue(compare_lists(actual, expected),
					  "Actual: " + print_list(actual) + ", " + "Expected: " + print_list(expected));

	delete_list(expected);
	delete_list(actual);
	std::remove("inlet.in");
}

void test_one_node() {
	ListNode* node= new ListNode;
	node->data= "Hello World";

	std::string input= "Hello World;-1";
	check_parser(input, node);
}

void test_two_nodes() {
	ListNode* root= new ListNode;
	ListNode* next= new ListNode;

	root->data= "Root node";
	root->next= next;

	next->data= "Next node";
	next->prev= root;

	std::string input= "Root node;-1\nNext node;-1\n";
	check_parser(input, root);
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

	std::string input= "apple;2\nbanana;-1\ncarrot;1\n";
	check_parser(input, node1);
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

	std::string input= "Node 1;-1\nNode 2;-1\nNode 3;-1\nNode 4;-1\n";
	check_parser(input, node1);
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
	std::string input= "Alpha;2\nBeta;1\nGamma;0";
	check_parser(input, node1);
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
	std::string input= "Node 1;1\nNode 2;2\nNode 3;3\nNode 4;0\n";
	check_parser(input, node1);
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
	check_parser(input, node1);
}

int main() {
	auto& runner= TestRunner::getInstance();

	runner.runTest("test_one_node", []() { test_one_node(); });
	runner.runTest("test_two_nodes", []() { test_two_nodes(); });
	runner.runTest("test_three_nodes", []() { test_three_nodes(); });
	runner.runTest("test_four_nodes", []() { test_four_nodes(); });
	runner.runTest("test_with_rand", []() { test_with_rand(); });
	runner.runTest("test_with_rand_big_cycle", []() { test_with_rand_big_cycle(); });
	runner.runTest("test_with_non_ascii", []() { test_with_non_ascii(); });

	runner.printSummary();
}