#pragma once

#if 0

#include <vector>
class TasksMgr;
class TaskData;

class TasksVector : public std::vector
{
    public:
        TasksVector(TasksMgr* TM);
        ~TasksVector();

        void addTask(TaskData* TD); // alias for push_back
    protected:
    private:
        TasksMgr *m_TM;
};



#include "Framework\TasksMgr.h"

TasksVector::TasksVector(TasksMgr* TM)
    :
    std::vector<TaskData*>(),
    m_TM(TM)
{
}

TasksVector::~TasksVector()
{
    for(auto TD : *this)
        m_TM->removeTask(TD);
}


TasksVector::addTask(TaskData *TD)
{
    push_back(TD);
}

#endif
