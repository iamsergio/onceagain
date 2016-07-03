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

#include "script.h"
#include "action.h"
#include "fileutils.h"
#include "stringutils.h"
#include "cmakeutils.h"
#include "kernel.h"

#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQmlContext>
#include <QDebug>
#include <QDir>

Script::Script(const QUrl &source, Kernel *kernel)
    : QObject(kernel)
    , m_sourceQml(source)
    , m_kernel(kernel)
{
    loadSourceQml();
}

bool Script::isValid() const
{
    return m_rootAction != nullptr;
}

QString Script::name() const
{
    return m_rootAction ? m_rootAction->name() : QString();
}

QList<QMetaProperty> Script::configurableProperties() const
{
    QList<QMetaProperty> props;
    if (!isValid())
        return props;

    const QMetaObject *mo = m_rootAction->metaObject();

    QMetaProperty hiddenPropsProp = mo->property(mo->indexOfProperty("hiddenProperties"));
    const QStringList hiddenProps = hiddenPropsProp.read(m_rootAction).toStringList();

    int numProperties = mo->propertyCount();
    for (int i = 0; i < numProperties; ++i) {
        QMetaProperty prop = mo->property(i);
        if ((prop.isUser() || !prop.isStored()) && prop.isWritable() && !hiddenProps.contains(prop.name()))
            props.push_back(prop);
    }
    return props;
}

Action *Script::rootAction() const
{
    return m_rootAction;
}

QString Script::description() const
{
    return m_rootAction ? m_rootAction->description() : QString();
}

QUrl Script::sourceUrl() const
{
    return m_sourceQml;
}

bool Script::execute() const
{
    if (m_rootAction) {
        if (m_rootAction->assertBaseTargetIsFolder()) {
            QDir dir(m_kernel->baseTarget());
            if (!dir.exists()) {
                qWarning() << Q_FUNC_INFO << "Couldn't find no folder named" << m_kernel->baseTarget();
                return false;
            }
        }

        return m_rootAction->execute();
    }

    return false;
}

void Script::loadSourceQml()
{
    auto engine = new QQmlEngine(this);
    engine->rootContext()->setContextProperty("_baseTarget", m_kernel->baseTarget());
    engine->rootContext()->setContextProperty("_dataFolder", m_kernel->scriptsFolder());
    engine->rootContext()->setContextProperty("_templatesFolder", m_kernel->scriptsFolder() + QStringLiteral("/templates/"));
    engine->rootContext()->setContextProperty("_file", m_kernel->fileUtils());
    engine->rootContext()->setContextProperty("_string", m_kernel->stringUtils());
    engine->rootContext()->setContextProperty("_cmake", m_kernel->cmakeUtils());
    auto rootComponent = new QQmlComponent(engine, m_sourceQml);
    m_rootAction = qobject_cast<Action*>(rootComponent->create());

    if (!m_rootAction)
        qWarning() << Q_FUNC_INFO << rootComponent->errorString();
}
