/*
  This file is part of onceagain.

  Copyright (C) 2016 Sérgio Martins <iamsergio@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <kddockwidgets/MainWindow.h>
#include <QMainWindow>

class Action;
class Script;
class Kernel;
class QTreeView;
class QTableWidget;
class QPushButton;
class QTableWidgetItem;
class ScriptModel;
class ScriptProxyModel;
class QLabel;
class QTextEdit;
class QContextMenuEvent;

class MainWindow : public KDDockWidgets::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(Kernel *sb, QWidget *parent = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent *ev) override;

private Q_SLOTS:
    void onPropertyChanged();
Q_SIGNALS:
    void propertyChanged(Action*);

private:
    void reloadSelectedScript();
    void setIsDebug(bool);
    void setShowReadonlyProperties(bool);
    void openFileExplorer(QString path);
    void openTemplatesDir();
    void openScriptsDir();
    void createNewScript();
    void createNewScriptFolder();
    void onPropertyCellDoubleClicked(QTableWidgetItem *);
    void openScriptExternally(const QModelIndex &);
    void updateBaseTargetLabel();
    void updateDescription();
    Script* selectedScript() const;
    QString selectedFolder() const;
    void onScriptSelected();
    void setupScriptView();
    void executeScript();
    void setupPropertyTable(Script *script = nullptr);
    Kernel *const m_kernel;
    QTableWidget *m_propertyTable;
    QTreeView *m_scriptView;
    QPushButton *m_executeButton;
    ScriptProxyModel *const m_scriptProxyModel;
    QLabel *const m_descriptionLabel;
    QLabel *const m_baseTargetLabel;
    QTextEdit *const m_logViewer;
    bool m_showReadonlyProperties = false;
    bool m_debug = false;
    QMetaObject::Connection m_updateExecuteButtonConnection;
};

#endif
