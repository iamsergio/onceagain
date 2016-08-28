%3
#include "%1"

%2::%2(%4)%5
{
}

bool %2::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (source_parent.isValid())
        return false;

    return true;
}
