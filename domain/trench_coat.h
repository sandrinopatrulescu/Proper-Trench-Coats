//
// Created by kamui on 23.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_TRENCH_COAT_H
#define A45_915_PATRULESCU_SANDRINO_TRENCH_COAT_H

#include<iostream>

class TrenchCoat{
private:
        int size;
        std::string colour;
        int price;
        int quantity;
        std::string photograph;
public:
    TrenchCoat();
    /// \def creates a new trench coat
    /// \param size - integer between 102 and 137 (represents bust size)
    /// \param colour - non-empty string
    /// \param price - positive integer
    /// \param quantity - non-null integer
    /// \param photograph - non-empty string
    TrenchCoat(int size, std::string colour, int price, int quantity , std::string photograph);
    TrenchCoat(const TrenchCoat& trench_coat);
    TrenchCoat& operator=(const TrenchCoat& trench_coat);
    ~TrenchCoat();

    bool operator==(TrenchCoat const& trench_coat) const;
    bool operator!=(TrenchCoat const& trench_coat) const;

    std::string get_id() const;
    int get_size() const;
    std::string get_colour() const;
    int get_price() const;
    int get_quantity() const;
    std::string get_photograph() const;
    
    void set_size(int new_size);
    void set_colour(std::string new_colour);
    void set_price(int new_price);
    void set_quantity(int new_quantity);
    void set_photograph(std::string new_photograph);

    std::string printable() const;
    friend std::ostream& operator<<(std::ostream&, const TrenchCoat&);
    friend std::istream& operator>>(std::istream&, TrenchCoat&);

};

bool size_is(const TrenchCoat&, void**);



#endif //A45_915_PATRULESCU_SANDRINO_TRENCH_COAT_H
