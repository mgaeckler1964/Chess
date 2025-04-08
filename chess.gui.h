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

	const int BishopBtn_id=133;
	const int ChessFORM_id=128;
	const int ControlCHILD_id=138;
	const int DepthEdt_id=129;
	const int EvalLABEL_id=131;
	const int KnightBtn_id=134;
	const int PromotionList_id=137;
	const int QueenBtn_id=136;
	const int RestartBtn_id=130;
	const int RookBtn_id=135;
	const int TurnBtn_id=132;

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
		winlib::PushButton *RestartBtn;
		winlib::Label *EvalLABEL;
		winlib::PushButton *TurnBtn;
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
