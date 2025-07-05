#include "CustomGraphicsView.h"

CustomGraphicsView::CustomGraphicsView(QWidget* parent)
    : QGraphicsView(parent), isPanning(false) {}

void CustomGraphicsView::wheelEvent(QWheelEvent* event) {
    const double scaleFactor = 1.15; // Zoom factor
    if (event->angleDelta().y() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zoom out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void CustomGraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        isPanning = true;
        panStart = event->pos(); // Store the starting position
        setCursor(Qt::ClosedHandCursor); // Change cursor
    } else {
        QGraphicsView::mousePressEvent(event); // Default behavior
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (isPanning) {
        QPointF delta = mapToScene(event->pos()) - mapToScene(panStart);
        panStart = event->pos(); // Update panStart for the next movement
        translate(-delta.x(), -delta.y()); // Move the view
    } else {
        QGraphicsView::mouseMoveEvent(event); // Default behavior
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        isPanning = false; // Stop panning
        setCursor(Qt::ArrowCursor); // Reset cursor
    } else {
        QGraphicsView::mouseReleaseEvent(event); // Default behavior
    }
}
