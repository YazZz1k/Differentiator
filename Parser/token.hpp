#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>


#define MAX_LEN_TOKEN 10
#define DEFAULT_LEN_ARR_TOKEN 128

typedef enum
{
    T_OPERATOR,
    T_VAR,
    T_NUMBER,
    T_BRACKET
} token_type;


class token
{
    public:
        token_type type;
        char value[MAX_LEN_TOKEN];
    public:
        token(token_type, char* _value);
        token(const token&);
};


class Arr_Token
{
    private:
        token* arr;
        int arr_size;  //размер выделенной памяти
        int arr_len;   //количество символов в массиве

    public:
        Arr_Token(const char*);
        Arr_Token();
        Arr_Token(const Arr_Token&);
        ~Arr_Token();
        void push(token);
        void push(token_type, const char* value);
        void do_empty(){arr_len = 0;}
        token operator [] (int index);

        int get_len()
        {
            return arr_len;
        }

        void print()
        {
            int i=0;
            while(i<arr_len)
            {
                printf("%s", arr[i].value);
                i++;
            }
            printf("\n");
        }
};

static void get_NUMBER(char* str, const char* copy_str, int start_index); 
static bool is_equal(const char* str1,const char* str2, int start);

#endif
