#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDate>
#include <QString>
#include <QTime>
#include <qsqlrecord.h>
#include <qvector.h>
#include "statement.h"

namespace SQLDAL {

  struct Messages {
	unsigned int id;
	unsigned int chat_id;
	unsigned int owner_id;
	QString	   data;
	QDate		   date;
	QTime		   time;
	bool		   status;
  };
  class Message : public Statement {
   public:
	Message(std::shared_ptr<Connect> Connect);
	Message();

	QVector<Messages>	GetMessages(unsigned int chat_id);  // Select All Info About One Chat
	void				AddNewMessage(const Messages& message);
	void				DeleteMessage(const Messages& message);
	void				UpdateMessage(const Messages& message);

   private:
	QString			UpdateQuery(const Messages& message);
	QString			SelectQuery(unsigned int chat_id);
	QString			InsertQuery(const Messages& message);
	QString			DeleteQuery(const Messages& message);
	QString			CreateQueryCountOfMessages(unsigned int chat_id);
  };
}  // namespace SQLDAL
#endif  // MESSAGE_H
