#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override; // For zooming
    void mousePressEvent(QMouseEvent* event) override; // For starting pan
    void mouseMoveEvent(QMouseEvent* event) override; // For panning
    void mouseReleaseEvent(QMouseEvent* event) override; // To stop pan

private:
    bool isPanning;        // Tracks if we are currently panning
    QPoint panStart;       // Tracks the start position of a pan
};

#endif // CUSTOMGRAPHICSVIEW_H
