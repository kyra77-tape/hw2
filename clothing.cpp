#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const string& name, double price, int qty,
           const string& size, const string& brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand)
{
}

set<string> Clothing::keywords() const
{
    set<string> k = parseStringToWords(name_);
    set<string> b = parseStringToWords(brand_);
    k.insert(b.begin(), b.end());
    return k;
}

string Clothing::displayString() const
{
    stringstream ss;
    ss << name_ << "\nSize: " << size_ << " BRAND: " << brand_ << "\n"
       << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}
