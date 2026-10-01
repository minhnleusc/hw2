#include "mydatastore.h"
#include "util.h"
#include <iomanip>

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore()
{
    for(size_t i = 0; i < products_.size(); ++i) delete products_[i];
    for(size_t i = 0; i < users_.size(); ++i) delete users_[i];
}
void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
    std::set<std::string> words = p->keywords();
    for(std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it)
        keywordIndex_[convToLower(*it)].insert(p);
}
void MyDataStore::addUser(User* u)
{
    users_.push_back(u);
    std::string name = convToLower(u->getName());
    userIndex_[name] = u;
    carts_[name];
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::set<Product*> matches;
    for(size_t i = 0; i < terms.size(); ++i) {
        std::map<std::string, std::set<Product*> >::const_iterator it =
            keywordIndex_.find(convToLower(terms[i]));
        std::set<Product*> current;
        if(it != keywordIndex_.end()) current = it->second;
        if(i == 0) matches = current;
        else if(type == 0) matches = setIntersection(matches, current);
        else matches = setUnion(matches, current);
        if(type == 0 && matches.empty()) break;
    }
    return std::vector<Product*>(matches.begin(), matches.end());
}
void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>\n";
    for(size_t i = 0; i < products_.size(); ++i) products_[i]->dump(ofile);
    ofile << "</products>\n<users>\n";
    for(size_t i = 0; i < users_.size(); ++i) users_[i]->dump(ofile);
    ofile << "</users>\n";
}
bool MyDataStore::addToCart(const std::string& username, Product* p)
{
    std::string name = convToLower(username);
    if(userIndex_.find(name) == userIndex_.end() || p == NULL) return false;
    carts_[name].push_back(p);
    return true;
}
bool MyDataStore::viewCart(const std::string& username, std::ostream& os) const
{
    std::map<std::string, std::vector<Product*> >::const_iterator it =
        carts_.find(convToLower(username));
    if(it == carts_.end()) return false;
    for(size_t i = 0; i < it->second.size(); ++i)
        os << "Item " << std::setw(3) << i + 1 << "\n"
           << it->second[i]->displayString() << "\n\n";
    return true;
}
bool MyDataStore::buyCart(const std::string& username)
{
    std::string name = convToLower(username);
    std::map<std::string, User*>::iterator user = userIndex_.find(name);
    if(user == userIndex_.end()) return false;
    std::vector<Product*>& cart = carts_[name];
    std::vector<Product*> remaining;
    for(size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];
        if(p->getQty() > 0 && user->second->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            user->second->deductAmount(p->getPrice());
        }
        else remaining.push_back(p);
    }
    cart.swap(remaining);
    return true;
}