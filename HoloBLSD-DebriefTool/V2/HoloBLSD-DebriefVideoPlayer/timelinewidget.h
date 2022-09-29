#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include "qgraphicsscene.h"
#include "qgraphicsview.h"
#include <QObject>
#include <QWidget>
#include <QScrollBar>
#include "qboxlayout.h"
#include "qscrollarea.h"
#include "timeline.h"
#include "timelinetoolbar.h"
#include "fileopener.h"

class TimelineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineWidget(QWidget *parent= nullptr, FileOpener *_fileOpener=nullptr, int _Width=0, int Height=0);

    Timeline *GetTimeline();
    TimelineToolBar *GetToolBar();
private:
    QScrollArea* toolbarArea;
    QGraphicsScene* timelineScene;
    QGraphicsView* timelineView;
    QGraphicsScene*  activityScene;
    QGraphicsView* activityView;
    Timeline* timeline;
    TimelineToolBar* toolbar;

    void DrawBackground(QGraphicsScene *_scene, int _height, int _width);
signals:

};

#endif // TIMELINEWIDGET_H