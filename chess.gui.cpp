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
"<form name=\"ChessFORM\" style=\"277807104\" width=\"694\" height=\"375\" caption=\"Chess\" id=\"128\" baseClass=\"OverlappedWindow\" bgColor=\"COLOR_WINDOW \" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layoutManager type=\"AttachmentManager\" />\n"
"</form>\n"
"</forms>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return doc;
	}


	void ChessFORM_form::getControls() {
	}	// ChessFORM
}	// namespace winlibGUI
