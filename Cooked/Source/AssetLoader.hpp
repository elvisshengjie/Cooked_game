/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file AssetLoader.hpp
@author Norman Chan (chan.f)

*/
#include "JsonParser.hpp"
#include "render.hpp"

class RectLoader {
public:
	static bool LoadRectangles(const std::string& filename);

private:
	static bool LoadRect(const JSONObject& obj, Rect& rect);
	static bool LoadRectArray(const JSONObject& root, const std::string& key, std::vector<Rect>& rects);
};