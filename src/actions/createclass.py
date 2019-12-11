import os, shutil

def execute_action():
    className = get_property('className')
    includeGuard = get_property('includeGuard')
    camelCaseFileName = get_property('includeGuard')
    headerFileName = get_property('headerFileName')
    cppFileName = get_property('cppFileName')
    baseTarget = get_property('baseTarget') + '/'
    baseClass = get_property('baseClass')
    namespace = get_property('namespace')
    isQObject = get_property('isQObject')
    explicit = get_property('explicit')
    ctorArguments = get_property('ctorArguments')
    implCtorArguments = get_property('implCtorArguments')
    ctorInitList = get_property('ctorInitList')

    # Create the header file:

    header_lines = []

    header_lines.append('#pragma once\n\n')
    baseClassInheritanceLine = ""
    if baseClass:
        header_lines.append('#include <%s>\n\n' % baseClass)
        baseClassInheritanceLine = " : public " + baseClass

    if namespace:
        header_lines.append('namespace %s {\n\n' % namespace)

    header_lines.append('class ' + className + baseClassInheritanceLine + '\n{\n')
    if isQObject:
        header_lines.append('    Q_OBJECT\n')
    header_lines.append('public:\n')

    ctor_line = '    '
    if explicit:
        ctor_line += 'explicit '
    ctor_line += className + '(%s);\n' % ctorArguments
    header_lines.append(ctor_line)

    header_lines.append('};\n')
    if namespace:
        header_lines.append('}\n')

    f = open(baseTarget + headerFileName, 'w')
    f.writelines(header_lines)
    f.close()

    # Create the cpp file:
    cpp_lines = []

    cpp_lines.append('#include "%s"\n\n' % headerFileName)
    if namespace:
        cpp_lines.append('using namespace %s\n\n' % namespace)

    cpp_lines.append('%s::%s(%s)\n' % (className, className, implCtorArguments))
    if ctorInitList:
        cpp_lines.append('    : %s\n' % ctorInitList)
    cpp_lines.append('{\n}\n')

    cpp_lines.append('\n')

    f = open(baseTarget + cppFileName, 'w')
    f.writelines(cpp_lines)
    f.close()

    return True

execute_action()
