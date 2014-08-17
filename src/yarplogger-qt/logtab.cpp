#include "logtab.h"
#include "ui_logtab.h"

LogTab::LogTab(yarp::os::YarprunLogger::LoggerEngine*  _theLogger, std::string _portName, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LogTab)
{ 
    theLogger= _theLogger;
    portName =_portName;
    displayTimestamp=false;
    ui->setupUi(this);
    model_logs = new QStandardItemModel(this);
    proxyModelButtons = new QSortFilterProxyModel(this);
    proxyModelButtons->setSourceModel(model_logs);
    proxyModelSearch = new QSortFilterProxyModel(this);
    proxyModelSearch->setSourceModel(proxyModelButtons);
    proxyModelSearch->setFilterKeyColumn(-1); 
    ui->listView->setModel(proxyModelSearch);
    //ui->listView->setModel(model_logs);

    ui->listView->verticalHeader()->setVisible(false);
    ui->listView->setSelectionBehavior(QAbstractItemView::SelectRows);

    logTimer = new QTimer(this);
    connect(logTimer, SIGNAL(timeout()), this, SLOT(updateLog()));
    logTimer->start(500);

    model_logs->setHorizontalHeaderItem(0,new QStandardItem("timestamp"));
    model_logs->setHorizontalHeaderItem(1,new QStandardItem("level"));
    model_logs->setHorizontalHeaderItem(2,new QStandardItem("message"));
    ui->listView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->listView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->listView->verticalHeader()->setDefaultSectionSize(20);

    updateLog(true);
}

LogTab::~LogTab()
{
    delete ui;
}

void LogTab::clear_model_logs()
{
    mutex.lock();
    if (model_logs) model_logs->clear();
    mutex.unlock();
}

void LogTab::updateLog(bool from_beginning)
{
    mutex.lock();
    std::list<yarp::os::YarprunLogger::MessageEntry> messages;
    this->theLogger->get_messages_by_port_complete(portName,messages, from_beginning);
    int size_messages= messages.size();
    std::list<yarp::os::YarprunLogger::MessageEntry>::iterator it;
    QStandardItem *rootNode = model_logs->invisibleRootItem();
    for (it=messages.begin(); it!=messages.end(); it++)
    {
        QList<QStandardItem *> rowItem;
        QColor rowcolor;
        std:: string error_level;
        if      (it->level==yarp::os::YarprunLogger::LOGLEVEL_ERROR)     { rowcolor = QColor(Qt::red);    error_level=ERROR_STRING;}
        else if (it->level==yarp::os::YarprunLogger::LOGLEVEL_WARNING)   { rowcolor = QColor(Qt::yellow); error_level=WARNING_STRING; }
        else if (it->level==yarp::os::YarprunLogger::LOGLEVEL_INFO)      { rowcolor = QColor(Qt::green);  error_level=INFO_STRING; }
        else if (it->level==yarp::os::YarprunLogger::LOGLEVEL_DEBUG)     { rowcolor = QColor(Qt::blue);   error_level=DEBUG_STRING;}
        else if (it->level==yarp::os::YarprunLogger::LOGLEVEL_UNDEFINED) { rowcolor = QColor(Qt::white);  error_level="";     }
        else                                                             { rowcolor = QColor(Qt::white);  error_level="";     }

        rowItem << new QStandardItem(it->timestamp.c_str()) << new QStandardItem(error_level.c_str()) << new QStandardItem(it->text.c_str());

        for (QList<QStandardItem *>::iterator col_it = rowItem.begin(); col_it != rowItem.end(); col_it++)
        {
            (*col_it)->setBackground(rowcolor);
        }
        rootNode->appendRow(rowItem);
    }
    mutex.unlock();
}
