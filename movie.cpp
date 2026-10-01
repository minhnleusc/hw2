#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Movie::Movie(const std::string category, const std::string name, double price,
           int qty, const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> words = parseStringToWords(name_);
    words.insert(convToLower(genre_));
    
    return words;
}

std::string Movie::displayString() const
{
    std::ostringstream os;
    os << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_
       << "\n" << std::fixed << std::setprecision(2)
       << price_ << " " << qty_ << " left.";
    return os.str();
}

void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << "\n";
}
