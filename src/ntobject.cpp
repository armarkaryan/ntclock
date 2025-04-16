// ntobject.cpp
// Implementation of the NTObject class

#include "ntobject.h"

// Constructor
NTObject::NTObject(NTObject *parent, const std::string &name) :
    _parent(parent), _name(name)
{
    //_parent(parent),	// Initialize parent pointer to null
    //_name(name)			// Initialize name to empty string
    // Basic object initialization
    // All members are already initialized in the initializer list
}

// Destructor
NTObject::~NTObject()
{
    // Currently no dynamic resources to free
    // Parent-child relationships should be managed by the owner class
}

// Sets the parent object
// Parameters:
//   parent - pointer to the parent object (can be null)
void NTObject::setParent(NTObject *parent)
{
    // Simple assignment, no reference counting or ownership management
    _parent = parent;
}

// Returns a pointer to the parent object
// Returns:
//   Pointer to the parent object or nullptr if no parent exists
NTObject *NTObject::parent() const
{
    return _parent;
}

// Sets the name of the object
// Parameters:
//   name - const reference to the new name string
void NTObject::setName(const std::string &name)
{
    // Copy the string content
    _name = name;
}

// Returns a pointer to the object's name
// Returns:
//   Pointer to the internal name string (note: this gives direct access to internal data)
//   Consider returning const std::string* or const reference instead for better encapsulation
std::string NTObject::name() const
{
    // WARNING: Returning direct pointer to internal data breaks encapsulation
    // In production code, consider returning const std::string* or const std::string&
    //return const_cast<std::string*>(&_name);
    return _name;
}
