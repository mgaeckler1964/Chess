/*
	this file was created from C:\CRESD\Source\chess\chess.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/
#ifndef C__CRESD_SOURCE_CHESS_CHESS_GUI_H
#define C__CRESD_SOURCE_CHESS_CHESS_GUI_H
#include <winlib/popup.h>
#include <winlib/frame.h>
#include <winlib/scrollFrame.h>
#include <winlib/ControlW.h>
#include <winlib/xmlEditorChild.h>
#include <winlib/gridView.h>

#include <winlib/winApp.h>

namespace winlibGUI {

	const int BishopBtn_id=136;
	const int BlackClk_id=132;
	const int ChessFORM_id=128;
	const int ControlCHILD_id=141;
	const int DepthEdt_id=129;
	const int EvalLABEL_id=130;
	const int KnightBtn_id=137;
	const int PromotionList_id=140;
	const int QueenBtn_id=139;
	const int RestartBtn_id=133;
	const int RookBtn_id=138;
	const int StopBtn_id=135;
	const int TurnBtn_id=134;
	const int WhiteClk_id=131;

	class GuiApplication : public winlib::Application {
		public:
		virtual gak::xml::Document *getGuiDoc( void );
		GuiApplication(int iconID=-1) : winlib::Application(iconID) {}
	};

	class ChessFORM_form : public winlib::OverlappedWindow {
		public:
		ChessFORM_form(winlib::BasicWindow *owner) : OverlappedWindow(owner) {}
		winlib::SuccessCode create(winlib::BasicWindow*parent) {
			return OverlappedWindow::create(parent,"ChessFORM");
		}

		winlib::EditControl *DepthEdt;
		winlib::Label *EvalLABEL;
		winlib::DateTimePicker *WhiteClk;
		winlib::DateTimePicker *BlackClk;
		winlib::PushButton *RestartBtn;
		winlib::PushButton *TurnBtn;
		winlib::PushButton *StopBtn;
		winlib::RadioButton *BishopBtn;
		winlib::RadioButton *KnightBtn;
		winlib::RadioButton *RookBtn;
		winlib::RadioButton *QueenBtn;
		winlib::FrameChild *PromotionList;
		winlib::FrameChild *ControlCHILD;
		private:
		virtual void getControls();
	};	// end of ChessFORM
}	// namespace winlibGUI

#endif // C__CRESD_SOURCE_CHESS_CHESS_GUI_H
