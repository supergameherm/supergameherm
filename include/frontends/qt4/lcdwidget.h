#ifndef __LCDWIDGET_H__
#define __LCDWIDGET_H__

#include <QWidget>

class LCDWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LCDWidget(QWidget *parent = 0);
	~LCDWidget();

	void setData(uchar *data);

signals:

public slots:

protected:
	void paintEvent(QPaintEvent *);

	QImage *image;
};

#endif // !LCDWIDGET_H
