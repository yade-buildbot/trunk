/***************************************************************************
 *   Copyright (C) 2004 by Olivier Galizzi                                 *
 *   olivier.galizzi@imag.fr                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Body.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// we must initialize id = 0, otherwise BodyContainer will crash.
Body::Body () : 
	  Serializable()
	, id(0)
	, groupMask(1)
{
}

Body::Body (unsigned int newId, int newGroup) :
	  Serializable()
	, id(newId)
	, groupMask(newGroup)
	, physicalParameters(shared_ptr<PhysicalParameters>())
	, geometricalModel(shared_ptr<GeometricalModel>())
	, interactionGeometry(shared_ptr<InteractingGeometry>())
	, boundingVolume(shared_ptr<BoundingVolume>())
	
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void Body::registerAttributes()
{
	REGISTER_ATTRIBUTE(id);
	REGISTER_ATTRIBUTE(groupMask);
	REGISTER_ATTRIBUTE(isDynamic); // FIXME? : only used for interaction : no collision between 2 non dynamic objects

	REGISTER_ATTRIBUTE(physicalParameters);
	REGISTER_ATTRIBUTE(geometricalModel);
	REGISTER_ATTRIBUTE(interactionGeometry);
	REGISTER_ATTRIBUTE(boundingVolume);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////