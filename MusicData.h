#pragma once

#include <vector>
#include <stdint.h>

namespace md{

	enum class Notetype : uint8_t {
		SINGLE,
		LONG_START,
		LONG_END,
		SLIDERIGHT_CONT,
		SLIDERIGHT_END,
		SLIDELEFT_CONT,
		SLIDELEFT_END,
		ERROR = 15
	};

	enum class noteline : uint8_t {
		LEFT,
		LEFTMIDDLE,
		MIDDLE,
		RIGHTMIDDLE,
		RIGHT,
		NONE = 7
	};

	enum class Notehand : uint8_t {
		LEFT,
		RIGHT,
		ERROR = 3
	};

	enum class Denom : uint8_t {
		FOUR,
		EIGHT,
		SIXTEEN,
		THREE,
	};

	/* ノーツデータ
	   1. ノーツタイプ
	      4bit
	      単音，連続開始，連続終了，スライド開始，スライド継続，スライド終了
	   2. 演奏時刻
	      18bit
	      in ms
	   3. 次のノーツ番号
	      10bit
	   4. 演奏腕
	      1bit
	      右，左
	   5. ノーツライン
	      3bit
	*/
	struct Notedata {
		Denom denominator;
		uint8_t numerator;
		uint16_t measure;
		Notetype type;
		Noteline line;
	};

	class Score {
	private:
		
	public:
		std::list<struct Notedata> notes;

		Score();

		bool addNote(uint16_t, struct Notedata);
		bool removeNote(uint16_t, struct Notedata);

		uint8_t getPage(std::list<struct Notedata>::iterator ite);
		
	};
}
