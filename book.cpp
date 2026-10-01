#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Book::Book(const std::string category, const std::string name, double price,
           int qty, const std::string isbn, const std::string author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> words = parseStringToWords(name_);
    std::set<std::string> extra = parseStringToWords(author_);
    words = setUnion(words, extra);
    words.insert(convToLower(isbn_));
    return words;
}

std::string Book::displayString() const
{
    std::ostringstream os;
    os << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_
       << "\n" << std::fixed << std::setprecision(2)
       << price_ << " " << qty_ << " left.";
    return os.str();
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << "\n";
}