#ifndef CUSTOMERREGISTER_H
#define CUSTOMERREGISTER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Owner.h"
using namespace std;

class CustomerRegister {
private:
    vector<shared_ptr<Owner>> customers;

public:
    void addCustomer(shared_ptr<Owner> owner) {
        customers.push_back(owner);
    }

    void removeCustomer(shared_ptr<Owner> owner) {
        auto it = find(customers.begin(), customers.end(), owner);
        if (it != customers.end()) {
            customers.erase(it);
        }
    }

    shared_ptr<Owner> findCustomer(const string& name) {
        for (auto& customer : customers) {
            if (customer->getContactInfo().find(name) != string::npos) {
                return customer;
            }
        }
        return nullptr;
    }
};

#endif 