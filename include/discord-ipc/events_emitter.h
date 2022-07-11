#pragma once
#include <string>
#include <functional>

std::string generate_uuid();

template<typename data_type>
struct node {
    data_type data;
    node<data_type>* next{};
};
template<typename emitter_data_type>
struct emitter_data {
    std::string key;
    emitter_data_type data;
};

template <class emitter_data_type>
class emitter {
protected:
    node<emitter_data<std::function<void(emitter_data_type&)>>>* node_head = new node<emitter_data<std::function<void(emitter_data_type&)>>>();
public:
    void emit(emitter_data_type& data) {
        auto node_pointer = this->node_head;
        while (node_pointer = node_pointer->next) {
            node_pointer->data.data(data);
        }
    };
    std::string on(std::function<void(emitter_data_type&)> data) {
        auto node_pointer = this->node_head;
        while (node_pointer->next) {
            node_pointer = node_pointer->next;
        };
        std::string sid = generate_uuid();

        node<emitter_data<std::function<void(emitter_data_type&)>>>* new_node = new node<emitter_data<std::function<void(emitter_data_type&)>>>();;
        new_node->data.key = sid;
        new_node->data.data = data;
        node_pointer->next = new_node;
        return sid;
    };
    bool contains(std::string key) {
        auto node_pointer = this->node_head;
        while (node_pointer->next && key != node_pointer->next->data.key) {
            node_pointer = node_pointer->next;
        };
        if (!node_pointer->next) return false;
        return true;
    };
    bool remove(std::string key) {
        auto node_pointer = this->node_head;
        while (node_pointer->next && key != node_pointer->next->data.key) {
            node_pointer = node_pointer->next;
        };
        if (!node_pointer->next) return false;
        auto key_pointer = node_pointer->next;
        node_pointer->next = node_pointer->next->next;
        delete key_pointer;
        return true;
    };
};

template <class emitter_data_type>
struct emitter_unique : emitter<emitter_data_type>{
public:
    bool emit(std::string key, emitter_data_type& data) {
        auto node_pointer = this->node_head;
        while (node_pointer = node_pointer->next) {
            if (key != node_pointer->data.key) continue;
            node_pointer->data.data(data);
            return true;
        }
        return false;
    };
};

template<class emitter_data_type>
struct events_emitter {
private:
    node<emitter_data<emitter<emitter_data_type&>>>* node_head = new node<emitter_data<emitter<emitter_data_type&>>>();
public:
    bool emit(std::string key, emitter_data_type& data) {
        auto node_pointer = this->node_head;
        while (node_pointer = node_pointer->next) {
            if (key != node_pointer->data.key) continue;
            node_pointer->data.data.emit(data);
            return true;
        }
        return false;
    };
    std::string on(std::string event_name, std::function<void(emitter_data_type&)> data) {
        auto node_pointer = this->node_head;
        while (node_pointer->next && event_name != node_pointer->next->data.key) {
            node_pointer = node_pointer->next;
        };
        if (!node_pointer->next) {
            node<emitter_data<emitter<emitter_data_type&>>>* new_node = new node<emitter_data<emitter<emitter_data_type&>>>;
            new_node->data.key = event_name;
            node_pointer->next = new_node;
        }
        return node_pointer->next->data.data.on(data);
    };
    bool remove(std::string event_name, std::string key) {
        auto node_pointer = this->node_head;
        while (node_pointer->next && event_name != node_pointer->next->data.key) {
            node_pointer = node_pointer->next;
        };
        if (!node_pointer->next) return false;
        return node_pointer->next->data.data.remove(key);
    };
};