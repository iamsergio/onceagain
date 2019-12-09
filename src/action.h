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

#ifndef ACTION_H
#define ACTION_H

#include <QQuickItem>
#include <QStringList>

class Action : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Action* abortIfPreviousFailed READ abortIfPreviousFailed WRITE setAbortIfPreviousFailed NOTIFY abortIfPreviousFailedChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QUrl defaultBaseTarget READ defaultBaseTarget WRITE setDefaultBaseTarget NOTIFY defaultBaseTargetChanged)
    Q_PROPERTY(QQmlListProperty<Action> childActions READ childActions)
    Q_PROPERTY(bool assertBaseTargetIsFolder READ assertBaseTargetIsFolder WRITE setAssertBaseTargetIsFolder NOTIFY assertBaseTargetIsFolderChanged)
    Q_PROPERTY(bool assertBaseTargetIsFile READ assertBaseTargetIsFile WRITE setAssertBaseTargetIsFile NOTIFY assertBaseTargetIsFileChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QStringList hiddenProperties READ hiddenProperties WRITE setHiddenProperties NOTIFY hiddenPropertiesChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_CLASSINFO("DefaultProperty", "childActions")
public:
    explicit Action(QObject *parent = nullptr);
    QQmlListProperty<Action> childActions();
    QString name() const;
    void setName(const QString &name);

    void setAssertBaseTargetIsFolder(bool);
    bool assertBaseTargetIsFolder() const;

    void setAssertBaseTargetIsFile(bool);
    bool assertBaseTargetIsFile() const;

    Action * abortIfPreviousFailed() const;
    void setAbortIfPreviousFailed(Action*);
    bool inErrorState() const;

    QString description() const;
    void setDescription(const QString &);

    bool enabled() const;
    void setEnabled(bool);

    QStringList hiddenProperties() const;
    void setHiddenProperties(const QStringList &);

    QUrl defaultBaseTarget() const;
    void setDefaultBaseTarget(const QUrl &);

    virtual bool execute();

    bool visible() const;
    void setVisible(bool visible);

Q_SIGNALS:
    void nameChanged();
    void abortIfPreviousFailedChanged();
    void assertBaseTargetIsFolderChanged();
    void assertBaseTargetIsFileChanged();
    void descriptionChanged();
    void enabledChanged();
    void hiddenPropertiesChanged();
    void defaultBaseTargetChanged();
    void visibleChanged(bool);

private:
    bool canExecute() const;
    Action *m_abortIfPreviousFailed = nullptr;
    QString m_name;
    QString m_description;
    bool m_inErrorState = false;
    bool m_assertBaseTargetIsFolder = false;
    bool m_assertBaseTargetIsFile = false;
    QList<Action*> m_childActions;
    bool m_enabled = true;
    QStringList m_hiddenProperties;
    QUrl m_defaultBaseTarget;
    bool m_visible = true;
};

#endif
