/*!	\file		ntobject.cpp
 *	\brief		Implementation of the NTObject class
 *	\author		Arthur Markaryan
 *	\date		18.04.2025
 *	\copyright	Arthur Markaryan
 */

#include "ntobject.h"

/*!	\brief		Constructor
 *	\param[in]	parent	Pointer to the parent object (default: nullptr)
 *	\param[in]	name	Object name (default: empty string)
 */
NTObject::NTObject(NTObject *parent, const std::string &name) :
    _parent(parent),
    _name(name)
{
    // Initialization handled in member initializer list
}

/*!	\brief	Destructor
 *	\note	Parent-child relationships should be managed by the owner class
 */
NTObject::~NTObject()
{
    // No dynamic resources to free
}

/*!	\brief		Sets the parent object
 *	\param[in]	parent	Pointer to the new parent object
 *	\note		Simple assignment, no reference counting or ownership management
 */
void NTObject::setParent(NTObject *parent)
{
    _parent = parent;
}

/*!	\brief		Gets the parent object
 *	\return		Pointer to the parent object or nullptr if none exists
 */
NTObject *NTObject::parent() const
{
    return _parent;
}

/*!	\brief		Sets the object name
 *	\param[in]	name	New name for the object
 */
void NTObject::setName(const std::string &name)
{
    _name = name;
}

/*!	\brief		Gets the object name
 *	\return		Copy of the object's name string
 *	\note		Returns by value to maintain encapsulation
 */
std::string NTObject::name() const
{
    return _name;
}
