/*!	\file		ntobject.h
 *	\brief		Base class module for NT (header file).
 *	\details	Contains the NTObject class definitions.
 *	\author		Arthur Markaryan
 *	\date		18.04.2025
 *	\copyright	Arthur Markaryan
 */

#ifndef NTOBJECT_H
#define NTOBJECT_H

/*!	\brief	Standard vector library */
#include <vector>
/*!	\brief	Standard string library */
#include <string>

/*!	\brief	Base NT types */
#include "nttypes.h"

/*!	\class      NTObject
 *	\brief      Base class for NT objects.
 *	\details	Represents the core functionality for objects in the NT system.
 */
class NTObject {
public:
    /*!	\brief		Constructor
     *	\param		parent	Pointer to the parent object (default: nullptr)
     *	\param		name	Object name (default: empty string)
     */
    NTObject(NTObject *parent = nullptr, const std::string &name = "");

    /*!	\brief	Destructor */
    ~NTObject();

    /*!	\brief		Sets the parent object
     *	\details	Updates the parent-child relationship.
     *	\param		parent	Pointer to the parent object
     *	\note		Pass nullptr to remove parent relationship
     */
    void setParent(NTObject *parent);

    /*!	\brief		Gets the parent object
     *	\return		Pointer to the parent object or nullptr if none exists
     */
    NTObject *parent() const;

    /*!	\brief		Sets the object name
     *	\param		name	New name for the object
     */
    void setName(const std::string &name);

    /*!	\brief		Gets the object name
     *	\return		Current name of the object
     */
    std::string name() const;

private:
    NTObject *_parent;	/*!< Pointer to parent object */
    std::string _name;	/*!< Object name */
};

#endif // NTOBJECT_H
