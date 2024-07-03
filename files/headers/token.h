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
    END_OF_FILE,
    WAITING,
};


class Token
{
    public:
        /**
         * Constructor;
         * 
         * @param type: type of the token
         * @param line: file line of the token
         * @param column: file column of the token
         * @param value: string value of the token
         */
        Token(TokenType type, unsigned int line, unsigned int column, std::string value) : _type(type), _line(line), _column(column), _value(value) {};

        /**
         * Getter
         * 
         * @return type of the token 
         */  
        const TokenType& type() { return _type; };

        /**
         * Getter
         * 
         * @return file line of the token
         */
        const unsigned int& line() { return _line; };

        /**
         * Getter
         * 
         * @return file column of the token
         */
        const unsigned int& column() { return _column; };

        /**
         * Getter
         * 
         * @return string value of the token
         */
        const std::string& value() { return _value; };
    
    private:
        TokenType _type;
        unsigned int _line;
        unsigned int _column;
        std::string _value;
};

#endif