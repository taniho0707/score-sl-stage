#pragma once

#include <utility>
#include <iterator>
#include <map>

#include "MusicData.h"

class ScorePage{
public:
	ScorePage(uint16_t, uint16_t, uint16_t);
	~ScorePage();

	void setDivide(uint16_t);
	
	bool setNote(md::noteline, md::notetype, md::notehand, uint32_t);
	bool removeNote(md::noteline, uint32_t);
	uint32_t getNoteTime(uint32_t pageheight, uint32_t pagey); //upside is 0, bottomside is max
	md::noteline getNoteLine(uint32_t pagewidth, uint32_t pagex);

	md::note getNote(uint32_t, md::noteline);

private:
	uint16_t bpm;
	uint16_t measure;
	uint32_t biastime;
	uint16_t divider;
	std::multimap<uint32_t, md::note> notes;

};
