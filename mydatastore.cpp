#include <iostream>
#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::~MyDataStore()
{
    for (size_t i = 0; i < products_.size(); i++) {
        delete products_[i];
    }
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
    set<string> kw = p->keywords();
    for (set<string>::iterator it = kw.begin(); it != kw.end(); ++it) {
        index_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    string key = convToLower(u->getName());
    users_[key] = u;
    carts_[key];
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> hits;
    if (terms.empty()) return hits;

    set<Product*> result;
    for (size_t i = 0; i < terms.size(); i++) {
        set<Product*> cur;
        map<string, set<Product*> >::iterator it = index_.find(terms[i]);
        if (it != index_.end()) cur = it->second;

        if (i == 0)         result = cur;
        else if (type == 0) result = setIntersection(result, cur);
        else                result = setUnion(result, cur);
    }
    hits.assign(result.begin(), result.end());
    return hits;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

bool MyDataStore::addToCart(const string& username, Product* p)
{
    string key = convToLower(username);
    if (users_.find(key) == users_.end()) return false;
    carts_[key].push_back(p);
    return true;
}

bool MyDataStore::viewCart(const string& username)
{
    string key = convToLower(username);
    if (users_.find(key) == users_.end()) return false;
    deque<Product*>& cart = carts_[key];
    for (size_t i = 0; i < cart.size(); i++) {
        cout << "Item " << (i + 1) << endl;
        cout << cart[i]->displayString() << endl << endl;
    }
    return true;
}

bool MyDataStore::buyCart(const string& username)
{
    string key = convToLower(username);
    map<string, User*>::iterator uit = users_.find(key);
    if (uit == users_.end()) return false;
    User* u = uit->second;

    deque<Product*>& cart = carts_[key];
    deque<Product*> remaining;
    for (size_t i = 0; i < cart.size(); i++) {
        Product* p = cart[i];
        if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            remaining.push_back(p);
        }
    }
    cart = remaining;
    return true;
}