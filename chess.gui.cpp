/*
	this file was created from C:\CRESD\Source\chess\chess.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/

#include "C:\CRESD\Source\chess\chess.gui.h"

namespace winlibGUI {

	gak::xml::Document *GuiApplication::getGuiDoc() {
		gak::xml::Document *doc = winlib::Application::getGuiDoc();
		if(!doc) {
			gak::STRING xmlSrc = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
"<gui>\n"
"<forms>\n"
"<form name=\"ChessFORM\" style=\"277807104\" width=\"758\" height=\"491\" caption=\"Chess\" id=\"128\" baseClass=\"OverlappedWindow\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layoutManager type=\"AttachmentManager\" />\n"
"<child type=\"FrameChild\" name=\"ControlCHILD\" caption=\"\" x=\"0\" y=\"0\" width=\"280\" height=\"728\" style=\"1342308352\" id=\"142\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout attachment=\"0\" growHeight=\"2\" x=\"0\" y=\"0\" />\n"
"<child type=\"Label\" name=\"\" caption=\"Tiefe:\" x=\"8\" y=\"8\" width=\"32\" height=\"16\" style=\"1342242827\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"EditControl\" name=\"DepthEdt\" caption=\"\" x=\"80\" y=\"8\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"129\" />\n"
"<child type=\"Label\" name=\"\" caption=\"Bewertung:\" x=\"8\" y=\"40\" width=\"64\" height=\"16\" style=\"1342242827\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"Label\" name=\"EvalLABEL\" caption=\"eval\" x=\"80\" y=\"40\" width=\"192\" height=\"16\" style=\"1342242827\" id=\"130\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"DateTimePicker\" name=\"WhiteClk\" caption=\"\" x=\"8\" y=\"64\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"131\" />\n"
"<child type=\"DateTimePicker\" name=\"BlackClk\" caption=\"\" x=\"96\" y=\"64\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"132\" />\n"
"<child type=\"PushButton\" name=\"RestartBtn\" caption=\"Neustart\" x=\"8\" y=\"96\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"133\" />\n"
"<child type=\"PushButton\" name=\"TurnBtn\" caption=\"Drehen\" x=\"96\" y=\"96\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"134\" />\n"
"<child type=\"PushButton\" name=\"StopBtn\" caption=\"Stop\" x=\"184\" y=\"96\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"135\" />\n"
"<child type=\"FrameChild\" name=\"PromotionList\" caption=\"\" x=\"8\" y=\"136\" width=\"112\" height=\"176\" style=\"1073872896\" id=\"140\">\n"
"<child type=\"RadioButton\" name=\"BishopBtn\" caption=\"L\xE4""ufer\" x=\"16\" y=\"16\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"136\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"RadioButton\" name=\"KnightBtn\" caption=\"Springer\" x=\"16\" y=\"48\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"137\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"RadioButton\" name=\"RookBtn\" caption=\"Turm\" x=\"16\" y=\"88\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"138\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"RadioButton\" name=\"QueenBtn\" caption=\"Dame\" x=\"16\" y=\"128\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"139\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"</child>\n"
"<child type=\"ListBox\" name=\"MovesBOX\" caption=\"\" x=\"128\" y=\"136\" width=\"152\" height=\"300\" style=\"1353777409\" id=\"141\" />\n"
"</child>\n"
"</form>\n"
"</forms>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return doc;
	}


	void ChessFORM_form::getControls() {
		DepthEdt=static_cast<winlib::EditControl*>(findChild(DepthEdt_id));
		EvalLABEL=static_cast<winlib::Label*>(findChild(EvalLABEL_id));
		WhiteClk=static_cast<winlib::DateTimePicker*>(findChild(WhiteClk_id));
		BlackClk=static_cast<winlib::DateTimePicker*>(findChild(BlackClk_id));
		RestartBtn=static_cast<winlib::PushButton*>(findChild(RestartBtn_id));
		TurnBtn=static_cast<winlib::PushButton*>(findChild(TurnBtn_id));
		StopBtn=static_cast<winlib::PushButton*>(findChild(StopBtn_id));
		BishopBtn=static_cast<winlib::RadioButton*>(findChild(BishopBtn_id));
		KnightBtn=static_cast<winlib::RadioButton*>(findChild(KnightBtn_id));
		RookBtn=static_cast<winlib::RadioButton*>(findChild(RookBtn_id));
		QueenBtn=static_cast<winlib::RadioButton*>(findChild(QueenBtn_id));
		PromotionList=static_cast<winlib::FrameChild*>(findChild(PromotionList_id));
		MovesBOX=static_cast<winlib::ListBox*>(findChild(MovesBOX_id));
		ControlCHILD=static_cast<winlib::FrameChild*>(findChild(ControlCHILD_id));
	}	// ChessFORM
}	// namespace winlibGUI
