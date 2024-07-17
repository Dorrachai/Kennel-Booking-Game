#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    int cookies;

public:
    User() : cookies(10) {} // Start with 10 cookies

    int getCookies() const {
        return cookies;
    }

    bool spendCookies(int amount) {
        if (cookies >= amount) {
            cookies -= amount;
            return true;
        }
        return false;
    }

    void addCookies(int amount) {
        cookies += amount;
    }
};

#endif // USER_H