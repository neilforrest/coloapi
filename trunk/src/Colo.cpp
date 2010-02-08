#include <H3D/Colo/Colo.h>
#include <sstream>

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