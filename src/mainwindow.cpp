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

#include "mainwindow.h"
#include "kernel.h"
#include "action.h"
#include "scriptmodel.h"
#include "scriptproxymodel.h"

#include <QTreeView>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QDir>
#include <QFileInfo>
#include <QTextEdit>
#include <QDockWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QProcess>
#include <QMenuBar>
#include <QApplication>
#include <QInputDialog>
#include <QHeaderView>
#include <QContextMenuEvent>

static QTextEdit *s_logViewer = nullptr;

void myMessageOutput(QtMsgType, const QMessageLogContext &, const QString &msg)
{
    static QMutex m_mutex;
    QMutexLocker locker(&m_mutex);
    if (!s_logViewer)
        return;

    QTextCursor cursor(s_logViewer->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(msg + "<br>");
}

static void runCommand(const QString &command)
{
    auto proc = new QProcess();
    QObject::connect(proc, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                     [proc](int ret, QProcess::ExitStatus) {
        if (ret != 0) {
            qWarning() << "Error running" << proc->program() << proc->arguments();
        }
        proc->deleteLater();
    });
    proc->start(command);
}

class TableWidgetItem : public QTableWidgetItem
{
public:
    TableWidgetItem(QMetaProperty prop, Action *action)
        : QTableWidgetItem(prop.read(action).toString())
        , m_prop(prop)
        , m_action(action)
    {
        Q_ASSERT(m_prop.isValid());
    }

    void setData(int role, const QVariant &value) override
    {
        if (role == Qt::EditRole) {
            m_prop.write(m_action, value);
            QTableWidgetItem::setData(Qt::DisplayRole, value.toString()); // Read back from the object, there might have been conversions
        }
    }

    QVariant propValue() const
    {
        return m_prop.read(m_action);
    }

    QMetaProperty m_prop;
    Action *const m_action;
};

MainWindow::MainWindow(Kernel *kernel, QWidget *parent)
    : QMainWindow(parent)
    , m_kernel(kernel)
    , m_scriptProxyModel(new ScriptProxyModel(kernel->baseTarget(), this))
    , m_descriptionLabel(new QLabel(this))
    , m_baseTargetLabel(new QLabel(this))
    , m_logViewer(new QTextEdit(this))
{
    resize(800, 600);
    m_scriptProxyModel->setSourceModel(m_kernel->scriptModel());
    m_logViewer->setMaximumHeight(100);
    s_logViewer = m_logViewer;
    m_logViewer->setTextInteractionFlags(Qt::TextSelectableByMouse);
    qInstallMessageHandler(myMessageOutput);
    m_kernel->loadScripts();

    auto central = new QWidget();
    auto outterLayout = new QVBoxLayout(central);
    auto layout = new QHBoxLayout();
    outterLayout->addWidget(m_baseTargetLabel);
    outterLayout->addLayout(layout);
    m_scriptView = new QTreeView(central);
    m_scriptView->setModel(m_scriptProxyModel);
    m_scriptView->setAlternatingRowColors(true);
    m_scriptView->header()->hide();
    m_propertyTable = new QTableWidget(central);
    m_propertyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(m_propertyTable, &QTableWidget::itemDoubleClicked, this, &MainWindow::onPropertyCellDoubleClicked);

    m_executeButton = new QPushButton(tr("Execute script"));
    auto groupBox = new QGroupBox(tr("Description"));
    groupBox->setMinimumWidth(300);
    auto boxLayout = new QVBoxLayout();
    groupBox->setLayout(boxLayout);
    boxLayout->addWidget(m_descriptionLabel);

    m_propertyTable->setColumnCount(2);
    layout->addWidget(m_scriptView);
    layout->addWidget(m_propertyTable);
    layout->addWidget(groupBox);
    outterLayout->addWidget(m_executeButton);

    auto bottomdock = new QDockWidget(tr("Log"), this);
    bottomdock->setWidget(m_logViewer);
    bottomdock->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, bottomdock);

    setCentralWidget(central);

    setupScriptView();
    onScriptSelected();
    setupPropertyTable();
    connect(m_executeButton, &QPushButton::clicked, this, &MainWindow::executeScript);
    connect(m_kernel, &Kernel::baseTargetChanged, this, &MainWindow::updateBaseTargetLabel);
    m_descriptionLabel->setAlignment(Qt::AlignTop);
    m_baseTargetLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    updateBaseTargetLabel();
    connect(m_scriptView, &QListView::doubleClicked, this, &MainWindow::openScriptExternally);
    connect(m_scriptProxyModel, &QSortFilterProxyModel::modelReset, this, &MainWindow::onScriptSelected);

    auto menubar = new QMenuBar(this);
    auto fileMenu = new QMenu(tr("File"));
    auto toolsMenu = new QMenu(tr("Tools"));
    auto aboutMenu = new QMenu(tr("About"));
    menubar->addMenu(fileMenu);
    menubar->addMenu(toolsMenu);
    menubar->addMenu(aboutMenu);
    auto newAction = fileMenu->addAction(tr("New script..."));
    auto newFolderAction = fileMenu->addAction(tr("New script folder..."));
    auto reloadAction = fileMenu->addAction(tr("Reload"));
    reloadAction->setShortcut(QKeySequence(QStringLiteral("F5")));
    auto quitAction = fileMenu->addAction(tr("Quit"));
    auto openScriptsDir = toolsMenu->addAction(tr("Open scripts dir"));
    auto openTemplateDir = toolsMenu->addAction(tr("Open templates dir"));
    newAction->setIcon(QIcon::fromTheme("document-new"));
    newAction->setShortcut(QKeySequence(QStringLiteral("ctrl+N")));
    reloadAction->setIcon(QIcon::fromTheme("view-refresh"));

    quitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(newAction, &QAction::triggered, this, &MainWindow::createNewScript);
    connect(newFolderAction, &QAction::triggered, this, &MainWindow::createNewScriptFolder);
    connect(reloadAction, &QAction::triggered, m_kernel, &Kernel::loadScripts);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::exit);
    connect(openScriptsDir, &QAction::triggered, this, &MainWindow::openScriptsDir);
    connect(openTemplateDir, &QAction::triggered, this, &MainWindow::openTemplatesDir);
    setMenuBar(menubar);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *ev)
{
    QModelIndex index = m_scriptView->indexAt(m_scriptView->viewport()->mapFromGlobal(ev->globalPos()));
    QModelIndex sourceIndex = m_scriptProxyModel->mapToSource(index);
    if (!sourceIndex.isValid())
        return;

    QMenu menu(this);

    QAction *del = menu.addAction("Delete");
    connect(del, &QAction::triggered, [this, sourceIndex] {
        m_kernel->scriptModel()->remove(sourceIndex);
    });

    menu.exec(QCursor::pos());
}

void MainWindow::openFileExplorer(QString path)
{
    QFileInfo pathInfo(path);
    path = pathInfo.absoluteFilePath(); // Cleanup path, remove double //

    QString fileExplorerCommand = m_kernel->externalFileExplorer();
    if (fileExplorerCommand.isEmpty()) {
        qWarning() << "Please set the ONCE_AGAIN_FILE_EXPLORER env variable. For example to"
                   << "<b>\"dolphin %1\"</b>";
        return;
    }

    qDebug() << "Opening" << path << "...";
    if (fileExplorerCommand.contains(QLatin1String("%1"))) {
        fileExplorerCommand = fileExplorerCommand.arg(path);
    } else {
        fileExplorerCommand += ' ' + path;
    }

    runCommand(fileExplorerCommand);
}

void MainWindow::openTemplatesDir()
{
    openFileExplorer(m_kernel->templatesFolder());
}

void MainWindow::openScriptsDir()
{
    openFileExplorer(m_kernel->scriptsFolder());
}

static bool isValidScriptName(const QString &name)
{
    static const QString allowedNonAlpha = QStringLiteral(".-_ ");
    for (auto c : name) {
        if (!(c.isLetterOrNumber() || allowedNonAlpha.contains(c)))
            return false;
    }

    return true;
}

void MainWindow::createNewScript()
{
    QString editorCommand = m_kernel->externalEditor();
    if (editorCommand.isEmpty()) {
        qWarning() << "No external editor specified.<br>";
        qWarning() << "Please set the ONCE_AGAIN_EDITOR env variable. For example to"
                   << "<b>\"kate %1\"</b>";
        return;
    }

    QString name = QInputDialog::getText(this, tr("New script"), tr("Enter script name"));
    if (name.isEmpty())
        return;

    if (!isValidScriptName(name)) {
        qWarning() << "Invalid script name" << name;
        return;
    }

    name.replace(' ', QString());

    if (!name.endsWith(QLatin1String(".qml")))
        name += QLatin1String(".qml");

    const QString parentFolder = selectedFolder();
    if (parentFolder.isEmpty()) {
        name = m_kernel->scriptsFolder() + QStringLiteral("/%1").arg(name);
    } else {
        name = parentFolder + QStringLiteral("/%1").arg(name);
    }

    runCommand(editorCommand + " " + name);
}

void MainWindow::createNewScriptFolder()
{
    QString name = QInputDialog::getText(this, tr("New script folder"), tr("Enter folder name"));
    if (name.isEmpty() || name.contains(QLatin1Char('/')) || name.contains(QLatin1Char('\\')))
        return;

    const QString parentFolder = selectedFolder();
    const QString absoluteFolderPath = parentFolder.isEmpty() ? (m_kernel->scriptsFolder() + QStringLiteral("/%1").arg(name))
                                                              : (parentFolder + QStringLiteral("/%1").arg(name));

    QDir dir(absoluteFolderPath);

    if (dir.mkdir(absoluteFolderPath)) {
        m_kernel->loadScripts();
    } else {
        qWarning() << "Failed to create" << absoluteFolderPath;
    }
}

void MainWindow::onPropertyCellDoubleClicked(QTableWidgetItem *item)
{
    auto twi = static_cast<TableWidgetItem*>(item);
    if (twi->m_prop.type() == QVariant::Bool) {
        twi->setData(Qt::EditRole, QVariant(!twi->propValue().toBool()));
    }
}

void MainWindow::openScriptExternally(const QModelIndex &index)
{
    Script *script = index.data(ScriptRole).value<Script*>();
    if (!script) {
        qWarning() << "Failed to open script";
        return;
    }

    QString editorCommand = m_kernel->externalEditor();
    if (editorCommand.isEmpty()) {
        qWarning() << "No external editor specified.<br>";
        qWarning() << "Please set the ONCE_AGAIN_EDITOR env variable. For example to"
                   << "<b>\"kate %1\"</b>";
        return;
    }

    const QString scriptFilename = script->sourceUrl().toLocalFile();

    QString fullCommand = editorCommand;
    if (editorCommand.contains(QLatin1String("%1"))) {
        fullCommand = fullCommand.arg(scriptFilename);
    } else {
        fullCommand += " " + scriptFilename;
    }

    runCommand(fullCommand);
}

void MainWindow::updateBaseTargetLabel()
{
    Script *script = selectedScript();
    QString baseTarget = script ? script->baseTarget() : m_kernel->baseTarget();
    if (baseTarget.isEmpty())
        baseTarget = QStringLiteral(".");
    QFileInfo info(baseTarget);
    QString absolutePath = info.absoluteFilePath();
    if (info.isDir())
        absolutePath += "/";

    m_baseTargetLabel->setText(tr("<b>Base target:</b> %1").arg(absolutePath));
}

void MainWindow::updateDescription()
{
    Script *script = selectedScript();
    m_descriptionLabel->setText(script ? script->description() : QString());
}

Script *MainWindow::selectedScript() const
{
    const auto indexes = m_scriptView->selectionModel()->selectedIndexes();
    return indexes.isEmpty() ? nullptr : indexes.first().data(ScriptRole).value<Script*>();
}

QString MainWindow::selectedFolder() const
{
    const auto indexes = m_scriptView->selectionModel()->selectedIndexes();
    return indexes.isEmpty() ? QString() : indexes.first().data(FolderPathRole).toString();
}

void MainWindow::onScriptSelected()
{
    Script *script = selectedScript();
    m_executeButton->setEnabled(script != nullptr);
    setupPropertyTable(script);
    updateDescription();
    updateBaseTargetLabel();
}

void MainWindow::setupScriptView()
{
    connect(m_scriptView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::onScriptSelected);
}

void MainWindow::executeScript()
{
    if (Script *script = selectedScript()) {
        if (!script->execute())
            qWarning() << Q_FUNC_INFO << "Error"; // TODO: Some UI
    } else {
        qWarning() << "No script selected";
    }
}

void MainWindow::setupPropertyTable(Script *script)
{
    m_propertyTable->clear();
    m_propertyTable->setHorizontalHeaderLabels({ QStringLiteral("Name"), QStringLiteral("Value") });
    m_propertyTable->setEnabled(script && !script->configurableProperties().isEmpty());
    if (!script)
        return;

    QList<QMetaProperty> properties = script->configurableProperties();
    m_propertyTable->setRowCount(properties.size());
    int row = 0;
    for (auto prop : properties) {
        auto item = new QTableWidgetItem(prop.name());
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable); // Not editable
        m_propertyTable->setItem(row, 0, item);
        item = new TableWidgetItem(prop, script->rootAction());
        if (!prop.isWritable() || prop.type() == QVariant::Bool) {
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable); // Not editable
        }
        m_propertyTable->setItem(row, 1, item);
        ++row;
    }
}
