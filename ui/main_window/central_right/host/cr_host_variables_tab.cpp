#include "cr_host_variables_tab.h"
#include "app/app.h"
#include "db/exception.h"
#include "central_right_host_tab.h"

namespace meow {
namespace ui {
namespace main_window {
namespace central_right {

HostVariablesTab::HostVariablesTab(QWidget *parent)
    : QWidget(parent)
{
    _mainLayout = new QVBoxLayout();
    _mainLayout->setContentsMargins(2, 2, 2, 2);
    this->setLayout(_mainLayout);

    createVariablesTable();
}

void HostVariablesTab::createVariablesTable()
{

    _variablesTable = new QTableView();
    _variablesTable->verticalHeader()->hide();
    _variablesTable->horizontalHeader()->setHighlightSections(false);
    auto geometrySettings = meow::app()->settings()->geometrySettings();
    _variablesTable->verticalHeader()->setDefaultSectionSize(
       geometrySettings->tableViewDefaultRowHeight());

    _variablesTable->setModel(&_model);
    _mainLayout->addWidget(_variablesTable);
    _variablesTable->setSortingEnabled(false); // TODO
    _variablesTable->setSelectionBehavior(
                QAbstractItemView::SelectionBehavior::SelectRows);
    _variablesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i=0; i<_model.columnCount(); ++i) {
        _variablesTable->setColumnWidth(i, _model.columnWidth(i));
    }
    _variablesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_variablesTable, &QWidget::customContextMenuRequested,
            this, &HostVariablesTab::onTableContextMenu);
}

void HostVariablesTab::setSession(meow::db::SessionEntity * session)
{
    _model.setSession(session);
}

void HostVariablesTab::onTableContextMenu(const QPoint &pos)
{
    QMenu menu(this);

    QAction refreshAction(QIcon(":/icons/arrow_refresh.png"),
                          tr("Refresh"), nullptr);
    refreshAction.setShortcuts(QKeySequence::Refresh);

    connect(&refreshAction, &QAction::triggered, [=](bool checked) {
        Q_UNUSED(checked);
        try {
            _model.refresh();
        } catch(meow::db::Exception & ex) {
            HostTab::showErrorMessage(ex.message());
        }
    });

    menu.addAction(&refreshAction);

    menu.exec(_variablesTable->viewport()->mapToGlobal(pos));
}

} // namespace central_right
} // namespace main_window
} // namespace ui
} // namespace meow
