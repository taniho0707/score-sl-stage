#include "ScoreDrawing.h"

ScoreDrawing::ScoreDrawing(QQuickItem *parent)
	: QQuickPaintedItem(parent),
	  m_width(300),
	  m_height(500)
{
	
}

void ScoreDrawing::setNum(const int &num){
	
}

void ScoreDrawing::setColor(const QString &color){
	
}

bool ScoreDrawing::setNote(const int16_t mousex, const int16_t mousey, const md::notetype type){
	
}

bool ScoreDrawing::removeNote(const int16_t mousex, const int16_t mousey){
	
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
