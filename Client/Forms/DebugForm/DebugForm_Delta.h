//---------------------------------------------------------------------------

#ifndef DebugForm_DeltaH
#define DebugForm_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TDebugForm : public TForm
{
__published:
	TMemo *DebugMemo;
	TImage *DebugImage;
	TStaticText *DebugStatic;
	void __fastcall FormShow(TObject *Sender);

private:


public:

	__fastcall TDebugForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TDebugForm *DebugForm;
//---------------------------------------------------------------------------
#endif
