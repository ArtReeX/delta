//---------------------------------------------------------------------------

#ifndef AddForm_Currencys_DeltaH
#define AddForm_Currencys_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TAddFormCurrencys : public TForm
{
__published:

	TButton *AddButton;
	TStaticText *NameStatic;
	TStaticText *ShortStatic;
	TStaticText *FeeStatic;
	TStaticText *GetterStatic;
	TStaticText *StaticText5;
	TStaticText *NotesStatic;
	TCheckBox *EnabledCheck;
	TEdit *NameEdit;
	TEdit *ShortEdit;
	TEdit *FeeEdit;
	TEdit *MinSumEdit;
	TEdit *NotesEdit;
	TStaticText *BaseStatic;
	TCheckBox *BaseCheck;
	void __fastcall AddButton_OneClick(TObject *Sender);

private:


public:

	__fastcall TAddFormCurrencys(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAddFormCurrencys *AddFormCurrencys;
//---------------------------------------------------------------------------
#endif
