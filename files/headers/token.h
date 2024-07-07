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
         * @param line: line of token's occurrence
         * @param column: column of token's occurrence
         */
        Token(TokenType type, std::string value, unsigned int line, unsigned int column) : _type(type), _value(value), _line(line), _column(column) {};

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
         * @return the line of token's occurrence
        */
       const unsigned int line() { return _line; };

        /**
         * Getter
         * 
         * @return the column of token's occurrence
        */
       const unsigned int column() { return _column; };

    private:
        TokenType _type;
        std::string _value;
        unsigned int _line;
        unsigned int _column;
};

#endif