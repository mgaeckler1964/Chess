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
"<form name=\"ChessFORM\" style=\"277807104\" width=\"694\" height=\"763\" caption=\"Chess\" id=\"128\" baseClass=\"OverlappedWindow\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layoutManager type=\"AttachmentManager\" />\n"
"<child type=\"FrameChild\" name=\"ControlCHILD\" caption=\"\" x=\"0\" y=\"0\" width=\"280\" height=\"728\" style=\"1342308352\" id=\"138\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layout attachment=\"0\" growHeight=\"2\" x=\"0\" y=\"0\" />\n"
"<child type=\"Label\" name=\"\" caption=\"Tiefe:\" x=\"8\" y=\"8\" width=\"32\" height=\"16\" style=\"1342242827\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"EditControl\" name=\"DepthEdt\" caption=\"\" x=\"80\" y=\"8\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"129\" />\n"
"<child type=\"PushButton\" name=\"RestartBtn\" caption=\"Neustart\" x=\"8\" y=\"72\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"130\" />\n"
"<child type=\"Label\" name=\"\" caption=\"Bewertung:\" x=\"8\" y=\"40\" width=\"64\" height=\"16\" style=\"1342242827\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"Label\" name=\"EvalLABEL\" caption=\"eval\" x=\"80\" y=\"40\" width=\"192\" height=\"16\" style=\"1342242827\" id=\"131\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"PushButton\" name=\"TurnBtn\" caption=\"Drehen\" x=\"96\" y=\"72\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"132\" />\n"
"<child type=\"FrameChild\" name=\"PromotionList\" caption=\"\" x=\"8\" y=\"128\" width=\"112\" height=\"176\" style=\"1342308352\" id=\"137\">\n"
"<child type=\"RadioButton\" name=\"BishopBtn\" caption=\"L\xE4""ufer\" x=\"16\" y=\"16\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"133\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"RadioButton\" name=\"KnightBtn\" caption=\"Springer\" x=\"16\" y=\"48\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"134\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"RadioButton\" name=\"RookBtn\" caption=\"Turm\" x=\"16\" y=\"88\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"135\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"<child type=\"RadioButton\" name=\"QueenBtn\" caption=\"Dame\" x=\"16\" y=\"128\" width=\"80\" height=\"24\" style=\"1342242825\" id=\"136\" bgColor=\"WHITE_BRUSH\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\" />\n"
"</child>\n"
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
		RestartBtn=static_cast<winlib::PushButton*>(findChild(RestartBtn_id));
		EvalLABEL=static_cast<winlib::Label*>(findChild(EvalLABEL_id));
		TurnBtn=static_cast<winlib::PushButton*>(findChild(TurnBtn_id));
		BishopBtn=static_cast<winlib::RadioButton*>(findChild(BishopBtn_id));
		KnightBtn=static_cast<winlib::RadioButton*>(findChild(KnightBtn_id));
		RookBtn=static_cast<winlib::RadioButton*>(findChild(RookBtn_id));
		QueenBtn=static_cast<winlib::RadioButton*>(findChild(QueenBtn_id));
		PromotionList=static_cast<winlib::FrameChild*>(findChild(PromotionList_id));
		ControlCHILD=static_cast<winlib::FrameChild*>(findChild(ControlCHILD_id));
	}	// ChessFORM
}	// namespace winlibGUI
