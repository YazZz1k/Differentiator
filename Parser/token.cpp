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
    if(index >= arr_len) {printf("Out of array\n"); exit(1);}

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


void Arr_Token::push(token_type type, char* value)
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
        if(str2[start+i] != str1[i])
            return false;
        i++;
    }

    return true;
}

Arr_Token::Arr_Token(char* str)
{
    arr_size = DEFAULT_LEN_ARR_TOKEN;
    arr_len  = 0;
    arr = (token*)malloc(arr_size*sizeof(token));

    for(int i=0; i<strlen(str); i++)
    {
        switch(str[i])
        {
            case '+': this->push(OPERATOR, "+"); break;
            case '-': this->push(OPERATOR, "-"); break;
            case '*': this->push(OPERATOR, "*"); break;
            case '/': this->push(OPERATOR, "/"); break;
            case '^': this->push(OPERATOR, "^"); break;

            case '(': this->push(BREACKET, "("); break;
            case ')': this->push(BREACKET, ")"); break;


            case 'c':
                if(is_equal("cos", str, i))
                {
                    i+=2;
                    this->push(OPERATOR, "cos");
                }
                else
                if(is_equal("ctg",str, i))
                {
                    i+=2;
                    this->push(OPERATOR, "ctg");
                }
                else
                {
                    this->push(VAR, "c");
                }
                break;


            case 'l':
                if(is_equal("ln", str, i))
                {
                    i+=1;
                    this->push(OPERATOR, "ln");
                }
                else
                {
                    this->push(VAR, "l");
                }
                break;


            case 's':
                if(is_equal("sin", str, i))
                {
                    i+=2;
                    this->push(OPERATOR, "sin");
                }
                break;


            case 't':
                if(is_equal("tg", str, i))
                {
                    i+=1;
                    this->push(OPERATOR, "tg");
                }
                else
                {
                    this->push(VAR, "t");
                }
                break;


            default:
                if((str[i]>='0')&&(str[i]<='9'))
                {
                    char val[100];
                    for(int j=0; (j+i<strlen(str))&&(j<100); j++) val[j] = str[j+i];

                    sscanf(val,"%[0-9.]", val);

                    i+=strlen(val)-1;
                    this->push(NUMBER, val);
                }
                else if((str[i]>='a')&&(str[i]<='z')||(str[i]>='a')&&(str[i]<='z'))
                {
                    char val[2];
                    val[0] = str[i];
                    val[1] = '\0';
                    this->push(VAR, val);
                }
                break;

        }
    }
}
