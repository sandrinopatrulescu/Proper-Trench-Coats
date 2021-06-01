//
// Created by kamui on 23.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_DYNAMIC_VECTOR_EXCEPTIONS_H
#define A45_915_PATRULESCU_SANDRINO_DYNAMIC_VECTOR_EXCEPTIONS_H


class DynamicVectorException: public std::exception{
private:
    std::string message;
public:

    explicit DynamicVectorException(const std::string& message){
        this->message = message;
    }
    const char * what () const noexcept override{
        return this->message.data();
    }

};

#endif //A45_915_PATRULESCU_SANDRINO_DYNAMIC_VECTOR_EXCEPTIONS_H
