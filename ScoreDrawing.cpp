#include "ScoreDrawing.h"

using namespace std;
using namespace md;

ScoreDrawing::ScoreDrawing(QQuickItem *parent)
	: QQuickPaintedItem(parent),
	  m_width(300),
	  m_height(500),
	  m_divider(Denom::FOUR)
{
	currentpage = 1;
	maxpage = 30;
	mouse_image.load("./img/note1_gray.png");
	filename.clear();
}

void ScoreDrawing::setNum(const int &num){
	
}

void ScoreDrawing::setColor(const QString &color){
	
}

void ScoreDrawing::setMouse(const qreal x, const qreal y){
	m_mousex = static_cast<uint32_t>(x);
	m_mousey = static_cast<uint32_t>(y);
}

void ScoreDrawing::changePage(const int page){
	currentpage = page;
}


bool ScoreDrawing::setType(const int type){
	switch(static_cast<Notetype>(type)){
	case Notetype::SINGLE:
		mouse_image.load("./img/note1_gray.png");
		break;
	case Notetype::LONG_START:
		mouse_image.load("./img/note2_gray.png");
		break;
	case Notetype::LONG_END:
		mouse_image.load("./img/note3_gray.png");
		break;
	case Notetype::SLIDELEFT_CONT:
		mouse_image.load("./img/note4_gray.png");
		break;
	case Notetype::SLIDELEFT_END:
		mouse_image.load("./img/note5_gray.png");
		break;
	case Notetype::SLIDERIGHT_CONT:
		mouse_image.load("./img/note6_gray.png");
		break;
	case Notetype::SLIDERIGHT_END:
		mouse_image.load("./img/note7_gray.png");
		break;
	case Notetype::SLIDEPLUS_CONT:
		mouse_image.load("./img/note8_gray.png");
		break;
	case Notetype::SLIDEPLUS_END:
		mouse_image.load("./img/note9_gray.png");
		break;
	}
}

int ScoreDrawing::getMaxpage(){
	return maxpage;
}
void ScoreDrawing::setMaxpage(const int page){
	maxpage = page;
}

QString ScoreDrawing::getFilename(){
	return QString::fromStdString(filename);
}

bool ScoreDrawing::setFilename(const QString &name){
	filename = QUrl(name).fileName().toStdString();
	filename = "score/" + filename;
	
	ifstream fin(filename, ios::in | ios::binary );
	if (!fin){
		cout << "Cannot open or not exist " << filename << endl;
		return false;
	}
	uint32_t max = 0;
	fin.read((char *) &max, sizeof(uint32_t));
	maxpage = max;
	uint32_t size = 0;
	fin.read((char *) &size, sizeof(uint32_t));
	cout << "Notes: " << size << endl;
	struct Notedata data;
	scoredata.notes.clear();
	for(int i=0; i<size; ++i){
		fin.read((char *) &data, sizeof(struct Notedata));
		cout << "denom:" << (uint16_t)data.denominator << ",num:" << (uint16_t)data.numerator << ",measure:" << data.measure << endl;
		scoredata.addNote(data);
	}
	fin.close();
	cout << filename << " loaded." << endl;
	update();
}

bool ScoreDrawing::setDenom(const int denom){
	m_divider = static_cast<Denom>(denom);
	return true;
}

bool ScoreDrawing::setNote(const int type, const int hand){
	struct Notedata note = getMousey2Line(m_mousey, m_divider);
	note.line = getMousex2Line(m_mousex);
	note.type = static_cast<Notetype>(type);
	note.measure = currentpage;
	note.hand = static_cast<Notehand>(hand);

	using iterator = multimap<uint32_t, struct Notedata>::iterator;
	std::pair<iterator, iterator> ret = scoredata.notes.equal_range(note.getNumber());
	for(iterator it = ret.first; it != ret.second; ++it) {
		if(it->second.line == note.line){
			it->second.hand = static_cast<Notehand>(hand);
			cout << "Already exists, set hand to " << (it->second.hand==Notehand::LEFT ? "Left" : "Right")
				 << endl;
			return false;
		}
	}

	scoredata.addNote(note);
	std::cout << "Set: "
		<< "line:" << static_cast<uint16_t>(note.line) << ", "
		<< static_cast<uint16_t>(note.numerator) << " / " << static_cast<uint16_t>(note.denominator)
		<< ", Num: " << note.getNumber()
		<< std::endl;
	return true;
}

bool ScoreDrawing::removeNote(){
	struct Notedata note = getMousey2Line(m_mousey, m_divider);
	note.line = getMousex2Line(m_mousex);
	note.measure = currentpage;

	using iterator = multimap<uint32_t, struct Notedata>::iterator;
	std::pair<iterator, iterator> ret = scoredata.notes.equal_range(note.getNumber());
	for(iterator it = ret.first; it != ret.second; ++it) {
		if(it->second.line == note.line){
			scoredata.notes.erase(it);
			cout << "Remove: "
				<< "line:" << static_cast<uint16_t>(note.line) << ", "
				<< static_cast<uint16_t>(note.numerator) << " / " << static_cast<uint16_t>(note.denominator)
					  << endl;
			return true;
		}
	}
	cout << "No notes." << endl;
	return false;
}

bool ScoreDrawing::save(){
	ofstream fout;
	fout.open(filename, ios::out|ios::binary|ios::trunc);
	if (!fout) {
		cout << "failure to open " << filename << endl;
		return false;
	}
	fout.write((char *) &maxpage, sizeof(uint32_t));
	uint32_t size = scoredata.notes.size();
	fout.write((char *) &size, sizeof(uint32_t));
	for(auto it : scoredata.notes){
		fout.write((char *) &it.second, sizeof(struct Notedata));
	}
	fout.close();
	cout << "Saved score to " << filename << endl;
	cout << sizeof(struct Notedata) << endl;
	return true;
}

void ScoreDrawing::drawGrayIcon(QPainter *painter){
	Notedata note = getMousey2Line(m_mousey, m_divider);
	QRect target(
		(static_cast<int16_t>(getMousex2Line(m_mousex))+1)*(m_width/6) - 14,
		(m_height - (m_height*4/5)*note.numerator/static_cast<uint16_t>(note.denominator) - (m_height/10)) - 14,
		28, 28);
	QRect source(0, 0, 28, 28);
	painter->drawImage(target, mouse_image, source);
}

void ScoreDrawing::drawIcon(uint32_t x, uint32_t y, Notetype t, QPainter *painter){
	QRect target(x, y, 28, 28);
	QRect source(0, 0, 28, 28);
	QImage image("./img/note1.png");
	painter->drawImage(target, image, source);
	// @TODO adapt to showing note2-note4
}

void ScoreDrawing::drawAllIcon(QPainter *painter){
	struct Notedata zero = {Denom::FOUR, 0, currentpage, Notetype::SINGLE, Noteline::MIDDLE, Notehand::LEFT};
	using iterator = multimap<uint32_t, struct Notedata>::iterator;
	iterator it = scoredata.notes.lower_bound(zero.getNumber()-1);
	zero.measure = currentpage+1;
	iterator top = scoredata.notes.upper_bound(zero.getNumber()-1);
	for(iterator cnote = it; it != top; ++it) {
		QRect targethand(
			(static_cast<int16_t>(it->second.line)+1)*(m_width/6) - 14 - 2,
			(m_height - (m_height*4/5)*it->second.numerator/static_cast<uint16_t>(it->second.denominator) - (m_height/10)) - 14,
			32, 28);
		QRect sourcehand(0, 0, 32, 28);
		QImage imagehand;
		if(it->second.hand == Notehand::LEFT) imagehand.load("./img/lefthand.png");
		else imagehand.load("./img/righthand.png");
		painter->drawImage(targethand, imagehand, sourcehand);
		QRect target(
			(static_cast<int16_t>(it->second.line)+1)*(m_width/6) - 14,
			(m_height - (m_height*4/5)*it->second.numerator/static_cast<uint16_t>(it->second.denominator) - (m_height/10)) - 14,
			28, 28);
		QRect source(0, 0, 28, 28);
		QImage image;
		switch(it->second.type){
		case Notetype::SINGLE:
			image.load("./img/note1.png");
			break;
		case Notetype::LONG_START:
			image.load("./img/note2.png");
			break;
		case Notetype::LONG_END:
			image.load("./img/note3.png");
			break;
		case Notetype::SLIDELEFT_CONT:
			image.load("./img/note4.png");
			break;
		case Notetype::SLIDELEFT_END:
			image.load("./img/note5.png");
			break;
		case Notetype::SLIDERIGHT_CONT:
			image.load("./img/note6.png");
			break;
		case Notetype::SLIDERIGHT_END:
			image.load("./img/note7.png");
			break;
		case Notetype::SLIDEPLUS_CONT:
			image.load("./img/note8.png");
			break;
		case Notetype::SLIDEPLUS_END:
			image.load("./img/note9.png");
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
	int16_t newy = m_height - y - m_height/10;
	int16_t tmp = floor((newy + max/(2*static_cast<uint16_t>(denom))) * static_cast<uint16_t>(denom) / max);
	if(tmp >= static_cast<int16_t>(denom)) tmp = static_cast<int16_t>(denom)-1;
	if(tmp < 0) tmp = 0;
	return (struct Notedata){denom, tmp, 0, Notetype::SINGLE, Noteline::MIDDLE, Notehand::LEFT};
}


// called as update()
void ScoreDrawing::paint(QPainter *painter){
	drawGrid(painter);
	drawAllIcon(painter);
	drawGrayIcon(painter);
}
