#pragma once

#include <utility>
#include <iterator>
#include <map>

#include <iostream>

#include "MusicData.h"

class ScorePage{
public:
	ScorePage(uint16_t m_bpm=100, uint16_t m_measure=4, uint16_t m_biastime=0);
	virtual ~ScorePage();

	void setDivide(uint16_t);

	void setAll(uint16_t, uint16_t, uint16_t);
	
	bool setNote(md::Noteline, md::Notetype, md::Notehand, uint32_t);
	bool removeNote(md::Noteline, uint32_t);
	uint32_t getNoteTime(uint32_t pageheight, uint32_t pagey); //upside is 0, bottomside is max
	uint32_t getNoteTimePixel(uint32_t pageheight, uint32_t pagey);
	uint32_t getNoteLinePixel(uint32_t pagewidth, uint32_t pagex);
	md::Noteline getNoteLine(uint32_t pagewidth, uint32_t pagex);
	std::pair<uint16_t, uint16_t> getNotePixels(uint32_t time, md::Noteline line, uint32_t pageheight, uint32_t pagewidth);

	md::Note getNote(uint32_t, md::Noteline);
	std::multimap<uint32_t, md::Note> getAllNotes();

private:
	uint16_t bpm;
	uint16_t measure;
	uint32_t biastime;
	uint16_t divider;
	std::multimap<uint32_t, md::Notedata> notes;

};
