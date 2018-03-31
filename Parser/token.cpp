#include"token.hpp"

token::token(token_type _type, char* _value)
{
    type = _type;
    strncpy(value, _value, MAX_LEN_TOKEN);
}


token::token(const token& src)
{
    type = src.type;
    strncpy(value, src.value, MAX_LEN_TOKEN);
}


Arr_Token::Arr_Token()
{
    arr_size = DEFAULT_LEN_ARR_TOKEN;
    arr_len = 0;
    arr = (token*)malloc(arr_size*sizeof(token));

    if(!arr){printf("Memory Error\n");exit(1);}
}


Arr_Token::Arr_Token(const Arr_Token& src)
{
     arr_size = src.arr_size;
     arr_len = src.arr_len;
     arr = (token*)malloc(arr_size*sizeof(token));

     if(!arr){printf("Memory Error\n");exit(1);}

     for(int i=0; i<src.arr_len; i++)
         arr[i] = src.arr[i];
}

Arr_Token::~Arr_Token()
{
    assert(arr!=NULL);
    free(arr);
}


token Arr_Token::operator [] (int index)
{
    if(index >= arr_len) {printf("Out of token array \n"); exit(1);}

    return arr[index];
}


void Arr_Token::push(token _token)
{
    assert(arr_len<=arr_size);
    if(arr_len == arr_size)
    {
        arr_size = 2*arr_size;
        arr = (token*)realloc(arr, arr_size*sizeof(token));
    }

    arr[arr_len] = _token;
    arr_len++;
}


void Arr_Token::push(token_type type,const char* value)
{
    char copy_value[100];
    strcpy(copy_value, value);
    token new_token(type, copy_value);

    this->push(new_token);
}


static bool is_equal(const char* str1,const char* str2, int start)
{
    int i=0;
    while(str1[i]!='\0')
    {
        if((start+i) ==  strlen(str2))
            return false;
        if(str2[start+i] != str1[i])
            return false;
        i++;
    }

    return true;
}

static void get_NUMBER(char* ret_str, const char* str, int start_index)
{
    int j=0;
    bool get_point = false;

    if(str[start_index] == '-')
        ret_str[j++] = '-';

    while(((str[start_index+j]>='0')&&(str[start_index+j]<='9'))||(str[start_index+j] == '.'))
    {
        if(str[start_index+j] == '.')
            (get_point)?(printf("Встречено две точки во float числе, выражение неверно\n")) : (get_point = true);
        ret_str[j] = str[start_index+j];
        j++;
    }

    ret_str[j] = '\0';
}

Arr_Token::Arr_Token(const char* str)
{
    arr_size = DEFAULT_LEN_ARR_TOKEN;
    arr_len  = 0;
    arr = (token*)malloc(arr_size*sizeof(token));

    for(int i=0; i<strlen(str); i++)
    {
        switch(str[i])
        {
            case '+': push(T_OPERATOR, "+"); break;
            case '*': push(T_OPERATOR, "*"); break;
            case '/': push(T_OPERATOR, "/"); break;
            case '^': push(T_OPERATOR, "^"); break;

            case '(': push(T_BRACKET, "("); break;
            case ')': push(T_BRACKET, ")"); break;

            case '-': push(T_OPERATOR, "-"); break;

            case 'a':
                if(is_equal("arccos", str, i))
                {
                    i+=5;
                    push(T_OPERATOR, "arccos");
                }
                else if(is_equal("arcctg",str, i))
                {
                    i+=5;
                    push(T_OPERATOR, "arcctg");
                }
                else if(is_equal("arctg", str, i))
                {
                    i+=4;
                    push(T_OPERATOR, "arctg");
                }
                else if(is_equal("arcsin",str, i))
                {
                    i+=5;
                    push(T_OPERATOR, "arcsin");
                }
                else
                    push(T_VAR, "a");
                break;


            case 'c':
                if(is_equal("cos", str, i))
                {
                    i+=2;
                    push(T_OPERATOR, "cos");
                }
                else
                if(is_equal("ctg",str, i))
                {
                    i+=2;
                    push(T_OPERATOR, "ctg");
                }
                else
                    push(T_VAR, "c");
                break;


            case 'l':
                if(is_equal("ln", str, i))
                {
                    i+=1;
                    push(T_OPERATOR, "ln");
                }
                else
                    push(T_VAR, "l");
                break;


            case 'e':
                if(is_equal("exp", str, i))
                {
                    i+=2;
                    push(T_OPERATOR, "exp");
                }
                else
                    push(T_VAR, "e");
                break;


            case 's':
                if(is_equal("sin", str, i))
                {
                    i+=2;
                    push(T_OPERATOR, "sin");
                }
                else
                    push(T_VAR, "s");
                break;


            case 't':
                if(is_equal("tg", str, i))
                {
                    i+=1;
                    push(T_OPERATOR, "tg");
                }
                else
                {
                    push(T_VAR, "t");
                }
                break;

            default:
                if((str[i]>='0')&&(str[i]<='9'))
                {
                    char val[100];

                    get_NUMBER(val, str, i);

                    i+=strlen(val)-1;
                    push(T_NUMBER, val);
                }
                else if((str[i]>='a')&&(str[i]<='z')||(str[i]>='a')&&(str[i]<='z'))
                {
                    char val[2];
                    val[0] = str[i];
                    val[1] = '\0';
                    push(T_VAR, val);
                }
                break;

        }
    }
}

