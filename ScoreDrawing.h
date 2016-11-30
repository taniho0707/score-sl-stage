#include <QQuickPaintedItem>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QRect>
#include <QFont>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "MusicData.h"

class ScoreDrawing : public QQuickPaintedItem{
    Q_OBJECT
    Q_DISABLE_COPY(ScoreDrawing)

public:
    explicit ScoreDrawing(QQuickItem *parent = 0);

    Q_INVOKABLE void setNum(const int &num);
    Q_INVOKABLE void setColor(const QString &color);

	Q_INVOKABLE void setMouse(const qreal x, const qreal y);
	Q_INVOKABLE void changePage(const int page);

	Q_INVOKABLE int getMaxpage();
	Q_INVOKABLE void setMaxpage(const int page);
	Q_INVOKABLE QString getFilename();
	Q_INVOKABLE bool setFilename(const QString& name);
	Q_INVOKABLE bool setDenom(const int denom);
	Q_INVOKABLE bool setNote(const int type, const int hand);
	Q_INVOKABLE bool removeNote();

	Q_INVOKABLE bool save();

	void drawGrayIcon(QPainter *painter);

	void drawAllIcon(QPainter *painter);
	void drawIcon(uint32_t x, uint32_t y, md::Notetype t, QPainter *painter);

	void drawGrid(QPainter *painter);
    void paint(QPainter *painter);

	// pixel convertion funcs
	md::Noteline getMousex2Line(uint32_t x);
	md::Notedata getMousey2Line(uint32_t y, md::Denom denom);

private:
	md::Score scoredata;
	uint16_t currentpage;
	uint16_t maxpage;
	std::string filename;
	
	const int16_t m_width, m_height;
	uint32_t m_mousex, m_mousey;
	md::Denom m_divider;
};
