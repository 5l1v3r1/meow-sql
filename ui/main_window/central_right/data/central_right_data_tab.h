#ifndef CENTRAL_RIGHT_DATA_TAB_H
#define CENTRAL_RIGHT_DATA_TAB_H

#include <QtWidgets>

namespace meow {
namespace ui {
namespace main_window {
namespace central_right {

class DataTab : public QWidget
{

public:
    explicit DataTab(QWidget *parent = 0);
private:

    void createDataTable();
    void createTopPanel();
    void createToolBar();

    QVBoxLayout * _mainLayout;
    // top panel:
    QHBoxLayout * _topLayout;
    QLabel * _dataLabel;
    QToolBar * _toolBar;
    QAction * _nextRowsAction;
    QAction * _showAllRowsAction;
    // bottom:
    QTableView  * _dataTable;
};

} // namespace central_right
} // namespace main_window
} // namespace ui
} // namespace meow

#endif // CENTRAL_RIGHT_DATA_TAB_H