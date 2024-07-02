#ifndef STAFFREGISTER_H
#define STAFFREGISTER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Staff.h"
using namespace std;

class StaffRegister {
private:
    vector<shared_ptr<Staff>> staffMembers;

public:
    void addStaff(shared_ptr<Staff> staff) {
        staffMembers.push_back(staff);
    }

    void removeStaff(shared_ptr<Staff> staff) {
        auto it = find(staffMembers.begin(), staffMembers.end(), staff);
        if (it != staffMembers.end()) {
            staffMembers.erase(it);
        }
    }

    shared_ptr<Staff> findStaff(int employeeID) {
        for (auto& staff : staffMembers) {
            if (staff->getDetails().find(to_string(employeeID)) != string::npos) {
                return staff;
            }
        }
        return nullptr;
    }
};

#endif 