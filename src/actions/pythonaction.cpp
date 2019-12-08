#include "pythonaction.h"
#include "kernel.h"

#include <QFile>
#include <QDebug>
#include <QScopeGuard>

#include <Python.h>

PythonAction::PythonAction(const QString &pythonFileName, QObject *parent)
    : Action(parent)
    , m_pythonFileName(pythonFileName)
    , m_commonPythonCode(readPythonFile(QStringLiteral(":/src/common.py")))
{
}

bool PythonAction::execute()
{
    Kernel::instance()->setCurrentAction(this);
    auto cleanup = qScopeGuard([] {
        Kernel::instance()->setCurrentAction(nullptr);
    });

    const QByteArray pythonCode = readPythonFile(QStringLiteral(":/src/actions/%1").arg(m_pythonFileName));
    if (pythonCode.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Could not read python code from" << m_pythonFileName;
        return false;
    }

    return PyRun_SimpleString((m_commonPythonCode + pythonCode).constData()) == 0;
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
