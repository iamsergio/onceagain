%3
#ifndef %1_H
#define %1_H
%6
class %2%4
{
%8public:
    %5%2(%7);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif
