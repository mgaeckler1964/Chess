/*
		Project:		Chess
		Module:			chess.cpp
		Description:	Chess 
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2025 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Linz, Austria ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/


// --------------------------------------------------------------------- //
// ----- switches ------------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- includes ------------------------------------------------------ //
// --------------------------------------------------------------------- //

#include <gak/numericString.h>
#include <gak/fmtNumber.h>
#include <gak/chess.h>
#include <gak/shared.h>

#include <WINLIB/WINAPP.H>
#include <WINLIB/AsyncThread.h>

#include "chess_rc.h"
#include "chess.gui.h"

// --------------------------------------------------------------------- //
// ----- imported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module switches ----------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT-
#	pragma option -b
#	pragma option -a4
#	pragma option -pc
#endif

using namespace winlib;
using namespace winlibGUI;

// --------------------------------------------------------------------- //
// ----- constants ----------------------------------------------------- //
// --------------------------------------------------------------------- //

// polygons for the chess figures
// logical points within an chess field

static const int META_HEIGHT=7;
static const int META_WIDTH=4;

static const POINT pawn[] =
{
	{0,0}, {1, 2}, {0,3}, {1,4}, {2,3}, {1,2}, {2,0}, {0,0}
};
static const POINT rook[] =
{
	{0,0}, {0,6}, {1,6}, {1,5}, {2,5}, {2, 6}, {3,6}, {3,0}, {0,0}
};

static const POINT bishop[] =
{
	{0,0}, {1,5}, {2,0}, {0,0}
};

static const POINT knight[] =
{
	{1,0}, {2,4}, {0,3}, {2,5}, {3,5}, {4,0}, {1,0}
};

static const POINT queen[] =
{
	{1,0}, {1,5}, {0,6}, {2,7}, {4,6}, {3,5}, {3,0}, {1,0}
};

static const POINT king[] =
{
	{0,0}, {0,5}, {1,5}, {1,6}, {0,6}, {1,6}, {1,7}, {1,6}, {2,6}, {1,6}, {1,5}, {2,5}, {2,0}, {0,0}
};

// --------------------------------------------------------------------- //
// ----- macros -------------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- type definitions ---------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class definitions --------------------------------------------- //
// --------------------------------------------------------------------- //

class ChessMainWindow;

class EngineThread : public winlib::AsyncThread
{
	gak::chess::Board	&m_board;
	ChessMainWindow		*m_mainWindow;

	public:
	EngineThread(ChessMainWindow *chessWin, gak::chess::Board	&board); 
	void ExecuteTask();
};

class ChessMainWindow : public ChessFORM_form
{
	bool									m_created;
	int										m_leftOffset;
	unsigned								m_squareSize;
	unsigned								m_maxHeight;
	unsigned								m_maxWidth;
	int										m_depth;
	bool									m_swapedDisplay;
	gak::chess::Board						m_board;
	gak::chess::Figure						*m_selected;

	gak::SharedObjectPointer<EngineThread>	m_engineThread;

	// winboard coordinates: left->right/top->bottom (0...7)
	Point mouseToWinBoard( const Point &position )
	{
		Point winPos;

		winPos.x = (position.x-m_leftOffset)/m_squareSize;
		winPos.y = position.y/m_squareSize;

		return winPos;
	}

	// chess coordinates: left->right/bottom->top (a1-h8)
	gak::chess::Position window2Board( const Point &winBoard )
	{
		char chessCol = char(winBoard.x+gak::chess::MIN_COL_LETTER);
		char chessRow = char(gak::chess::NUM_ROWS - winBoard.y);

		if( m_swapedDisplay )
		{
			chessCol = gak::chess::NUM_COLS - chessCol + 1;
			chessRow = gak::chess::NUM_ROWS - chessRow + 1;
		}
		return gak::chess::Position(chessCol, chessRow);
	}

	// winboard coordinates: left->right/top->bottom (0-7)
	Point board2Window( const gak::chess::Position &chessBoard )
	{
		Point winPos;

		winPos.x = chessBoard.col - gak::chess::MIN_COL_LETTER;
		winPos.y = gak::chess::NUM_ROWS - chessBoard.row;

		if( m_swapedDisplay )
		{
			winPos.x = gak::chess::NUM_COLS - winPos.x - 1;
			winPos.y = gak::chess::NUM_ROWS - winPos.y - 1;
		}

		return winPos;
	}

	Point window2Pixed( const Point &input )
	{
		Point result;

		result.x = input.x * m_squareSize;
		result.y = input.y * m_squareSize;

		return result;
	}

	RectBorder board2RectBorder( const gak::chess::Position &chessBoardPos )
	{
		RectBorder rect;
		Point		winPos = board2Window( chessBoardPos );
		winPos = window2Pixed(winPos);

		rect.left = m_leftOffset + winPos.x;
		rect.top = winPos.y;
		rect.right = m_leftOffset + winPos.x+m_squareSize;
		rect.bottom = winPos.y+m_squareSize;

		return rect;
	}

	gak::chess::Figure::Type getPromotion() const
	{
		if( !PromotionList->ForeignWindow::isVisible() )
			return gak::chess::Figure::ftNone;
		if( BishopBtn->isActive() )
			return gak::chess::Figure::ftBishop;
		if( KnightBtn->isActive() )
			return gak::chess::Figure::ftKnight;
		if( RookBtn->isActive() )
			return gak::chess::Figure::ftRook;
		if( QueenBtn->isActive() )
			return gak::chess::Figure::ftQueen;

		return gak::chess::Figure::ftNone;
	}
	void unselect()
	{
		m_selected = NULL;
		PromotionList->hide();
	}
	void postMove()
	{
		unselect();
		displayEval();
		makeNextComputerMove();
	}

	void makeNextComputerMove();
	void displayClock();
	void displayHistory();
	void displayEval();
	void drawFigure( Device &hDC, Point logWindowsPos, int xFactor, int yFactor, const POINT *points, size_t numPoints );

	virtual ProcessStatus handleCreate( void );
	virtual ProcessStatus handleEditChange( int control );
	virtual ProcessStatus handleButtonClick( int control );
	virtual ProcessStatus handleLeftButton( LeftButton leftButton, WPARAM modifier, const Point &position );
	virtual ProcessStatus handleResize( const Size &newSize );
	virtual ProcessStatus handleRepaint( Device &hDC );
	virtual void handleTimer( void );
	virtual void handleAsyncTaskEnd( void * /*data*/ );

public:
	ChessMainWindow();
	int getDepth() const
	{
		return m_depth;
	}
};

class WindowsApplication : public GuiApplication
{
	virtual bool 	startApplication( HINSTANCE /*hInstance*/, const char * /*cmdLine*/ )
	{
		doEnableLogEx(gakLogging::llInfo);
		doDisableLog();
		setApplication("chess");
		setComapny("gak");
		return 0;
	}
	virtual CallbackWindow  *createMainWindow( const char * /*cmdLine*/, int /*nCmdShow*/ )
	{
		ChessMainWindow	*mainWindow = new ChessMainWindow;
		if( mainWindow->create( NULL ) == scERROR )
		{
			MessageBox( NULL, "Could not create window", "Error", MB_ICONERROR );
			delete mainWindow;
			mainWindow = NULL;
		}
		mainWindow->focus();

		return mainWindow;
	}
	virtual void deleteMainWindow( BasicWindow  *mainWindow )
	{
		delete mainWindow;
	}

	public:
	WindowsApplication() : GuiApplication( IDI_CHESS ) {}
};

// --------------------------------------------------------------------- //
// ----- exported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module static data -------------------------------------------- //
// --------------------------------------------------------------------- //

static WindowsApplication	app;

// --------------------------------------------------------------------- //
// ----- class static data --------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- prototypes ---------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module functions ---------------------------------------------- //
// --------------------------------------------------------------------- //

static STRING getChessPath()
{
	static STRING s_thePath;

	if( s_thePath.isEmpty() )
	{
		s_thePath = getenv("TMP");
		if( s_thePath.isEmpty() )
		{
			s_thePath = getenv("TEMP");
		}
		s_thePath.condAppend( DIRECTORY_DELIMITER );
	}
	return s_thePath;
}

static STRING getBaseChessFile()
{
	static STRING s_thePath;

	if( s_thePath.isEmpty() )
	{
		s_thePath = getChessPath() + "chess";
	}
	return s_thePath;
}

static STRING getChessFile()
{
	static STRING s_thePath;

	if( s_thePath.isEmpty() )
	{
		s_thePath = getBaseChessFile() + ".txt";
	}
	return s_thePath;
}

static STRING getNumberedChessFile()
{
	static size_t number = 0;
	STRING thePath = getBaseChessFile() + gak::formatNumber( ++number ) + ".txt";

	return thePath;
}

// --------------------------------------------------------------------- //
// ----- class inlines ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class constructors/destructors -------------------------------- //
// --------------------------------------------------------------------- //

inline EngineThread::EngineThread(ChessMainWindow *chessWin, gak::chess::Board	&board) 
	: m_board(board), m_mainWindow(chessWin), winlib::AsyncThread(chessWin, &board) 
{
}

ChessMainWindow::ChessMainWindow() : ChessFORM_form( NULL ), m_created(false), m_leftOffset(280), m_squareSize(0), m_swapedDisplay(false), m_selected(NULL), m_depth(1)
{
	STRING chessFile = getChessFile();
	STRING strChess;
		
	if( gak::exists(chessFile) )
	{
		strChess.readFromFile(chessFile);
	}
	if( strChess.isEmpty() )
	{
		m_board.reset();
	}
	else
	{
		m_board.generateFromString(strChess);
	}
}

// --------------------------------------------------------------------- //
// ----- class static functions ---------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class privates ------------------------------------------------ //
// --------------------------------------------------------------------- //

void ChessMainWindow::drawFigure( Device &hDC, Point logWindowsPos, int xFactor, int yFactor, const POINT *points, size_t numPoints  )
{
	Point windowsPos = window2Pixed( logWindowsPos );

	int x = windowsPos.x;
	int y = windowsPos.y;

	int minX = m_squareSize;
	int maxX = 0;
	gak::PODarray<Point>	figure;
	figure.createElements(numPoints);
	for( size_t i=0; i<numPoints; ++i )
	{
		int px = points[i].x *xFactor;
		int py = points[i].y *yFactor;
		figure[i].x = m_leftOffset + x + px;
		figure[i].y = y + m_squareSize - py;

		minX = gak::math::min(minX, px );
		maxX = gak::math::max(maxX, px );
	}
	if( minX || maxX != int(m_squareSize) )
	{
		int avg = (minX + m_squareSize-maxX)/2;
		int offset = minX-avg;
		if( offset )
		{
			for( size_t i=0; i<numPoints; ++i )
			{
				figure[i].x -= offset;
			}
		}
	}
	hDC.polygon(figure);
}

void ChessMainWindow::makeNextComputerMove()
{
	m_engineThread = new EngineThread(this,m_board);
	m_engineThread->StartThread();
	StopBtn->enable();
}

void ChessMainWindow::displayClock()
{
	WhiteClk->setStopWatch(m_board.getWhiteClock());
	BlackClk->setStopWatch(m_board.getBlackClock());
}

void ChessMainWindow::displayHistory()
{
	const gak::chess::Movements &moves = m_board.getHistory();
	int shown = MovesBOX->getTag();
	for( int i=shown+1; i<moves.size(); ++i )
	{
		const gak::chess::Movement &move = moves[i];
		STRING moveStr = move.toString();
		if(move.fig->m_color == gak::chess::Figure::White || !i )
		{
			STRING listStr = gak::formatNumber(i/2+1) + ". ";
			if( move.fig->m_color == gak::chess::Figure::Black )
			{
				listStr += "..., ";
			}
			listStr += moveStr;
			MovesBOX->addEntry(listStr);
			MovesBOX->setTag( i );
		}
		else
		{
			STRING last = MovesBOX->getEntry( i/2 );
			last += ", ";
			last+= moveStr;
			MovesBOX->replaceEntry(i/2, last);
			MovesBOX->setTag( i );
		}
		MovesBOX->showLast();
	}
}

void ChessMainWindow::displayEval()
{
	STRING stateStr = m_board.getStateString();
	if( m_board.canPlay() )
	{
		stateStr = gak::formatNumber( m_board.evaluate() ) + STRING(' ') + stateStr;
	}
	EvalLABEL->setText( stateStr );

	displayHistory();
}

// --------------------------------------------------------------------- //
// ----- class protected ----------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class virtuals ------------------------------------------------ //
// --------------------------------------------------------------------- //
   
void EngineThread::ExecuteTask()
{
	static int count=0;
	int qual;
	gak::chess::Movement next = m_board.findBest(m_mainWindow->getDepth(),&qual);
	if( qual )
	{
		m_board.performMove( next );
		STRING strChess = m_board.generateString()+ (m_board.isWhiteTurn() ? 'W' : 'S');
		strChess.writeToFile(getChessFile());
		strChess.writeToFile(getNumberedChessFile());
	}
}

ProcessStatus ChessMainWindow::handleCreate( void )
{
	m_leftOffset = ControlCHILD->getClientRectangle().getWidth();

	MovesBOX->setTag( -1 );
	PromotionList->hide();
	STRING depth = gak::formatNumber(m_depth);
	DepthEdt->setText(depth);
	StopBtn->disable();
	displayEval();
	setTimer(1000);

	m_depth = app.GetProfile( "", "depth", 1 );
	DepthEdt->setText( gak::formatNumber(m_depth) );

	m_created = true;
	return psDO_DEFAULT;
}

ProcessStatus ChessMainWindow::handleEditChange( int control )
{
	switch( control )
	{
		case DepthEdt_id:
		{
			if( m_created )
			{
				STRING text = DepthEdt->getText();
				m_depth = gak::getValueN<int>(text);
				app.WriteProfile( false, "", "depth", m_depth );
			}

		}
	}
	return ChessFORM_form::handleEditChange( control );
}

ProcessStatus ChessMainWindow::handleButtonClick( int buttonID )
{
	switch( buttonID )
	{
		case RestartBtn_id:
		{
			if( !m_engineThread )
			{
				m_board.reset();
				MovesBOX->setTag( -1 );
				MovesBOX->clearEntries();
				displayEval();
				invalidateWindow();
			}
			break;
		}
		case TurnBtn_id:
			if( !m_engineThread )
			{
				m_swapedDisplay = !m_swapedDisplay;
				makeNextComputerMove();
				invalidateWindow();
			}
			break;
		case StopBtn_id:
			if( m_engineThread )
			{
				m_engineThread->StopThread();
			}
		default:
			return ChessFORM_form::handleButtonClick( buttonID );
	}
	return psPROCESSED;
}

ProcessStatus ChessMainWindow::handleLeftButton( LeftButton leftButton, WPARAM /* modifier */, const Point &position )
{
	if( !m_engineThread && leftButton == lbUP )
	{
		Point winPos = mouseToWinBoard(position);
		if( winPos.x < gak::chess::NUM_COLS && winPos.y < gak::chess::NUM_ROWS )
		{
			gak::chess::Position chessPos = window2Board( winPos );

			if( !m_selected )
			{
				m_selected = m_board.getFigure(chessPos);
				if( m_selected )
				{
					if( m_selected->m_color != m_board.getNextColor() )
					{
						unselect();
					}
					else if( m_selected->canPromote() )
					{
						PromotionList->show();
					}
				}
			}
			else
			{
				gak::chess::Figure::Type newType = getPromotion();
				if( !m_board.checkMoveTo(m_selected, chessPos, newType) )
				{
					gak::chess::King *king = dynamic_cast<gak::chess::King*>(m_selected);
					const gak::chess::King::Rochade *rochade = king ? king->getRochade(chessPos) : NULL;
					if( rochade )
					{
						m_board.rochade(m_selected,rochade->rook,chessPos,rochade->rookTarget);
						postMove();
					}
					else if( PromotionList->ForeignWindow::isVisible() )
					{
						if( newType )
						{
							m_board.promote(m_selected, newType, chessPos);
							postMove();
						}
					}
					else
					{
						m_board.moveTo(m_selected, chessPos );
						postMove();
					}

				}
				else if(m_selected->getPos() != chessPos)
				{
					unselect();
				}
			}

			invalidateWindow();
			return psPROCESSED;
		}
	}

	return psDO_DEFAULT;
}

ProcessStatus ChessMainWindow::handleResize( const Size &newSize )
{
	int squareWidth = (newSize.width-m_leftOffset) / gak::chess::NUM_COLS;
	int squareHeight = newSize.height / gak::chess::NUM_ROWS;
	m_squareSize = gak::math::min(squareWidth, squareHeight);
	m_maxHeight = m_squareSize * gak::chess::NUM_ROWS;
	m_maxWidth = m_squareSize * gak::chess::NUM_COLS;

	invalidateWindow();
	return psPROCESSED;
}

ProcessStatus ChessMainWindow::handleRepaint( Device &hDC )
{
	Pen	blackPen = Pen().setColor(0,0,0).setWidth(1);
	Pen	selFramePen = Pen().setColor(0,0,0xFF).setWidth(3);
	Pen	targetFramePen = Pen().setColor(0,0xFF,0).setWidth(3);

	Brush whiteField, blackField, frameBrush;
	whiteField.create( 240, 239, 216 );
	blackField.create( 212, 187, 4 );
	frameBrush.selectBrush(Brush::sbNull);

	Brush whiteFigs, blackFigs;
	whiteFigs.create( 190, 178, 118 );
	blackFigs.create( 110, 47, 47 );

	hDC.selectPen(blackPen);
	bool paintWhite=true;
	for( int i=0; i<gak::chess::NUM_COLS; ++i )
	{
		int left = m_leftOffset + i*m_squareSize;
		for( int j=0; j<gak::chess::NUM_ROWS; ++j )
		{
			if( j )
			{
				paintWhite = !paintWhite;
			}
			hDC.selectBrush( paintWhite ? whiteField : blackField );
			int top = j*m_squareSize;
			hDC.rectangle(left,top,left+m_squareSize,top+m_squareSize);
		}
	}

	for( int i=1, y=m_squareSize; i<= gak::chess::NUM_ROWS; ++i, y += m_squareSize )
	{
		hDC.moveTo(m_leftOffset,y);
		hDC.lineTo( m_maxWidth, y );
	}
	for( int i=1, x=m_leftOffset + m_squareSize; i<= gak::chess::NUM_COLS; ++i, x += m_squareSize )
	{
		hDC.moveTo(x,0);
		hDC.lineTo( x, m_maxHeight );
	}

	for( size_t i = 0; i<gak::chess::NUM_FIELDS; ++i )
	{
		gak::chess::Figure *fig = m_board.getFigure(i);
		if( fig )
		{
			if( fig->m_color == gak::chess::Figure::White )
			{
				hDC.selectPen( blackPen );
				hDC.selectBrush( whiteFigs );
			}
			else
			{
				hDC.selectPen( blackPen );
				hDC.selectBrush( blackFigs );
			}
			Point winPos = board2Window( fig->getPos() );

			switch( fig->getType() )
			{
			case gak::chess::Figure::ftPawn:
				drawFigure(hDC, winPos, m_squareSize/META_WIDTH, m_squareSize/META_HEIGHT, pawn, arraySize(pawn));
				break;
			case gak::chess::Figure::ftKnight:
				drawFigure(hDC, winPos, m_squareSize/META_WIDTH, m_squareSize/META_HEIGHT, knight, arraySize(knight));
				break;
			case gak::chess::Figure::ftBishop:
				drawFigure(hDC, winPos, m_squareSize/META_WIDTH, m_squareSize/META_HEIGHT, bishop, arraySize(bishop));
				break;
			case gak::chess::Figure::ftRook:
				drawFigure(hDC, winPos, m_squareSize/META_WIDTH, m_squareSize/META_HEIGHT, rook, arraySize(rook));
				break;
			case gak::chess::Figure::ftQueen:
				drawFigure(hDC, winPos, m_squareSize/META_WIDTH, m_squareSize/META_HEIGHT, queen, arraySize(queen));
				break;
			case gak::chess::Figure::ftKing:
				drawFigure(hDC, winPos, m_squareSize/META_WIDTH, m_squareSize/META_HEIGHT, king, arraySize(king));
				break;
			}
		}
	}

	if(m_selected)
	{
		const gak::chess::Position &pos = m_selected->getPos();

		RectBorder rect = board2RectBorder( pos );

		hDC.selectBrush(frameBrush);
		hDC.selectPen(selFramePen);
		hDC.rectangle( rect );

		const gak::chess::PotentialDestinations &pot = m_selected->getPossible();

		hDC.selectPen(targetFramePen);

		for( size_t i=0; i<pot.numTargets; ++i )
		{
			rect = board2RectBorder( pot.targets[i].getTarget() );
			hDC.rectangle( rect );
		}
	}
	return psPROCESSED;
}

void ChessMainWindow::handleTimer( void )
{
	displayClock();
}

void ChessMainWindow::handleAsyncTaskEnd( void * /*data*/ )
{
	displayEval();
	m_engineThread = NULL;
	StopBtn->disable();
	invalidateWindow();
}

// --------------------------------------------------------------------- //
// ----- class publics ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- entry points -------------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT.
#	pragma option -b.
#	pragma option -a.
#	pragma option -p.
#endif

