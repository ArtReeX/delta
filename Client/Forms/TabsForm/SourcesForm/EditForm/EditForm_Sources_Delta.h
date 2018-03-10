//---------------------------------------------------------------------------

#ifndef EditForm_Sources_DeltaH
#define EditForm_Sources_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

//-- подключение типа идентификаторов --//
#include <MapsID.h>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TEditFormSources : public TForm
{
__published:

	TButton *SaveButton;
	TStaticText *NameStatic;
	TStaticText *UrlStatic;
	TStaticText *DataUrlStatic;
	TStaticText *GetterStatic;
	TStaticText *StaticText5;
	TStaticText *NotesStatic;
	TCheckBox *EnabledCheck;
	TEdit *NameEdit;
	TEdit *UrlEdit;
	TEdit *DataUrlEdit;
	TEdit *GetterEdit;
	TEdit *NotesEdit;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SaveButton_OneClick(TObject *Sender);

private:


public:

	__fastcall TEditFormSources(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TEditFormSources *EditFormSources;
//---------------------------------------------------------------------------
#endif
