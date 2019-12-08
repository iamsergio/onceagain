#pragma once

#include <Python.h>
#include "action.h"

class PythonAction : public Action
{
    Q_OBJECT
public:
    explicit PythonAction(const QString &pythonFileName, QObject *parent = nullptr);

protected:
    bool execute() override final;

private:

    QByteArray readPythonFile(const QString &filename) const;

    const QString m_pythonFileName;
    const QByteArray m_commonPythonCode;
};
