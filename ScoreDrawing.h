#include <QQuickPaintedItem>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QRect>
#include <QFont>

#include "MusicData.h"

class ScoreDrawing : public QQuickPaintedItem{
    Q_OBJECT
    Q_DISABLE_COPY(ScoreDrawing)

public:
    explicit ScoreDrawing(QQuickItem *parent = 0);

    Q_INVOKABLE void setNum(const int &num);

    Q_INVOKABLE void setColor(const QString &color);

	Q_INVOKABLE bool setNote(const int16_t mousex, const int16_t mousey, const md::notetype type);
	Q_INVOKABLE bool removeNote(const int16_t mousex, const int16_t mousey);

	void drawGrid(QPainter *painter);
    void paint(QPainter *painter);

private:
	const int16_t m_width, m_height;
	
};
