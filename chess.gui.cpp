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
"<child type=\"FrameChild\" name=\"LeftCHILD\" caption=\"\" x=\"50\" y=\"91\" width=\"280\" height=\"25\" style=\"1342308352\" id=\"131\">\n"
"<layout attachment=\"0\" growHeight=\"2\" x=\"0\" y=\"0\" />\n"
"<child type=\"Label\" name=\"LABEL\" caption=\"Tiefe:\" x=\"18\" y=\"29\" width=\"0\" height=\"0\" style=\"1342242827\" id=\"129\" />\n"
"<child type=\"EditControl\" name=\"DepthCONTROL\" caption=\"\" x=\"48\" y=\"24\" width=\"80\" height=\"24\" style=\"1350631808\" id=\"130\" />\n"
"</child>\n"
"</form>\n"
"</forms>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return doc;
	}


	void ChessFORM_form::getControls() {
		LABEL=static_cast<winlib::Label*>(findChild(LABEL_id));
		DepthCONTROL=static_cast<winlib::EditControl*>(findChild(DepthCONTROL_id));
		LeftCHILD=static_cast<winlib::FrameChild*>(findChild(LeftCHILD_id));
	}	// ChessFORM
}	// namespace winlibGUI
