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
//------------ ÎÁÐÀÁÎÒ×ÈÊÈ ÑÒÀÍÄÀÐÒÍÛÕ ÑÎÁÛÒÈÉ ------------//
//---------------------------------------------------------//

//-- ÔÓÍÊÖÈß ÏÎÊÀÇÀ ÔÎÐÌÛ --//
void __fastcall TDebugForm::FormShow(TObject *Sender)
{
	//-- î÷èñòêà ïîëÿ ëîãîâ --//
	DebugMemo->Clear();

	//-- çàãðóçêà ëîãîâ â ïîëå --//
	DebugMemo->Lines->Add( MainForm->engine->GetLogs() );
}


