//---------------------------------------------------------------------------

#ifndef AuthForm_DeltaH
#define AuthForm_DeltaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Graphics.hpp>

#include "MainForm_Delta.h"

//---------------------------------------------------------------------------
class TAuthForm : public TForm
{
__published:

	TImage *AuthImage;
	TButton *AuthButton;
	TStaticText *LoginStatic;
	TStaticText *PasswordStatic;
	TEdit *LoginEdit;
	TEdit *PasswordEdit;
	void __fastcall AuthButton_OneClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:


public:

	__fastcall TAuthForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAuthForm *AuthForm;
//---------------------------------------------------------------------------
#endif
