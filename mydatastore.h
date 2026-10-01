#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    bool addToCart(const std::string& username, Product* p);
    bool viewCart(const std::string& username, std::ostream& os) const;
    bool buyCart(const std::string& username);
private:
    // The store owns products/users; the index and carts only reference products.
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, User*> userIndex_;
    std::map<std::string, std::set<Product*> > keywordIndex_;
    std::map<std::string, std::vector<Product*> > carts_;
    MyDataStore(const MyDataStore&);
    MyDataStore& operator=(const MyDataStore&);
};
#endif