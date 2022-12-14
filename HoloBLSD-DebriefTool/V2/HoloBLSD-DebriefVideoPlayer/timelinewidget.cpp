#include "timelinewidget.h"
#include "mainwindow.h"

TimelineWidget::TimelineWidget( MainWindow* _mw,QWidget *parent,FileOpener* _fileOpener ,int _width, int _height)
    : QWidget{parent}
{
    mainWindow=_mw;
    Theme* theme = new Theme();

    toolbarArea = new QScrollArea(this);
    toolbarArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    toolbarArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    toolbarArea->setFixedSize(_width,_height/10);
    toolbar = new TimelineToolBar(toolbarArea, _fileOpener,_mw, _width, _height/10);
    qDebug()<< "toolbar area cations" << toolbarArea->actions();



    QScrollArea* localScrollArea = new QScrollArea(this);
    localScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    localScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    localScrollArea->setFixedSize(_width,_height);


    QVBoxLayout* timelineFrame = new QVBoxLayout(this);
    timelineFrame->setMargin(0);
    timelineFrame->addWidget(toolbarArea);
    timelineFrame->addWidget(localScrollArea);

    QHBoxLayout* timelineWidgetLayout = new QHBoxLayout(localScrollArea);

    QScrollArea* activityScrollArea = new QScrollArea();
    activityScrollArea->setMaximumWidth(_width/6);
    activityScrollArea->setMinimumWidth(_width/6);
    activityScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    activityScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timelineWidgetLayout->addWidget(activityScrollArea);


    timelineScene = new QGraphicsScene();
    timelineView = new QGraphicsView(timelineScene);
    timelineView->setInteractive(true);


    activityScene = new QGraphicsScene();
    activityView = new QGraphicsView(activityScene);
    activityView->setInteractive(true);

    activityScene->setBackgroundBrush(theme->TimelineBG);
    activityScene->setSceneRect(0,0,_width/6,1000);
    timelineScene->setBackgroundBrush(theme->TimelineBG);
    timelineScene->setSceneRect(0,0, 5*_width/6,1000);
    timelineWidgetLayout->addWidget(timelineView);

    timeline = new Timeline(timelineView,this, _fileOpener, 5*_width/6,activityScene);

    activityScrollArea->setWidget(activityView);

    connect(activityScrollArea->verticalScrollBar(), &QScrollBar::valueChanged, timelineView->verticalScrollBar(), &QScrollBar::setValue);
    connect(timelineView->verticalScrollBar(),&QScrollBar::valueChanged, activityScrollArea->verticalScrollBar(), &QScrollBar::setValue);
    connect(timeline, &Timeline::TimelineDrawn, this, &TimelineWidget::ChangeSceneRect);
    connect(mainWindow, &MainWindow::SaveSession, this, &TimelineWidget::SaveData);
    connect(mainWindow, &MainWindow::OpenSession, this, &TimelineWidget::LoadData);

}

void TimelineWidget::ChangeSceneRect(){
    timelineScene->setSceneRect(0,0, timeline->GetTimelineLength(),1000);
}

Timeline* TimelineWidget::GetTimeline(){
    return timeline;
}

TimelineToolBar* TimelineWidget::GetToolBar(){
    return toolbar;
}

void TimelineWidget::SaveData(){
    mainWindow->SaveTimelineValues(toolbar->zoom ,toolbar->volume ,timeline->GetCursor()->x() );
}
void TimelineWidget::LoadData(){
     toolbar->SetZoom(mainWindow->GetScale());
     toolbar->SetVolume(mainWindow->GetVolume());
     timeline->UpdateVideoCursorX(mainWindow->GetVC());
}
