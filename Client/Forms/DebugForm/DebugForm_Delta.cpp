//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DebugForm_Delta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDebugForm *DebugForm;
//---------------------------------------------------------------------------
__fastcall TDebugForm::TDebugForm(TComponent* Owner)
	: TForm(Owner)
{
}


//---------------------------------------------------------//
//------------ ����������� ����������� ������� ------------//
//---------------------------------------------------------//

//-- ������� ������ ����� --//
void __fastcall TDebugForm::FormShow(TObject *Sender)
{
	//-- ������� ���� ����� --//
	DebugMemo->Clear();

	//-- �������� ����� � ���� --//
	DebugMemo->Lines->Add( MainForm->engine->GetLogs() );
}


