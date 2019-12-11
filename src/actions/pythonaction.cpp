#include "pythonaction.h"
#include "kernel.h"

#include <QFile>
#include <QDebug>
#include <QScopeGuard>

#include <Python.h>

PythonAction::PythonAction(QObject *parent)
    : Action(parent)
    , m_commonPythonCode(readPythonFile(QStringLiteral(":/src/common.py")))
{
}

bool PythonAction::execute()
{
    if (name().isEmpty()) {
        qWarning() << "PythonAction requires a name. Otherwise we don't know which py file to run";
        return false;
    }

    Kernel::instance()->setCurrentAction(this);
    auto cleanup = qScopeGuard([] {
        Kernel::instance()->setCurrentAction(nullptr);
    });

    const QString pythonFileName = QStringLiteral("%1.py").arg(name().toLower());

    const QByteArray pythonCode = readPythonFile(QStringLiteral(":/src/actions/%1").arg(pythonFileName));
    if (pythonCode.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Could not read python code from" << pythonFileName;
        return false;
    }

    const bool success = PyRun_SimpleString((m_commonPythonCode + pythonCode).constData()) == 0;

    if (success)
        qDebug() << "PythonAction: success";
    else
        qDebug() << "PythonAction: error";

    return success;
}

QByteArray PythonAction::readPythonFile(const QString &filename) const
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << Q_FUNC_INFO << file.errorString();
        return {};
    }

    return file.readAll();
}
