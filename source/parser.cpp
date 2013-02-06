#include "headers/parser.h"

Parser::Parser(std::string filename)
{
    num_of_tags = 0;

    file_location = filename;
    file.open(file_location.c_str());
}

Parser::Parser(void)
{

}

Parser::~Parser()
{
    delete [] tags;
    delete [] data;
}

bool Parser::test_file()
{
    if(!file.good())
    {
        printf("ERROR: The file located at '%s' could not be read or is non-existent!\n", file_location.c_str());
        return false;
    }
    return true;
}

int Parser::init_tags()
{
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string line;
    while(!file.eof())
    {
        getline(file, line);

        int j = 0;
        while((line[j] == '\t') || (line[j] == ' ')) j++;

        if((line[j] == '<') && (line[j + 1] != '/')) {
            num_of_tags++;
        }
    }

    tags = new std::string[num_of_tags];
    data = new Tag_Data[num_of_tags];

    return num_of_tags;
}

bool Parser::load_data()
{
    load_tags();
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string line;
    int tagNum = 0;

    while(!file.eof())
    {
        getline(file, line);

        int j = 0;
        while((line[j] == '\t') || (line[j] == ' ')) j++;

        if((line[j] == '<') && (line[j + 1] != '/')) {
            int i = j;
            while(line[i] != '>') {
                i++;
            }

            bool row;
            bool vert = false;
            bool vertCheck = true;
            int u = i + 1;
            for(int u = i; u < i + 100; u++)
            {
                if(!row && !vert) {
                    if(line.substr(u, 2) == "</") {
                        int u1 = u;
                        row = true;
                        while(line[u1] != '>') {
                            u1++;
                            //printf("%s vs. %s\n", line.substr(u+2, u1 - u).c_str(), data[tagNum].tag.c_str());
                        }
                        if(line.substr(u + 2, u1 - (u + 2)) != data[tagNum].tag) {
                            printf("ERROR (SYNTAX): Opening and closing tags do not match.\n%s and %s\n", data[tagNum].tag.c_str(), line.substr(u + 2, u1 - (u + 2)).c_str());
                            return false;
                        }
                    }
                }
            }
            if(row) {
                int k = i;
                k++;
                while(line[k] == ' ') k++;

                int q = k;
                while(line[q] != '<') q++;

                data[tagNum].data = line.substr(k, q - k);
                tagNum++;
            }

            if(vert)
            {
                while(line[0] == 0) {
                    getline(file, line);
                }
                printf("%c\n", line[0]);
                data[tagNum].data = line;
            }
        }

    }
}

void Parser::load_tags()
{
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string line;
    int tagNum = 0;

    while(!file.eof())
    {
        getline(file, line);

        int j = 0;
        while((line[j] == '\t') || (line[j] == ' ')) j++;

        if((line[j] == '<') && (line[j + 1] != '/')) {

            int i = j;
            while(line[i] != '>') {
                i++;
            }

            i--;

            data[tagNum].tag = line.substr(j + 1, i - j);
            tagNum++;
        }
    }
}

void Parser::show_tags()
{
    printf("Tags:\n");
    for(int i = 0; i < num_of_tags; i++)
    {
        printf("    %s: %s\n", data[i].tag.c_str(), data[i].data.c_str());
    }
    printf("\n");
}

void Parser::display_file()
{
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string line;
    while(!file.eof())
    {
        getline(file, line);
        printf("%s\n", line.c_str());
    }
}
