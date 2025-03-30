/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file collison.hpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
@author2
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
#pragma once

class Collison {
	public:
	bool collisonRect(float x0, float y0, float width0, float height0, float x1, float y1,
			float width1, float height1);
	void collisonobjectRect(float& x0, float& y0, float width0, float height0, float x1, float y1,
		float width1, float height1);
};
extern Collison Colingredientbox1;

