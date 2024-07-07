#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
    PUNCTUATION,
    INT_CONSTANT,
    FLOAT_CONSTANT,
    STRING_CONSTANT,
    TYPE,
    IDENT,
    KEYWORD,
    RELOP,
    OPERATION,
    SIGNAL,
    ATRIBUITION
};


class Token
{
    public:
        /**
         * Constructor;
         * 
         * @param type: type of the token
         * @param value: string value of the token
         */
        Token(TokenType type, std::string value, int line, int column) : _type(type), _value(value), _line(line), _column(column) {};

        /**
         * Getter
         * 
         * @return type of the token 
         */  
        const TokenType& type() { return _type; };

        /**
         * Getter
         * 
         * @return string value of the token
         */
        const std::string& value() { return _value; };
    
        /**
         * Getter
         * 
         * @return the line of occurence of token
        */
       int line() { return _line; };

        /**
         * Getter
         * 
         * @return the column of occurence of token
        */
       int column() { return _column; };

    private:
        TokenType _type;
        std::string _value;
        int _line;
        int _column;
};

#endif