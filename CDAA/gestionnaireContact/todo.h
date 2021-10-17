#ifndef TODO_H
#define TODO_H

#include <string>
#include "interaction.h"

using namespace std;

class Todo
{
private:
    string contenu;
    tm* date;
    Interaction* owner;
public:
    Todo();

    void setContenu(const string &);
    void setDate(const tm &);
    void setInteraction(const Interaction &);

    string const getContenu();
    tm* getTime();
    Interaction* getInteraction();
};

#endif // TODO_H
