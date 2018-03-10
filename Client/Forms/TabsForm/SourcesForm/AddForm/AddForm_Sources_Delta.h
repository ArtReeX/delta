//---------------------------------------------------------------------------

#ifndef AddForm_Sources_DeltaH
#define AddForm_Sources_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TAddFormSources : public TForm
{
__published:

	TButton *AddButton;
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
	void __fastcall AddButton_OneClick(TObject *Sender);

private:


public:

	__fastcall TAddFormSources(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAddFormSources *AddFormSources;
//---------------------------------------------------------------------------
#endif
