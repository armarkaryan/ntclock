#ifndef NTLAYOUTMANAGER_H
#define NTLAYOUTMANAGER_H

#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include "nttypes.h"
#include "ntimage.h"

class NTLayoutManager : public NTObject {
public:
	enum class LayoutType {
		HORIZONTAL,
		VERTICAL,
		GRID,
		ABSOLUTE
	};

	NTLayoutManager(NTObject* parent = nullptr, const std::string& name = "");
	~NTLayoutManager();

	// Add an image to be managed
	void addImage(NTImage* image);

	// Remove an image
	void removeImage(NTImage* image);

	// Clear all images
	void clearImages();

	// Set layout type
	void setLayoutType(LayoutType type);

	// Set spacing between elements
	void setSpacing(int spacing);

	// Set margins (top, right, bottom, left)
	void setMargins(int top, int right, int bottom, int left);

	// Update all positions according to layout rules
	void updateLayout(int containerWidth, int containerHeight);

	// Center the entire layout in the container
	void centerInContainer(int containerWidth, int containerHeight);

private:
	LayoutType _layoutType;
	int _spacing;
	struct {
		int top;
		int right;
		int bottom;
		int left;
	} _margins;

	std::vector<NTImage*> _images;
	std::mutex _imagesMutex;

	void updateHorizontalLayout(int containerWidth, int containerHeight);
	void updateVerticalLayout(int containerWidth, int containerHeight);
	void updateGridLayout(int containerWidth, int containerHeight);
};

#endif // NTLAYOUTMANAGER_H
