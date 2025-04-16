#ifndef NTOBJECT_H
#define NTOBJECT_H

// Include standard vector and string libraries
#include <vector>
#include <string>

// Base class definition for NTObject (likely "NT" stands for something specific to the project)
class NTObject {
public:
    // Constructor and destructor
    //NTObject();
    NTObject(NTObject *parent = nullptr, const std::string &name = "");
    ~NTObject();

    // Sets the parent object
    void setParent(NTObject *parent);

    // Returns a pointer to the parent object
    NTObject *parent() const;

    // Sets the name of the object
    void setName(const std::string &name);

    // Returns a pointer to the object's name
    std::string name() const;

private:
    NTObject *_parent;
    std::string _name;
};

// End of header guard
#endif // NTOBJECT_H
