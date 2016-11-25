#include "ScorePage.h"

using namespace md;
using namespace std;

ScorePage::ScorePage(uint16_t m_bpm, uint16_t m_measure, uint16_t m_biastime){
	bpm = m_bpm;
	measure = m_measure;
	biastime = m_biastime;
	divider = measure;
}

ScorePage::~ScorePage(){
	
}

void ScorePage::setDivide(uint16_t d){
	divider = d;
}

void ScorePage::setAll(uint16_t m_bpm, uint16_t m_measure, uint16_t m_biastime){
	bpm = m_bpm;
	measure = m_measure;
	biastime = m_biastime;
	divider = measure;
}

bool ScorePage::setNote(Noteline line, Notetype type, Notehand hand, uint32_t time){
	Note tmpnote = {
		static_cast<unsigned>(type),
		0,
		0,
		static_cast<unsigned>(hand),
		static_cast<unsigned>(line)
	};
	notes.insert(make_pair(time, tmpnote));
	return true;
}

bool ScorePage::removeNote(Noteline line, uint32_t time){
	if(notes.count(time) == 0) return false;
	for(auto ite = notes.equal_range(time);
		ite.first != ite.second; ite.first++){
		if((*ite.first).second.line == static_cast<unsigned>(line)){
			notes.erase(ite.first);
			return true;
		}
	}
	return false;
}

uint32_t ScorePage::getNoteTimePixel(uint32_t pageheight, uint32_t pagey){
	// @TODO
	setDivide(4);
	
	pagey -= (pageheight/(2*divider));
	return static_cast<uint32_t>((pagey+(pageheight/(2*divider)))/(pageheight/divider))*(pageheight/divider);
}

uint32_t ScorePage::getNoteTime(uint32_t pageheight, uint32_t pagey){
	// @TODO
	setDivide(4);
	
	uint16_t length = bpm/measure;
	uint32_t pixel = getNoteTimePixel(pageheight, pagey);

	return length*pixel/pageheight;
}

uint32_t ScorePage::getNoteLinePixel(uint32_t pagewidth, uint32_t pagex){
	return static_cast<uint32_t>((pagex+(pagewidth/8))/(pagewidth/4))*(pagewidth/4);
}

Noteline ScorePage::getNoteLine(uint32_t pagewidth, uint32_t pagex){
	return static_cast<Noteline>((getNoteLinePixel(pagewidth, pagex)+(3*pagewidth/8))/(pagewidth/4));
}

pair<uint16_t, uint16_t> ScorePage::getNotePixels(uint32_t time, Noteline line, uint32_t pageheight, uint32_t pagewidth){
	std::pair<uint16_t, uint16_t> tmp(
		(static_cast<uint16_t>(line)*(pagewidth/4)),
		(time*pageheight*measure/bpm)
		);
	return tmp;
}

Note ScorePage::getNote(uint32_t time, Noteline line){
	Note no = {
		static_cast<unsigned>(Notetype::ERROR),
		0,
		0,
		static_cast<unsigned>(Notehand::ERROR),
		static_cast<unsigned>(Noteline::NONE),
	};
	if(notes.count(time) == 0) return no;
	for(auto ite = notes.equal_range(time);
		ite.first != ite.second; ite.first++){
		if((*ite.first).second.line == static_cast<unsigned>(line)){
			return (*ite.first).second;
		}
	}
	return no;
}

multimap<uint32_t, Note> ScorePage::getAllNotes(){
	return notes;
}
