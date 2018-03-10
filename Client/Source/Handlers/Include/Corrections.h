//-- ******************************************* --//
//-- *************** Corrections *************** --//
//-- ******************************************* --//

#ifndef CORRECTIONSH
#define CORRECTIONSH

//-- ����������� ��������������� ������ --//
#include <MapsID.h>

//-- ����������� JSON --//
#include <System.JSON.hpp>


#include "MainForm_Delta.h"



namespace HandlersNS
{

	//-- �������-���������� ��������� ��������� --//
	void getCorrections(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ���������� ��������� --//
	void CheckAddCorrection(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ��������� ��������� --//
	void CheckEditCorrection(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� �������� ��������� --//
	void CheckDeleteCorrection(TJSONObject *json_object_parse);

	//-- �������-���������� ��������� ��������� --//
	void editCorrection(TJSONObject *json_object_parse);

	//-- �������-���������� ���������� ��������� --//
	void addCorrection(TJSONObject *json_object_parse);

	//-- �������-���������� �������� ��������� --//
	void deleteCorrection(TJSONObject *json_object_parse);

}

#endif
