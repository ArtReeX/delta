//-- ******************************************* --//
//-- ****************** Others ***************** --//
//-- ******************************************* --//

#ifndef OTHERSH
#define OTHERSH

//-- ����������� ��������������� ������ --//
#include <MapsID.h>


//-- ����������� JSON --//
#include <System.JSON.hpp>

#include "MainForm_Delta.h"


namespace HandlersNS
{

	//-- �������-���������� ����������� --//
	void CheckAuthorization(TJSONObject *json_object_parse);

	//-- �������-���������� ������� ������� --//
	void start(TJSONObject *json_object_parse);

	//-- �������-���������� ��������� ������� --//
	void stop(TJSONObject *json_object_parse);

	//-- �������-���������� ��������� ������� --//
	void getState(TJSONObject *json_object_parse);

	//-- �������-���������� ��������� ����� ����������� �������� --//
	void chain(TJSONObject *json_object_parse);

}


#endif
