#include "ScorePage.h"

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

bool ScorePage::setNote(md::noteline line, md::notetype type, md::notehand hand, uint32_t time){
	md::note tmpnote = {
		static_cast<unsigned>(type),
		0,
		0,
		static_cast<unsigned>(hand),
		static_cast<unsigned>(line)
	};
	notes.insert(std::make_pair(time, tmpnote));
}

bool ScorePage::removeNote(md::noteline line, uint32_t time){
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
	return ((pagey+pageheight)/(2*divider))/(pageheight/divider));
}

uint32_t ScorePage::getNoteTime(uint32_t pageheight, uint32_t pagey){
	uint16_t length = bpm/measure;
	uint32_t pixel = static_cast<uint32_t>(
		((pagey+pageheight)/(2*divider))/(pageheight/divider))*(pageheight/divider
			);
	return length*pixel/pageheight;
}

md::noteline ScorePage::getNoteLine(uint32_t pagewidth, uint32_t pagex){
	return static_cast<md::noteline>(((pagex+pagewidth)/12)/(pagewidth/6));
}

md::note ScorePage::getNote(uint32_t time, md::noteline line){
	md::note no = {
		static_cast<unsigned>(md::notetype::ERROR),
		0,
		0,
		static_cast<unsigned>(md::notehand::ERROR),
		static_cast<unsigned>(md::noteline::NONE),
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
