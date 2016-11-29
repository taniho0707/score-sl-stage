#include "ScoreDrawing.h"

using namespace std;
using namespace md;

ScoreDrawing::ScoreDrawing(QQuickItem *parent)
	: QQuickPaintedItem(parent),
	  m_width(300),
	  m_height(500),
	  m_divider(Denom::FOUR)
{
	currentpage = 0;
}

void ScoreDrawing::setNum(const int &num){
	
}

void ScoreDrawing::setColor(const QString &color){
	
}

void ScoreDrawing::setMouse(const qreal x, const qreal y){
	m_mousex = static_cast<uint32_t>(x);
	m_mousey = static_cast<uint32_t>(y);
}


bool ScoreDrawing::setNote(const int type, const int hand){
	Notetype mdtype = static_cast<Notetype>(type);
	struct Notedata note = getMousey2Line(m_mousey+14, m_divider);
	note.line = getMousex2Line(m_mousex + 14);
	scoredata.addNote(note);
	std::cout << "Set: "
		<< "line:" << static_cast<uint16_t>(note.line) << ", "
		<< static_cast<uint16_t>(note.numerator) << " / " << static_cast<uint16_t>(note.denominator)
		<< std::endl;
}

bool ScoreDrawing::removeNote(){
	
}

void ScoreDrawing::drawGrayIcon(QPainter *painter){
	Notedata note = getMousey2Line(m_mousey+14, m_divider);
	QRect target(
		(static_cast<int16_t>(getMousex2Line(m_mousex + 14))+1)*(m_width/6) - 14,
		(m_height - (m_height*4/5)*note.numerator/static_cast<uint16_t>(note.denominator) - (m_height/10)) - 14,
		28, 28);
	QRect source(0, 0, 28, 28);
	QImage image("./img/note1_gray.png");
	painter->drawImage(target, image, source);
}

void ScoreDrawing::drawIcon(uint32_t x, uint32_t y, Notetype t, QPainter *painter){
	QRect target(x, y, 28, 28);
	QRect source(0, 0, 28, 28);
	QImage image("./img/note1.png");
	painter->drawImage(target, image, source);
	// @TODO adapt to showing note2-note4
}

void ScoreDrawing::drawAllIcon(QPainter *painter){
	struct Notedata zero = {Denom::FOUR, 0, currentpage, Notetype::SINGLE, Noteline::MIDDLE};
	using iterator = multimap<uint32_t, struct Notedata>::iterator;
	iterator it = scoredata.notes.lower_bound(zero.getNumber());
	zero.measure = currentpage+1;
	iterator top = scoredata.notes.upper_bound(zero.getNumber());
	for(iterator cnote = it; it != top; ++it) {
		QRect target(
			(static_cast<int16_t>(it->second.line)+1)*(m_width/6) - 14,
			(m_height - (m_height*4/5)*it->second.numerator/static_cast<uint16_t>(it->second.denominator) - (m_height/10)) - 14,
			28, 28);
		QRect source(0, 0, 28, 28);
		QImage image("./img/note1_gray.png");
		switch(it->second.type){
		case Notetype::SINGLE:
			image.load("./img/note1.png");
			break;
		case Notetype::LONG_START:
		case Notetype::LONG_END:
			image.load("./img/note2.png");
			break;
		case Notetype::SLIDELEFT_CONT:
		case Notetype::SLIDELEFT_END:
			image.load("./img/note4.png");
			break;
		case Notetype::SLIDERIGHT_CONT:
		case Notetype::SLIDERIGHT_END:
			image.load("./img/note5.png");
			break;
		}
		painter->drawImage(target, image, source);
	}
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


Noteline ScoreDrawing::getMousex2Line(uint32_t x){
	int16_t tmp = floor((x - (m_width/12))/(m_width/6));
	if(tmp < 0) tmp = 0;
	if(tmp > 4) tmp = 4;
	return static_cast<Noteline>(tmp);
}
Notedata ScoreDrawing::getMousey2Line(uint32_t y, md::Denom denom){
	int16_t max = m_height * 4 / 5;
	int16_t newy = m_height - y;
	int16_t tmp = floor(newy * static_cast<uint16_t>(denom) / max);
	return (struct Notedata){denom, tmp, 0, Notetype::SINGLE, Noteline::MIDDLE};
}


// called as update()
void ScoreDrawing::paint(QPainter *painter){
	drawGrid(painter);
	drawGrayIcon(painter);

	drawAllIcon(painter);

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
