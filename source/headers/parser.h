#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>

struct Tag_Data
{
    std::string tag;
    std::string data;
};

class Parser
{
    private:
        Tag_Data *data;

        std::string *tags;
        int num_of_tags;
        std::ifstream file;
        std::string file_location;
    public:
        Parser(std::string filename);
        Parser(void);
        ~Parser();

        bool test_file();
        bool error_check();
        int init_tags();
        void load_tags();

        bool load_data();

        void show_tags();
        void display_file();

        Tag_Data *retrieve_data()
        {
            return data;
        }
};

#endif
