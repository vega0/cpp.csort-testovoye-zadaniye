#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>

class Person {

    private:

        std::string role_name;

    public:
        bool is_technical() {return this->role_name == "technical";}
        bool is_operator() {return this->role_name == "operator";}
        bool is_ingeneer() {return this->role_name == "ingeneer";}
        
        bool is_valid_role_name() {
            return is_technical() || is_operator() || is_ingeneer();
        }

        void set_role_name(const std::string & value) {this->role_name = value;}
        
        const std::string & get_role_name();
};

#endif // __PERSON_H__