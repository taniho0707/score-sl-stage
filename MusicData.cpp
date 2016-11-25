#include "MusicData.h"

using namespace std;
using namespace md;

MusicData::MusicData(){
	
}

multimap<uint32_t, struct Notedata>::iterator addNote(struct Notedata data){
	return notes.emplace(data.getNumber(), data);
}

bool removeNote(uint32_t number, Noteline line){
	using iterator = multimap<uint32_t, struct Notedata>::iterator;
	std::pair<iterator, iterator> ret = m.equal_range(number);
	for(iterator it = ret.first; it != ret.second; ++it) {
		if(it.second.line == line){
			notes.remove(it);
			return true;
		}
	}
	return false;
}

