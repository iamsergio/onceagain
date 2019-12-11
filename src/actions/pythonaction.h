#pragma once

#include <Python.h>
#include <QString>
#include "action.h"

class PythonAction : public Action
{
    Q_OBJECT
    Q_PROPERTY(QString pythonFileName READ pythonFileName WRITE setPythonFileName NOTIFY pythonFileNameChanged)
public:
    explicit PythonAction(QObject *parent = nullptr);

    QString pythonFileName() const;

public Q_SLOTS:
    void setPythonFileName(const QString &pythonFileName);

Q_SIGNALS:
    void pythonFileNameChanged();

protected:
    bool execute() override final;

private:
    QByteArray readPythonFile(const QString &filename) const;

    QString m_pythonFileName;
    const QByteArray m_commonPythonCode;
};
