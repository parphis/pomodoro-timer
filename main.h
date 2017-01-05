//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TTimer *pomodoroTimer;
	TTimer *breakTimer;
	TImage *Image1;
	TPopupMenu *popup;
	TMenuItem *pause;
	TMenuItem *reset;
	TMenuItem *start;
	TMenuItem *endapp;
	TMenuItem *N1;
	TMenuItem *p_timer;
	TMenuItem *b_timer;
	TImage *Image2;
	TMenuItem *re_paint;
	void __fastcall pomodoroTimerTimer(TObject *Sender);
	void __fastcall breakTimerTimer(TObject *Sender);
	void __fastcall pauseClick(TObject *Sender);
	void __fastcall resetClick(TObject *Sender);
	void __fastcall startClick(TObject *Sender);
	void __fastcall p_timerClick(TObject *Sender);
	void __fastcall b_timerClick(TObject *Sender);
	void __fastcall endappClick(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall re_paintClick(TObject *Sender);
private:	// User declarations
	int counter;
	int pomodoro_limit;
	int break_limit;
	int pomodoro_timer_tick; //in seconds
	int break_timer_tick; //in seconds
	int draw_period; //in seconds
	int position_counter;
	bool pomodoro_state;
	bool break_state;
	enum timers {
		pomodoro=0,
		brk=1
	} t;
	void __fastcall WndProc(Messages::TMessage& Message);
	void __fastcall Init(int w, int h, TColor c, bool i, bool p, bool b);
	bool __fastcall modifyTimerValue(timers what);
	void __fastcall Redraw();
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
