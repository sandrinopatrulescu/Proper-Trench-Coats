//
// Created by kamui on 24.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_TRENCH_COAT_EXCEPTIONS_H
#define A45_915_PATRULESCU_SANDRINO_TRENCH_COAT_EXCEPTIONS_H

class TrenchCoatValidatorException: public std::exception{
private:
    std::string message;
public:

    explicit TrenchCoatValidatorException(const std::string& message){
        this->message = message;
    }
    const char * what () const noexcept override{
        return this->message.data();
    }

};

#endif //A45_915_PATRULESCU_SANDRINO_TRENCH_COAT_EXCEPTIONS_H
