#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person
{
    public:
        Person();
        virtual void print(){
        std::cout <<"print";}
        void show();

    protected:

    private:
};

#endif // PERSON_H
