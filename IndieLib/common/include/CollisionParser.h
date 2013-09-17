/*****************************************************************************************
 * Desc: Parse collision files
 *****************************************************************************************/

/*
 IndieLib 2d library Copyright (C) 2005 Javier LÛpez LÛpez (javierlopezpro@gmail.com)
 
 This library is free software; you can redistribute it and/or modify it under the
 terms of the GNU Lesser General Public License as published by the Free Software
 Foundation; either version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License along with
 this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
 Suite 330, Boston, MA 02111-1307 USA
 */


#ifndef _COLLISIONPARSER_
#define _COLLISIONPARSER_

// ----- Includes -----

#include <list>


// --------------------------------------------------------------------------------
//									CollisionParser
// --------------------------------------------------------------------------------

/** @cond DOCUMENT_PRIVATEAPI */
class CollisionParser {
public:

	static CollisionParser *instance();

	// ----- Methods -----

	bool parseCollision(list <BOUNDING_COLLISION *> *pBList, const char *pFile);
	void setBoundingTriangle(list <BOUNDING_COLLISION *> *pBList, const char *pId, int pAx, int pAy, int pBx, int pBy, int pCx, int pCy);
	void setBoundingCircle(list <BOUNDING_COLLISION *> *pBList, const char *pId, int pOffsetX, int pOffsetY, int pRadius);
	void setBoundingRectangle(list <BOUNDING_COLLISION *> *pBList, const char *pId, int pOffsetX, int pOffsetY, int pWidth, int pHeight);
	void deleteBoundingAreas(list <BOUNDING_COLLISION *> *pBList, const char *pId);

protected:

	CollisionParser()  {}
	CollisionParser(const CollisionParser &);
	CollisionParser &operator = (const CollisionParser &);

private:
	static CollisionParser *_pinstance;
};

/** @endcond */

#endif // _COLLISIONPARSER_
