#include "huffman.hpp"

node::node(std::uint32_t new_frequency, unsigned char new_character):
        frequency(new_frequency),
        character(new_character),
        is_letter_node(true),
        left_child(nullptr),
        right_child(nullptr) {}
node::node(node* l_child, node* r_child):
        frequency((l_child -> get_frequency()) + (r_child -> get_frequency())),
        character('_'),
        is_letter_node(false),
        left_child(l_child),
        right_child(r_child) {}
node::node():
        frequency(0),
        character('_'),
        is_letter_node(false),
        left_child(nullptr),
        right_child(nullptr) {}
node::~node() {
    if (left_child)
        delete(left_child);
    if (right_child)
        delete(right_child);
}

std::uint32_t node::get_frequency() const {
    return frequency;
}
unsigned char node::get_character() const {
    return character;
}
node* node::get_left_child() const {
    return left_child;
}
node* node::get_right_child() const {
    return right_child;
}
void node::set_left_child(node* child) {
    left_child = child;
}
void node::set_right_child(node* child) {
    right_child = child;
}
bool node::is_character() const {
    return is_letter_node;
}
void node::set_is_character() {
    is_letter_node = true;
}
void node::set_character(unsigned char c) {
    character = c;
}
//get codes of all character by a detour of the tree
unsigned char node::find_path(std::map<unsigned char, std::vector<unsigned char>>& paths, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::vector<unsigned char>& path) const {
    if (is_letter_node) {
        if (paths.count(character) > 0) {
            paths[character] = path;
        }
        else {
            paths.insert({character, path});
        }
        codes.push_back({character, path});
        return character;
    }
    std::vector<unsigned char> left_path(path);
    std::vector<unsigned char> right_path(path);
    left_path.push_back(0);
    right_path.push_back(1);
    if (left_child)
        left_child -> find_path(paths, codes, left_path);
    if (right_child)
        right_child -> find_path(paths, codes, right_path);
    return 0;
}

//for using std::priority_queue we need a way to compare two nodes
bool less_than_by_frequency::operator()(node* lhs, node* rhs) const {
    return (lhs -> get_frequency()) > (rhs -> get_frequency());
}
//find a character by the path to it in the tree
std::pair<unsigned char, bool> find_in_tree(node* my_node, std::vector<char>& path, std::uint32_t i) {
    if (i >= static_cast<std::uint32_t>(path.size()))
        return {0, false};
    if (my_node -> is_character())
        return {my_node -> get_character(), true};
    if (path[i] == 0) {
        return find_in_tree(my_node -> get_left_child(), path, i + 1);
    }
    else {
        return find_in_tree(my_node -> get_right_child(), path, i + 1);
    }
}
//insert a new node in the tree by the path to it
void insert_in_tree(unsigned char let, node* my_node, std::vector<unsigned char>& path, std::uint32_t i) {
    if (i == static_cast<std::uint32_t>(path.size()))
        return;
    node* new_dir;
    if (path[i] == 1) {
        if (my_node -> get_right_child()) {
            new_dir = my_node -> get_right_child();
        }
        else {
            my_node -> set_right_child(new node());
            new_dir = my_node -> get_right_child();
        }
    } else {
        if (my_node -> get_left_child()) {
            new_dir = my_node -> get_left_child();
        }
        else {
            my_node -> set_left_child(new node());
            new_dir = my_node -> get_left_child();
        }
    }
    if (i == static_cast<std::uint32_t>(path.size()) - 1) {
        new_dir -> set_character(let);
        new_dir -> set_is_character();
        return;
    }
    insert_in_tree(let, new_dir, path, i + 1);
}
//returns a map of frequencies to all the characters from the input file
std::pair<std::map<unsigned char, std::uint32_t>, std::uint32_t> get_map_of_characters(const std::string& s, std::uint32_t& total_input) {
    std::map<unsigned char, std::uint32_t> my_map;
    std::uint32_t number = 0;
    total_input = 0;
    std::ifstream fin(s, std::ios::binary);
    if (!fin.is_open()) {
    }
    else {
        while(!(fin.eof())) {
            unsigned char buff[1];
            buff[0] = 0;
            unsigned char temp;
            fin.read(reinterpret_cast<char*>(buff), 1);
            if(fin.eof())
                break;
            ++total_input;
            temp = buff[0];
            ++number;
            if (my_map.find(temp) != my_map.end()) {
                ++my_map[temp];
            }
            else {
                my_map.insert({temp, 1});
            }
        }
    }
    return {my_map, number};
}
unsigned char get_byte(const std::vector<unsigned char>& arr) {
    unsigned char res = 0;
    for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(arr.size()); ++i) {
        res += static_cast<unsigned char>((arr[arr.size() - 1 - i]) ? (pow(2, i)) : (0));
    }
    return res;
}
//gets 2 paths - input and output files and writes auxiliary tables and coded sequence to the output file
//also prints size of used memory to the console
void write_to_file_binary(const std::string& f_in_path, const std::string& f_out_path, std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes, std::uint32_t number_of_ch, std::uint32_t& total_aux, std::uint32_t& total_coded) {
    std::ofstream fout(f_out_path, std::ios::binary);
    std::ifstream fin(f_in_path, std::ios::binary);
    std::map<unsigned char, std::vector<unsigned char>> my_map;
    for (const auto& e: codes) {
        my_map.insert(e);
    }
    if (fin.is_open() && fout.is_open()) {
        fout << static_cast<std::uint32_t>(number_of_ch) << '\n';
        fout << static_cast<std::uint32_t>(codes.size()) << '\n';
        for (const auto& e: codes) {
            fout << e.first << ' ';
            for (const auto& c: e.second) {
                fout << static_cast<unsigned char>(c);
            }
            fout << '\n';
        }
        std::vector<unsigned char> buffer(8,8);
        std::int32_t ptr = -1;
        total_aux = static_cast<std::uint32_t>(fout.tellp());
        while (!fin.eof()) {
            unsigned char buf[1];
            buf[0] = 0;
            fin.read(reinterpret_cast<char*>(buf), 1);
            if (fin.eof())
                break;
            std::vector<unsigned char> temp = my_map[buf[0]];
            for (const auto& e: temp) {
                ++ptr;
                if (ptr == 7) {
                    buffer[ptr % 8] = e;
                    ptr = -1;
                    fout << get_byte(buffer);
                } else {
                    buffer[ptr] = e;
                }
            }
        }
        if (ptr >= 0) {
            for (std::int32_t i = ptr + 1; i < static_cast<std::int32_t>(buffer.size()); ++i)
                buffer[i] = 0;
            fout << get_byte(buffer);
        }
    }
    total_coded = static_cast<std::uint32_t>(fout.tellp());
    total_coded -= total_aux;
}
//gets binary representation of std::uint32_teger
std::vector<unsigned char> get_vector_from_int(unsigned char c) {
    std::vector<unsigned char> res(8,0);
    if (c == 0) {
        res.push_back(0);
        return res;
    }
    std::uint32_t j = 1;
    while (c > 0) {
        res[8 - j] = c % 2;
        c = c / 2;
        ++j;
    }
    return res;
}
void print_sorted_codes(const std::vector<std::pair<unsigned char, std::vector<unsigned char>>>& codes) {
    for (const auto& pair: codes) {
        for (const auto& e: pair.second) {
            std::cout << static_cast<std::uint32_t>(e);
        }
        std::cout << " " << static_cast<std::uint32_t>(pair.first) << std::endl;;
    }
}
node* get_tree_of_codes(std::ifstream& fin, std::uint32_t& number, std::uint32_t& number_of_ch, std::uint32_t& total_aux) {
    unsigned char lit = 0;
    node* root_of_tree = new node();
    if (fin.is_open()) {
        unsigned char buf[1];
        fin >> number_of_ch;
        fin.read(reinterpret_cast<char *>(buf), 1);
        if (!fin.eof()) {
            fin >> number;
            fin.read(reinterpret_cast<char *>(buf), 1);
            for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(number); ++i) {
                std::vector<unsigned char> path;
                fin.read(reinterpret_cast<char *>(buf), 1);
                lit = buf[0];
                fin.read(reinterpret_cast<char *>(buf), 1);
                unsigned char curr = 0;
                std::uint32_t counter = 0;
                while ((curr != '\n') && (counter < 100)) {
                    fin.read(reinterpret_cast<char *>(buf), 1);
                    if (buf[0] != '\n')
                        path.push_back(buf[0]);
                    curr = buf[0];
                    ++counter;
                }
                insert_in_tree(lit, root_of_tree, path, 0);
            }
            total_aux = static_cast<std::uint32_t>(fin.tellg());
        }
    }
    return root_of_tree;
}
void print_to_file_decoded_characters(std::ifstream &fin, std::ofstream &fout, node *root_of_tree, std::uint32_t &number_of_ch, std::uint32_t &total_input) {
    std::uint32_t count = 0;
    node* root = root_of_tree;
    while (!fin.eof() && (count < static_cast<std::uint32_t>(number_of_ch))) {
        unsigned char buf[1];
        unsigned char c = 0;
        fin.read(reinterpret_cast<char*>(buf), 1);
        if (!fin.eof()) {
            c = buf[0];
            auto vector_form_of_ch = get_vector_from_int(c);
            for (std::uint32_t j = 0; j < 8; ++j) {
                if (vector_form_of_ch[j] == 0) {
                    if (root -> get_left_child()) {
                        root = root -> get_left_child();
                    }
                }
                else {
                    if (root -> get_right_child()) {
                        root = root -> get_right_child();
                    }
                }
                if (root -> is_character()) {
                    fout << root -> get_character();
                    root = root_of_tree;
                    ++count;
                    if (count >= static_cast<std::uint32_t>(number_of_ch))
                        break;
                }
            }
        }
        total_input = static_cast<std::uint32_t>(fin.tellg());
    }
}
//get codes in lexicography order by detour
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes_from_tree(node* root_of_tree, std::uint32_t& total_input, std::uint32_t& number_of_ch) {
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes;
    std::map<unsigned char, std::vector<unsigned char>> paths;
    std::vector<unsigned char> path;
    node* temp_node = root_of_tree;
    if (total_input != 0) {
        if (temp_node) {
            if (number_of_ch != 0) {
                temp_node -> find_path(paths, sorted_codes, path);
            } else {
                unsigned char letter = temp_node -> get_character();
                paths.insert({letter, {0}});
                sorted_codes.push_back({letter, {0}});
            }
        }
    }
    return sorted_codes;
}
std::uint32_t huffman_decode(const std::string &f_in_path, const std::string &f_out_path, bool flag_v) {
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    std::ifstream fin(f_in_path, std::ios::binary);
    std::ofstream fout(f_out_path, std::ios::binary);
    std::uint32_t number = 0;
    std::uint32_t number_of_ch = 0;
    node* root_of_tree = get_tree_of_codes(fin, number, number_of_ch, total_aux);
    print_to_file_decoded_characters(fin, fout, root_of_tree, number_of_ch, total_input);
    total_coded = static_cast<std::uint32_t>(fout.tellp());
    total_input -= total_aux;
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes = get_sorted_codes_from_tree(root_of_tree, total_aux, number);
    delete root_of_tree;
    std::cout << total_input << std::endl;
    std::cout << total_coded << std::endl;
    std::cout << total_aux << std::endl;
    if (flag_v) {
        print_sorted_codes(sorted_codes);
    }
    return number_of_ch;
}
//build Huffman tree
node* get_tree_of_characters(const std::string& fin_path, std::uint32_t& number_of_ch, bool& flag, std::uint32_t& total_input) {
    std::ifstream fin(fin_path, std::ios::binary);
    auto map_of_ch = get_map_of_characters(fin_path, total_input);
    auto my_map = map_of_ch.first;
    number_of_ch = map_of_ch.second;
    std::priority_queue<node*, std::vector<node*>, less_than_by_frequency> pq;
    for (const auto& e: my_map) {
        pq.push((new node(e.second, e.first)));
    }
    flag = false;
    if (pq.size() == 1)
        flag = true;
    while (pq.size() > 1) {
        auto p1 = pq.top();
        pq.pop();
        auto p2 = pq.top();
        pq.pop();
        auto n = new node(p1, p2);
        pq.push(n);
    }
    if (pq.empty()) {
        return nullptr;
    }
    node* res = pq.top();
    return res;
}
std::vector<std::pair<unsigned char, std::vector<unsigned char>>> get_sorted_codes(const std::string& fin_path, std::uint32_t& number_of_ch, bool& flag, std::uint32_t& total_input) {
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes;
    node* res = get_tree_of_characters(fin_path, number_of_ch, flag, total_input);
    std::map<unsigned char, std::vector<unsigned char>> paths;
    std::vector<unsigned char> path;
    if (res) {
        if (!flag) {
            res -> find_path(paths, sorted_codes, path);
        } else {
            unsigned char letter = res -> get_character();
            paths.insert({letter, {0}});
            sorted_codes.push_back({letter, {0}});
        }
        delete res;
        return sorted_codes;
    }
    return sorted_codes;
}
void huffman(const std::string& fin_path, const std::string& fout_path, bool flag_v) {
    std::ifstream fin(fin_path, std::ios::binary);
    std::ofstream fout(fout_path, std::ios::binary);
    std::uint32_t number_of_ch = 0;
    bool flag = false;
    std::uint32_t total_input = 0;
    std::uint32_t total_aux = 0;
    std::uint32_t total_coded = 0;
    std::vector<std::pair<unsigned char, std::vector<unsigned char>>> sorted_codes  = get_sorted_codes(fin_path, number_of_ch, flag, total_input);
    if (!sorted_codes.empty()) {
        write_to_file_binary(fin_path, fout_path, sorted_codes, number_of_ch, total_aux, total_coded);
    }
    std::cout << total_input << std::endl;
    std::cout << total_coded << std::endl;
    std::cout << total_aux << std::endl;
    if (flag_v) {
        print_sorted_codes(sorted_codes);
    }
}
void run_coding_or_decoding(std::string& path1, std::string& path2, bool f_v, bool f_c_d) {
    if (f_c_d) {
        huffman(path1, path2, f_v);
    } else {
        huffman_decode(path1, path2, f_v);
    }
}