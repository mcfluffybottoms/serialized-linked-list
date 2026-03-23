#include "LinkedList.hpp"
#include <unordered_map>
#include <queue>
#include <fstream>
#include <array>

void serialize(std::ofstream& out, ListNode* root) {
    std::queue<ListNode*> nodes_to_add;
    std::unordered_map<ListNode*, size_t> unique_nodes;
    size_t nextId = 0;

    // add nodes to map - can do easier since its a linked list
    nodes_to_add.push(root);
    nextId = 0;
    while(!nodes_to_add.empty()) {
        ListNode* node = nodes_to_add.front();
        nodes_to_add.pop();
        if(unique_nodes.count(node) == 0) {
            unique_nodes.emplace(node, nextId);
            ++nextId;
            if(node->prev) nodes_to_add.push(node->prev);
            if(node->rand) nodes_to_add.push(node->rand);
            if(node->next) nodes_to_add.push(node->next);
        }
    }

    // serialize all
    size_t number_of_nodes = unique_nodes.size();
    out.write((char*)(number_of_nodes), sizeof(number_of_nodes));
    for(auto [node, id] : unique_nodes) {
        // --- enter data
        out.write((char*)(node->data.size()), sizeof(node->data.size())); // !!
        out.write(node->data.c_str(), node->data.size());
        // --- then write node relatives
        size_t prev = unique_nodes.at(node->prev);
        size_t next = unique_nodes.at(node->next);
        size_t rand = unique_nodes.at(node->rand);
        out.write((char*)(prev), sizeof(prev));
        out.write((char*)(next), sizeof(next));
        out.write((char*)(rand), sizeof(rand));
    }
}

ListNode* deserialize(std::ifstream& in) {
    std::unordered_map<size_t, ListNode*> unique_nodes;
    std::unordered_map<size_t, std::array<size_t, 3>> unique_nodes_relatives;

    size_t number_of_nodes = 0;
    in.read((char*)&number_of_nodes, sizeof(number_of_nodes));

    for(size_t node_id = 0; node_id < number_of_nodes; ++node_id) {
        size_t data_size = 0;
        in.read((char*)&data_size, sizeof(data_size));
        std::string data;
        data.resize(data_size);
        in.read(&data[0], data_size);
        size_t prev, next, rand;
        in.read((char*)&prev, sizeof(prev));
        in.read((char*)&next, sizeof(next));
        in.read((char*)&rand, sizeof(rand));

        ListNode* node = new ListNode;
        node->data = data;
        unique_nodes.emplace(node_id, node);
        unique_nodes_relatives.emplace(node_id, std::array<size_t, 3>{prev, next, rand});
    }

    for(auto [id, node] : unique_nodes) {
        auto relatives = unique_nodes_relatives.at(id);
        size_t prev = relatives[0];
        size_t next = relatives[1];
        size_t rand = relatives[2];
        node->prev = unique_nodes.at(prev);
        node->next = unique_nodes.at(next);
        node->rand = unique_nodes.at(rand);
    }

    return unique_nodes.at(0);
}