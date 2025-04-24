/*! \file       ntimage.h
 *  \brief      NT Image module (header file).
 *  \details    Contains the NTImage class definitions for image handling in the NT system.
 *  \author     Arthur Markaryan
 *  \date       24.04.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef NTIMAGE_H
#define NTIMAGE_H

/*! \brief  Standard vector library */
#include <vector>
/*! \brief  Standard string library */
#include <string>
/*! \brief  File stream operations */
#include <fstream>
/*! \brief  Standard exception handling */
#include <stdexcept>
/*! \brief  Standard algorithms */
#include <algorithm>

/*! \brief  Base NT object */
#include "ntobject.h"

/*! \class      NTImage
 *  \brief      Image class for NT system.
 *  \details    Represents an image object with position, color attributes and transparency support.
 *  \extends    NTObject
 */
class NTImage : public NTObject
{
public:
	/*! \brief      Default constructor
	 *  \param      parent  Pointer to the parent object (default: nullptr)
	 *  \param      name    Image name (default: empty string)
	 */
	NTImage(NTObject *parent = nullptr, const std::string &name = "");

	/*! \brief      Parameterized constructor
	 *  \param      parent      Pointer to the parent object
	 *  \param      name        Image name
	 *  \param      image       Vector of strings representing image data
	 *  \param      x           X coordinate of the image
	 *  \param      y           Y coordinate of the image
	 *  \param      colorPair   Color pair for the image
	 */
	NTImage(NTObject *parent, const std::string& name,
			const std::vector<std::string>& image,
			int x, int y, nt::ColorPair colorPair);

	/*! \brief  Destructor */
	~NTImage();

	/*! \brief      Copy constructor
	 *  \param      other   Reference to source NTImage object
	 */
	NTImage(const NTImage& other);

	/*! \brief      Assignment operator
	 *  \param      other   Reference to source NTImage object
	 *  \return     Reference to the assigned NTImage object
	 */
	NTImage& operator=(const NTImage& other);

	/*! \brief      Sets the X coordinate
	 *  \param      x   New X coordinate value
	 */
	void setx(int x){_x = x; notifyObservers(); _changed = true; }

	/*! \brief      Gets the X coordinate
	 *  \return     Current X coordinate value
	 */
	int x() const { return _x; }

	/*! \brief      Sets the Y coordinate
	 *  \param      y   New Y coordinate value
	 */
	void sety(int y){ _y = y; notifyObservers(); _changed = true; }

	/*! \brief      Gets the Y coordinate
	 *  \return     Current Y coordinate value
	 */
	int y() const { return _y; }

	/*! \brief      Sets the image data
	 *  \param      image   Vector of strings representing the new image data
	 */
	void setImage(const std::vector<std::string>& image);

	/*! \brief      Gets the image data
	 *  \return     Constant reference to the image data vector
	 */
	const std::vector<std::string>& image() const;

	/*! \brief      Sets the color pair
	 *  \param      colorPair   New color pair value
	 */
	void setColorPair(nt::ColorPair colorPair);

	/*! \brief      Gets the color pair
	 *  \return     Current color pair value
	 */
	nt::ColorPair colorPair() const { return _colorPair; }

	/*! \brief      Sets the image width
	 *  \param      width   New width value
	 */
	void setWidth(unsigned int width){ _width = width; notifyObservers(); _changed = true; }

	/*! \brief      Gets the image width
	 *  \return     Current width value
	 */
	unsigned int width() const;

	/*! \brief      Sets the image height
	 *  \param      height  New height value
	 */
	void setHeight(unsigned int height){ _height = height; notifyObservers(); _changed = true; }

	/*! \brief      Gets the image height
	 *  \return     Current height value
	 */
	unsigned int height() const;

	/*! \brief      Sets the transparency flag
	 *  \param      transparent New transparency value
	 */
	void setTransparent(unsigned int transparent){ _transparent = transparent; notifyObservers(); _changed = true;}

	/*! \brief      Gets the image transparency flag
	 *  \return     true if transparent false otherwise
	 */
	bool isTransparent() const { return _transparent; }

	/*! \brief      Set the changed flag
	 *  \return     height  New height value
	 */
	void setChanged(const bool &changed) { _changed = changed; }

	/*! \brief      Checks if image parameters is changed
	 *  \return     true if changed false otherwise
	 */
	bool isChanged() const { return _changed; }

private:
	std::vector<std::string> _image;	/*!< Image data storage */
	unsigned int _width;				/*!< Image width */
	unsigned int _height;				/*!< Image height */
	bool _transparent;					/*!< Transparency flag */
	int _x;								/*!< X coordinate */
	int _y;								/*!< Y coordinate */
	nt::ColorPair _colorPair;			/*!< Color pair attributes */
	bool _changed;						/*!< Changed parameter flag */

	/*! \brief      Copies data from another NTImage object
	 *  \param      other   Reference to source NTImage object
	 */
	void copyFrom(const NTImage& other);

	/*! \brief      Clears current image data */
	void clearImage();
};

#endif // NTIMAGE_H
