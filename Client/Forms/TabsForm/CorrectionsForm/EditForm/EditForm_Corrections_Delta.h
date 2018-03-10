//---------------------------------------------------------------------------

#ifndef EditForm_Corrections_DeltaH
#define EditForm_Corrections_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TEditFormCorrections : public TForm
{
__published:
	TListBox *CurrInListBox;
	TListBox *CurrOutListBox;
	TListBox *SourceListBox;
	TButton *SaveButton;
	TStaticText *SourceIDStatic;
	TStaticText *CurrOutStatic;
	TStaticText *CurrInStatic;
	TStaticText *FeeStatic;
	TStaticText *StaticText5;
	TStaticText *NotesStatic;
	TCheckBox *EnabledCheck;
	TEdit *FeeEdit;
	TEdit *NotesEdit;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SaveButtonClick(TObject *Sender);

private:


public:

	__fastcall TEditFormCorrections(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TEditFormCorrections *EditFormCorrections;
//---------------------------------------------------------------------------
#endif
