/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file AssetLoader.cpp
@author Norman Chan (chan.f)

*/
#include "AssetLoader.hpp"


bool RectLoader::LoadRectangles(const std::string& filename) {
	JSONParser parser;
	JSONObject root;

	if (!parser.parseFile(filename, root)) {
		std::cerr << "Failed to parse rectangles file: " << filename << '\n';
		return false;
	}

	if (!LoadRect(root["backgroundRect"], backgroundRect)) return false;
	if (!LoadRect(root["dustbinRect"], dustbinRect)) return false;
	if (!LoadRect(root["ingredientBoxRect"], ingredientBoxRect)) return false;
	if (!LoadRect(root["mouseDevice"], mouseDevice)) return false;
	if (!LoadRect(root["backgroundMain_menu"], backgroundMain_menu)) return false;
	if (!LoadRect(root["digipen_logo"], digipen_logo)) return false;

	LoadRectArray(root, "highingredientBoxes", highingredientBoxes);
	LoadRectArray(root, "collisionBoxes", collisionBoxes);
	LoadRectArray(root, "objectcollision", objectcollision);
	LoadRectArray(root, "recipeBoxes", recipeBoxes);

	return true;
}

bool RectLoader::LoadRect(const JSONObject& obj, Rect& rect) {
	if (!obj.contains("x") || !obj.contains("y") ||
		!obj.contains("width") || !obj.contains("height")) {
		std::cerr << "Missing rect attributes\n";
		return false;
	}

	rect.x = obj.getFloat("x");
	rect.y = obj.getFloat("y");
	rect.width = obj.getFloat("width");
	rect.height = obj.getFloat("height");
	return true;
}

bool RectLoader::LoadRectArray(const JSONObject& root, const std::string& key, std::vector<Rect>& rects) {
	rects.clear();
	if (!root.contains(key)) return false;

	const auto& array = root[key].getArray();
	for (const auto& item : array) {
		Rect rect;
		if (LoadRect(item, rect)) {
			rects.push_back(rect);
		}
		else {
			std::cerr << "Error loading rect from array: " << key << '\n';
			return false;
		}
	}
	return true;
}