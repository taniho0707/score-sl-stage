#include "ScoreDrawing.h"

ScoreDrawing::ScoreDrawing(QQuickItem *parent)
	: QQuickPaintedItem(parent),
	  m_width(300),
	  m_height(500),
	  page(100, 4, 0)
{
	pages.reserve(100);
	for(auto itr = pages.begin(); itr != pages.end(); ++itr) {
		(*itr).setAll(100, 4, 0);
	}
	currentpage = pages.begin();
}

void ScoreDrawing::setNum(const int &num){
	
}

void ScoreDrawing::setColor(const QString &color){
	
}

void ScoreDrawing::setMouse(const qreal x, const qreal y){
	m_mousex = static_cast<uint32_t>(x);
	m_mousey = static_cast<uint32_t>(y);
}


bool ScoreDrawing::setNote(const int16_t mousex, const int16_t mousey, const int type, const int hand){
	md::notetype mdtype = static_cast<md::notetype>(type);
	md::notehand mdhand = static_cast<md::notehand>(hand);
	(*currentpage).setNote(
		(*currentpage).getNoteLine(m_width*4/6, mousex),
		mdtype,
		mdhand,
		(*currentpage).getNoteTime(m_height*8/10, mousey)
		);
}

bool ScoreDrawing::removeNote(const int16_t mousex, const int16_t mousey){
	
}

void ScoreDrawing::drawGrayIcon(QPainter *painter){
	QRect target(
		(*currentpage).getNoteLinePixel(m_width*4/6, m_mousex)-14,
		(*currentpage).getNoteTimePixel(m_height*8/10, m_mousey)-14,
		28, 28);
	QRect source(0, 0, 28, 28);
	QImage image("./img/note1_gray.png");
	painter->drawImage(target, image, source);
}

void ScoreDrawing::drawIcon(QPainter *painter){
	QRect target(
		(*currentpage).getNoteLinePixel(m_width*4/6, m_mousex)-14,
		(*currentpage).getNoteTimePixel(m_height*8/10, m_mousey)-14,
		28, 28);
	QRect source(0, 0, 28, 28);
	QImage image("./img/note1.png");
	painter->drawImage(target, image, source);
}

void ScoreDrawing::drawAllIcon(QPainter *painter){
	QRect target(
		(*currentpage).getNoteLinePixel(m_width*4/6, m_mousex)-14,
		(*currentpage).getNoteTimePixel(m_height*8/10, m_mousey)-14,
		28, 28);
	QRect source(0, 0, 28, 28);
	QImage image("./img/note1.png");
	painter->drawImage(target, image, source);
}


void ScoreDrawing::drawGrid(QPainter *painter){
    QPen pen(QColor("black"));
	QRect rect(0, 0, 1, m_height);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
	for(auto i=0; i<5; ++i){
		rect.moveTo((i+1)*m_width/6, 0);
		painter->fillRect(rect, "black");
	}
	rect.setWidth(m_width);
	for(auto i=0; i<5; ++i){
		if(i == 0 || i == 4) rect.setHeight(3);
		else 	rect.setHeight(1);
		rect.moveTo(0, (m_height*81/400)*i+(m_height/10));
		painter->fillRect(rect, "black");
	}
}

// called as update()
void ScoreDrawing::paint(QPainter *painter){
	drawGrid(painter);
	drawGrayIcon(painter);

	// drawAllIcon(painter);

    // QFont font = QFont();
    // QPen pen(m_color, 3);
    // QRect rect(0, 0, 100, 100);
    // rect.moveTo(110, 70);
    // font.setPointSize(30);
    // painter->setFont(font);
    // painter->setPen(pen);
    // painter->setRenderHints(QPainter::Antialiasing, true);
    // painter->fillRect(rect, "white");
    // painter->drawText(150, 110, m_num);
}
