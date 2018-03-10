//---------------------------------------------------------------------------

#ifndef AddForm_Corrections_DeltaH
#define AddForm_Corrections_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.CheckLst.hpp>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TAddFormCorrections : public TForm
{
__published:
	TEdit *NotesEdit;
	TEdit *FeeEdit;
	TCheckBox *EnabledCheck;
	TStaticText *NotesStatic;
	TStaticText *StaticText5;
	TStaticText *FeeStatic;
	TStaticText *CurrInStatic;
	TStaticText *CurrOutStatic;
	TStaticText *SourceIDStatic;
	TButton *AddButton;
	TListBox *SourceListBox;
	TListBox *CurrOutListBox;
	TListBox *CurrInListBox;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall AddButton_OneClick(TObject *Sender);

private:


public:

	__fastcall TAddFormCorrections(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAddFormCorrections *AddFormCorrections;
//---------------------------------------------------------------------------
#endif
