#ifndef MESSAGE_H
#define MESSAGE_H
#include <qsqlrecord.h>
#include <qvector.h>
#include <QDate>
#include <QString>
#include <QTime>
#include "statement.h"
namespace SQLDAL {
	class Message : public Statement {
	public:
		Message(std::shared_ptr<Connect> Connect);
		Message();

		unsigned int		id;
		unsigned int		chat_id;
		unsigned int		owner_id;
		QString			data;
		QDate				date;
		QTime				time;
		bool				status;

		QVector<Message>	GetMessages();  // SelectAllInfoAboutOneChat
		void			    AddNewMessage();
		void              DeleteMessage();
		void			    UpdateMessage();

	private:
		QString UpdateQuery();
		QString SelectQuery();
		QString InsertQuery();
		QString DeleteQuery();
		QString CreateQueryCountOfMessages();
	};
}
#endif  // MESSAGE_H
