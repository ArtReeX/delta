//-- ******************************************* --//
//-- ****************** Others ***************** --//
//-- ******************************************* --//

#ifndef OTHERSH
#define OTHERSH

//-- ОНДЙКЧВЕМХЕ ХДЕМРХТХЙЮРНПНБ ДЮММШУ --//
#include <MapsID.h>


//-- ОНДЙКЧВЕМХЕ JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"


namespace HandlersNS
{

	//-- тсмйжхъ-напюанрвхй юбрнпхгюжхх --//
	void CheckAuthorization(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй гюосяйю яепбепю --//
	void start(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй нярюмнбйх яепбепю --//
	void stop(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй янярнъмхъ яепбепю --//
	void getState(TJSONObject *json_object_parse);

	//-- тсмйжхъ-напюанрвхй онксвемхъ мнбни юпахрпюфмни ноепюжхх --//
	void chain(TJSONObject *json_object_parse);

}


#endif
