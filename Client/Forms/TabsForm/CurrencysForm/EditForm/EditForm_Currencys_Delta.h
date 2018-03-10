//---------------------------------------------------------------------------

#ifndef EditForm_Currencys_DeltaH
#define EditForm_Currencys_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "MainForm_Delta.h"

//-- подключение типа идентификаторов --//
#include <MapsID.h>


//---------------------------------------------------------------------------
class TEditFormCurrencys : public TForm
{
__published:

	TButton *SaveButton;
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
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SaveButton_OneClick(TObject *Sender);

private:


public:

	__fastcall TEditFormCurrencys(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TEditFormCurrencys *EditFormCurrencys;
//---------------------------------------------------------------------------
#endif
