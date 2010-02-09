//  Copyright 2010, Neil Forrest
//
//  This file is part of ColoAPI.
//
//  ColoAPI is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  ColoAPI is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with ColoAPI.  If not, see <http://www.gnu.org/licenses/>.
//
#include <H3D/Colo/Colo.h>
#include <sstream>
#include <string.h>

using namespace std;

H3D::LibraryInfo getLibraryInfo() {
	H3D::LibraryInfo r = H3D::LibraryInfo::createEmptyInfo();
	std::stringstream s;
	s << COLO_MAJOR_VERSION << "."
	<< COLO_MINOR_VERSION << " (build "
	<< COLO_BUILD_VERSION << ")";

	strcpy(r.name, "ColoAPI" );
	strcpy( r.version, s.str().c_str() );
	//strcpy( r.web, "http://www.h3dapi.org/modules/mediawiki/index.php/UI" );
	strcpy( r.developer, "Neil Forrest" );
	strcpy( r.developer_web, "http://www.touchaptics.com/" );
	strcpy( r.info, "Various additional nodes to support graphic/haptic colocation display." );
	return r;
}
