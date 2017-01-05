//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner), counter(0), pomodoro_limit(1500), break_limit(600),
	pomodoro_timer_tick(1), break_timer_tick(1), draw_period(60),
	position_counter(0), pomodoro_state(true), break_state(false)
{
	this->Height = 10;
	this->Width = 300;
	pomodoroTimer->Interval = this->pomodoro_timer_tick*1000;
	breakTimer->Interval = this->break_timer_tick*1000;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::WndProc(Messages::TMessage& Message) {
    TForm::WndProc(Message); // Inherited implementation
    if (Message.Msg == WM_NCHITTEST) {
        TWMNCHitTest& oMsg = reinterpret_cast<TWMNCHitTest&>(Message);
        TPoint oPoint(oMsg.XPos, oMsg.YPos); // Screen coordinates
        oPoint = ScreenToClient(oPoint); // Now in form-local coordinates
        // It's in the title bar (caption) if it's in a rectangle at the top of the form
		if ((oPoint.x > 0 && oPoint.x < 16) &&
			(oPoint.y > 0 && oPoint.y < 12))
        {
            oMsg.Result = HTCAPTION;
        }
    }
}
void __fastcall TfrmMain::pomodoroTimerTimer(TObject *Sender)
{
	//this->Repaint();
	if(this->counter >= this->pomodoro_limit) {
		this->Init(16, 24, clYellow, true, false, true);
	}
	else {
		if( (this->counter%this->draw_period)==0 ) {
			this->Canvas->Brush->Color = clBlack;
			this->Canvas->Pen->Color = clWhite;
			TRect r;
			for (int i=0; i <= this->position_counter; i++) {
            	r.init((10*i), 0, (10*i)+10, 10);
				this->Canvas->Rectangle(r);
			}
			this->position_counter += 1;
		}
		this->counter += 1;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::breakTimerTimer(TObject *Sender)
{
	if(this->counter >= this->break_limit) {
		this->Init(300, 10, clWhite, false, true, false);
	}
	else {
		if(Image1->Visible) {
			this->counter += 1;
		}
		Image1->Visible ^= true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pauseClick(TObject *Sender)
{
	this->pomodoro_state = pomodoroTimer->Enabled;
	this->break_state = breakTimer->Enabled;
	breakTimer->Enabled = false;
	pomodoroTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::resetClick(TObject *Sender)
{
	this->Init(300, 10, clWhite, false, true, false);
	this->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::startClick(TObject *Sender)
{
	breakTimer->Enabled = this->break_state;
	pomodoroTimer->Enabled = this->pomodoro_state;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Init(int w, int h, TColor c, bool i, bool p, bool b)
{
    this->Repaint();
	Image1->Visible = i;
	this->Color = c;
	this->Height = h;
	this->Width = w;
	this->counter = 0;
	this->position_counter = 0;
	breakTimer->Enabled = b;
	pomodoroTimer->Enabled = p;
	this->pomodoro_state = pomodoroTimer->Enabled;
	this->break_state = breakTimer->Enabled;
}
bool __fastcall TfrmMain::modifyTimerValue(timers what)
{
	int tmp;

	if(what==pomodoro) {
		try {
			tmp = StrToInt(InputBox("pomodoro Timer Interval",
				"pomodoro timer interval change in seconds",
				IntToStr(this->pomodoro_limit)));
			if(tmp==this->pomodoro_limit) return false;
			if(tmp>0) {
				this->pomodoro_limit = tmp;
			}
			else {
				ShowMessage("Please enter a number bigger than 0!");
			}
		} catch (...) {
			ShowMessage("Please enter a valid number!");
		}
	}
	if(what==brk) {
		try {
			tmp = StrToInt(InputBox("Break Timer Interval",
				"Break timer interval change in seconds",
				IntToStr(this->break_limit)));
			if(tmp==this->break_limit) return false;
			if(tmp>0) {
				this->break_limit = tmp;
			}
			else {
				ShowMessage("Please enter a number bigger than 0!");
			}
		} catch (...) {
			ShowMessage("Please enter a valid number!");
		}
	}
	return true;
}
void __fastcall TfrmMain::p_timerClick(TObject *Sender)
{
	if(modifyTimerValue(pomodoro))
		this->Init(300, 10, clWhite, false, true, false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::b_timerClick(TObject *Sender)
{
	if(modifyTimerValue(brk))
		this->Init(300, 10, clWhite, false, true, false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::endappClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormPaint(TObject *Sender)
{
	this->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::re_paintClick(TObject *Sender)
{
	this->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Redraw()
{
	TRect r;
	for (int i=0; i < this->position_counter; i++) {
		r.init((10*i), 0, (10*i)+10, 10);
		this->Canvas->Rectangle(r);
	}
}

